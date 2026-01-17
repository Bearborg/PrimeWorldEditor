#include "Editor/Undo/CCloneSelectionCommand.h"

#include "Editor/WorldEditor/CWorldEditor.h"

#include <QCoreApplication>

CCloneSelectionCommand::CCloneSelectionCommand(INodeEditor *pEditor)
    : IUndoCommand(QCoreApplication::translate("CCloneSelectionCommand", "Clone"))
    , mpEditor(qobject_cast<CWorldEditor*>(pEditor)) // todo: fix this! bad assumption! (clone handling code is in INodeEditor but active area is in CWorldEditor)
{
    mOriginalSelection = mpEditor->Selection()->SelectedNodeList();

    for (auto* node : mpEditor->Selection()->Nodes())
    {
        if (node->NodeType() == ENodeType::Script)
        {
            mNodesToClone.push_back(node);

            // Fetch linked objects
            auto* pScript = static_cast<CScriptNode*>(node);
            auto* pInst = pScript->Instance();

            for (const auto* link : pInst->Links(ELinkType::Outgoing))
            {
                CScriptNode *pNode = mpEditor->Scene()->NodeForInstance(link->Receiver());

                if (!pNode->IsSelected())
                    mLinkedInstances.push_back(pNode->Instance());
            }
        }
    }
}

void CCloneSelectionCommand::undo()
{
    QList<CSceneNode*> ClonedNodes = mClonedNodes.DereferenceList();
    mpEditor->Selection()->Clear();

    for (CSceneNode *pNode : ClonedNodes)
    {
        CScriptObject *pInst = static_cast<CScriptNode*>(pNode)->Instance();

        mpEditor->NotifyNodeAboutToBeDeleted(pNode);
        mpEditor->Scene()->DeleteNode(pNode);
        mpEditor->ActiveArea()->DeleteInstance(pInst);
        mpEditor->NotifyNodeDeleted();
    }

    mClonedNodes.clear();
    mpEditor->OnLinksModified(mLinkedInstances.DereferenceList());
    mpEditor->Selection()->SetSelectedNodes(mOriginalSelection.DereferenceList());
}

void CCloneSelectionCommand::redo()
{
    QList<CSceneNode*> ToClone = mNodesToClone.DereferenceList();
    QList<CSceneNode*> ClonedNodes;
    QList<CInstanceID> ToCloneInstanceIDs;
    QList<CInstanceID> ClonedInstanceIDs;

    // Clone nodes
    for (CSceneNode *pNode : ToClone)
    {
        mpEditor->NotifyNodeAboutToBeSpawned();
        CScriptNode *pScript = static_cast<CScriptNode*>(pNode);
        CScriptObject *pInstance = pScript->Instance();

        CScriptObject *pCloneInst = mpEditor->ActiveArea()->SpawnInstance(pInstance->Template(), pInstance->Layer());
        pCloneInst->CopyProperties(pInstance);
        pCloneInst->EvaluateProperties();

        CScriptNode *pCloneNode = mpEditor->Scene()->CreateScriptNode(pCloneInst);
        pCloneNode->SetName(pScript->Name());
        pCloneNode->SetPosition(pScript->LocalPosition());
        pCloneNode->SetRotation(pScript->LocalRotation());
        pCloneNode->SetScale(pScript->LocalScale());

        ToCloneInstanceIDs.push_back(pInstance->InstanceID());
        ClonedInstanceIDs.push_back(pCloneInst->InstanceID());
        ClonedNodes.push_back(pCloneNode);
        mClonedNodes.push_back(pCloneNode);
        mpEditor->NotifyNodeSpawned(pCloneNode);
    }

    // Clone outgoing links from source object; incoming ones are discarded
    for (qsizetype iNode = 0; iNode < ClonedNodes.size(); iNode++)
    {
        auto* pSrc = static_cast<CScriptNode*>(ToClone[iNode])->Instance();
        auto* pClone = static_cast<CScriptNode*>(ClonedNodes[iNode])->Instance();

        for (const auto* srcLink : pSrc->Links(ELinkType::Outgoing))
        {
            // If we're cloning the receiver then target the cloned receiver instead of the original one.
            auto ReceiverID = srcLink->ReceiverID();
            if (ToCloneInstanceIDs.contains(ReceiverID))
                ReceiverID = ClonedInstanceIDs[ToCloneInstanceIDs.indexOf(ReceiverID)];

            CLink *pCloneLink = new CLink(srcLink->Area(), srcLink->State(), srcLink->Message(), pClone->InstanceID(), ReceiverID);
            pCloneLink->Sender()->AddLink(ELinkType::Outgoing, pCloneLink);
            pCloneLink->Receiver()->AddLink(ELinkType::Incoming, pCloneLink);
        }
    }

    // Call LoadFinished
    for (CSceneNode *pNode : ClonedNodes)
        pNode->OnLoadFinished();

    mpEditor->OnLinksModified(mLinkedInstances.DereferenceList());
    mpEditor->Selection()->SetSelectedNodes(mClonedNodes.DereferenceList());
}
