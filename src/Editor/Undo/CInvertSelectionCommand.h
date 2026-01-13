#ifndef CINVERTSELECTIONCOMMAND_H
#define CINVERTSELECTIONCOMMAND_H

#include "Editor/Undo/IUndoCommand.h"
#include "Editor/Undo/ObjReferences.h"

#include <Core/Scene/CSceneNode.h>

#include <QCoreApplication>

class CInvertSelectionCommand : public IUndoCommand
{
    CNodeSelection *mpSelection;
    CNodePtrList mOldSelection;
    CNodePtrList mNewSelection;

public:
    CInvertSelectionCommand(CNodeSelection *pSelection, CScene *pScene, FNodeFlags NodeFlags)
        : IUndoCommand(QCoreApplication::translate("CInvertSelectionCommand", "Invert Selection"))
        , mpSelection(pSelection)
    {
        for (auto* node : pScene->MakeNodeView(NodeFlags))
        {
            if (node->IsSelected())
                mOldSelection.push_back(node);
            else
                mNewSelection.push_back(node);
        }
    }

    void undo() override { mpSelection->SetSelectedNodes(mOldSelection.DereferenceList()); }
    void redo() override { mpSelection->SetSelectedNodes(mNewSelection.DereferenceList()); }
    bool AffectsCleanState() const override { return false; }
};

#endif // CINVERTSELECTIONCOMMAND_H
