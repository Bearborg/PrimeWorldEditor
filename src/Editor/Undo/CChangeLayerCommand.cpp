#include "Editor/Undo/CChangeLayerCommand.h"

#include "Editor/WorldEditor/CWorldEditor.h"
#include <Core/Scene/CScriptNode.h>

#include <QCoreApplication>

CChangeLayerCommand::CChangeLayerCommand(CWorldEditor *pEditor, std::span<CScriptNode*> nodeList, CScriptLayer *pNewLayer)
    : IUndoCommand(QCoreApplication::translate("CChangeLayerCommand", "Change Layer"))
    , mpNewLayer(pNewLayer)
    , mpEditor(pEditor)
{
    for (CScriptNode *pNode : nodeList)
    {
        CScriptLayer *pLayer = pNode->Instance()->Layer();

        if (pLayer != pNewLayer && !mNodes.contains(pNode))
        {
            mNodes.push_back(pNode);
            mOldLayers[pNode->ID()] = pLayer;
        }
    }
}

void CChangeLayerCommand::undo()
{
    mpEditor->InstancesLayerAboutToChange();
    QList<CSceneNode*> Nodes = mNodes.DereferenceList();

    QList<CScriptNode*> ScriptNodes;
    for (CSceneNode* pNode : Nodes)
        ScriptNodes.push_back(static_cast<CScriptNode*>(pNode));

    for (CScriptNode *pNode : ScriptNodes)
        pNode->Instance()->SetLayer(mOldLayers[pNode->ID()]);

    mpEditor->InstancesLayerChanged(ScriptNodes);
}

void CChangeLayerCommand::redo()
{
    mpEditor->InstancesLayerAboutToChange();
    QList<CSceneNode*> Nodes = mNodes.DereferenceList();

    QList<CScriptNode*> ScriptNodes;
    for (CSceneNode* pNode : Nodes)
        ScriptNodes.push_back(static_cast<CScriptNode*>(pNode));

    for (CScriptNode *pNode : ScriptNodes)
        pNode->Instance()->SetLayer(mpNewLayer);

    mpEditor->InstancesLayerChanged(ScriptNodes);
}

