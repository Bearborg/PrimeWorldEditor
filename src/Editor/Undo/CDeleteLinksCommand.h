#ifndef CDELETELINKSCOMMAND_H
#define CDELETELINKSCOMMAND_H

#include "Editor/Undo/IUndoCommand.h"
#include "Editor/Undo/ObjReferences.h"

#include <span>

class CScriptObject;
class CWorldEditor;

class CDeleteLinksCommand : public IUndoCommand
{
    CWorldEditor *mpEditor = nullptr;
    CInstancePtrList mAffectedInstances;

    struct SDeletedLink;
    QList<SDeletedLink> mLinks;

public:
    CDeleteLinksCommand();
    CDeleteLinksCommand(CWorldEditor *pEditor, CScriptObject *pObject, ELinkType Type, std::span<uint32_t> indices);
    ~CDeleteLinksCommand() override;

    void undo() override;
    void redo() override;
    bool AffectsCleanState() const override { return true; }
};

#endif // CDELETELINKSCOMMAND_H
