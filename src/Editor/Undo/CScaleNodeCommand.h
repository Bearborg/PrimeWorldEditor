#ifndef CSCALENODECOMMAND_H
#define CSCALENODECOMMAND_H

#include "Editor/Undo/IUndoCommand.h"
#include "Editor/Undo/ObjReferences.h"

#include <QList>

class CSceneNode;
class INodeEditor;

class CScaleNodeCommand : public IUndoCommand
{
    struct SNodeScale;

    QList<SNodeScale> mNodeList;
    INodeEditor *mpEditor = nullptr;
    bool mCommandEnded = false;

public:
    CScaleNodeCommand();
    CScaleNodeCommand(INodeEditor *pEditor, const QList<CSceneNode*>& rkNodes, bool UsePivot, const CVector3f& rkPivot, const CVector3f& rkDelta);
    ~CScaleNodeCommand() override;

    int id() const override;
    bool mergeWith(const QUndoCommand *pkOther) override;
    void undo() override;
    void redo() override;
    bool AffectsCleanState() const override { return true; }
    static CScaleNodeCommand* End();
};

#endif // CScaleNODECOMMAND_H
