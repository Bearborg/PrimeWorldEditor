#ifndef CDELETELINKSCOMMAND_H
#define CDELETELINKSCOMMAND_H

#include "Editor/Undo/IUndoCommand.h"
#include "Editor/Undo/ObjReferences.h"

class CScriptObject;
class CWorldEditor;

class CDeleteLinksCommand : public IUndoCommand
{
    CWorldEditor *mpEditor = nullptr;
    CInstancePtrList mAffectedInstances;

    struct SDeletedLink
    {
        uint32 State;
        uint32 Message;
        CInstancePtr pSender;
        CInstancePtr pReceiver;
        uint32 SenderIndex;
        uint32 ReceiverIndex;
    };
    QList<SDeletedLink> mLinks;

public:
    CDeleteLinksCommand() = default;
    CDeleteLinksCommand(CWorldEditor *pEditor, CScriptObject *pObject, ELinkType Type, const QList<uint32>& rkIndices);
    void undo() override;
    void redo() override;
    bool AffectsCleanState() const override { return true; }
};

#endif // CDELETELINKSCOMMAND_H
