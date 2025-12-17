#ifndef CPASTENODESCOMMAND
#define CPASTENODESCOMMAND

#include <Common/Math/CVector3f.h>
#include "Editor/Undo/IUndoCommand.h"
#include "Editor/Undo/ObjReferences.h"

#include <memory>

class CNodeCopyMimeData;
class CScriptLayer;
class CWorldEditor;

class CPasteNodesCommand : public IUndoCommand
{
    CWorldEditor *mpEditor;
    CScriptLayer *mpLayer;
    CVector3f mPastePoint;
    std::unique_ptr<CNodeCopyMimeData> mpMimeData;
    CNodePtrList mPastedNodes;
    CNodePtrList mOriginalSelection;
    CInstancePtrList mLinkedInstances;

public:
    CPasteNodesCommand(CWorldEditor *pEditor, CScriptLayer *pLayer, CVector3f PastePoint);
    ~CPasteNodesCommand() override;

    void undo() override;
    void redo() override;

    bool AffectsCleanState() const override { return true; }
};

#endif // CPASTENODESCOMMAND

