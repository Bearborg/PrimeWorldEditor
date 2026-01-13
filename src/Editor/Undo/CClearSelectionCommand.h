#ifndef CCLEARSELECTIONCOMMAND_H
#define CCLEARSELECTIONCOMMAND_H

#include "Editor/Undo/IUndoCommand.h"
#include "Editor/Undo/ObjReferences.h"

#include <QCoreApplication>

class CClearSelectionCommand : public IUndoCommand
{
    CNodeSelection *mpSelection;
    CNodePtrList mOldSelection;

public:
    explicit CClearSelectionCommand(CNodeSelection *pSelection)
        : IUndoCommand(QCoreApplication::translate("CClearSelectionCommand", "Clear Selection")),
          mpSelection(pSelection)
    {
        for (auto* node : pSelection->Nodes())
            mOldSelection.push_back(node);
    }

    void undo() override { mpSelection->SetSelectedNodes(mOldSelection.DereferenceList()); }
    void redo() override { mpSelection->Clear(); }
    bool AffectsCleanState() const override { return false; }
};

#endif // CCLEARSELECTIONCOMMAND_H
