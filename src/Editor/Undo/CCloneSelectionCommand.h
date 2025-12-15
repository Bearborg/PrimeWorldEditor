#ifndef CCLONESELECTIONCOMMAND_H
#define CCLONESELECTIONCOMMAND_H

#include "Editor/Undo/IUndoCommand.h"
#include "Editor/Undo/ObjReferences.h"

class INodeEditor;
class CWorldEditor;

class CCloneSelectionCommand : public IUndoCommand
{
    CWorldEditor *mpEditor;
    CNodePtrList mOriginalSelection;
    CNodePtrList mNodesToClone;
    CNodePtrList mClonedNodes;
    CInstancePtrList mLinkedInstances;

public:
    explicit CCloneSelectionCommand(INodeEditor *pEditor);

    void undo() override;
    void redo() override;
    bool AffectsCleanState() const override { return true; }
};

#endif // CCLONESELECTIONCOMMAND_H
