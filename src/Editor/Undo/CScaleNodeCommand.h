#ifndef CSCALENODECOMMAND_H
#define CSCALENODECOMMAND_H

#include "Editor/Undo/IUndoCommand.h"
#include "Editor/Undo/ObjReferences.h"

#include <QList>
#include <span>

class CSceneNode;
class CVector3f;
class INodeEditor;

class CScaleNodeCommand : public IUndoCommand
{
    struct SNodeScale;

    QList<SNodeScale> mNodeList;
    INodeEditor *mpEditor = nullptr;
    bool mCommandEnded = false;

public:
    CScaleNodeCommand();
    CScaleNodeCommand(INodeEditor *pEditor, std::span<CSceneNode*> nodes, bool UsePivot, const CVector3f& rkPivot, const CVector3f& rkDelta);
    ~CScaleNodeCommand() override;

    int id() const override;
    bool mergeWith(const QUndoCommand *pkOther) override;
    void undo() override;
    void redo() override;
    bool AffectsCleanState() const override { return true; }
    static CScaleNodeCommand* End();
};

#endif // CScaleNODECOMMAND_H
