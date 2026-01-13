#ifndef CSELECTALLCOMMAND_H
#define CSELECTALLCOMMAND_H

#include "Editor/Undo/IUndoCommand.h"
#include "Editor/Undo/ObjReferences.h"
#include <Core/Scene/ENodeType.h>

#include <QCoreApplication>

class CSelectAllCommand : public IUndoCommand
{
    CNodePtrList mOldSelection;
    CNodePtrList mNewSelection;
    CNodeSelection *mpSelection;

public:
    CSelectAllCommand(CNodeSelection *pSelection, CScene *pScene, FNodeFlags NodeFlags)
        : IUndoCommand(QCoreApplication::translate("CSelectAllCommand", "Select All"))
        , mpSelection(pSelection)
    {
        for (auto* node : pSelection->Nodes())
            mOldSelection.push_back(node);
        for (auto* node : pScene->MakeNodeView(NodeFlags))
            mNewSelection.push_back(node);
    }

    void undo() override { mpSelection->SetSelectedNodes(mOldSelection.DereferenceList()); }
    void redo() override { mpSelection->SetSelectedNodes(mNewSelection.DereferenceList()); }
    bool AffectsCleanState() const override { return false; }
};

#endif // CSELECTALLCOMMAND_H
