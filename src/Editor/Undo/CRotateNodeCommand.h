#ifndef CROTATENODECOMMAND_H
#define CROTATENODECOMMAND_H

#include "Editor/Undo/IUndoCommand.h"
#include "Editor/Undo/ObjReferences.h"

#include <QList>

class CSceneNode;
class INodeEditor;

class CRotateNodeCommand : public IUndoCommand
{
    struct SNodeRotate
    {
        CNodePtr pNode;
        CVector3f InitialPos;
        CQuaternion InitialRot;
        CVector3f NewPos;
        CQuaternion NewRot;
    };
    QList<SNodeRotate> mNodeList;
    INodeEditor *mpEditor = nullptr;
    bool mCommandEnded = false;

public:
    CRotateNodeCommand();
    CRotateNodeCommand(INodeEditor *pEditor, const QList<CSceneNode*>& rkNodes, bool UsePivot, const CVector3f& rkPivot, const CQuaternion& rkPivotRotation, const CQuaternion& rkDelta, ETransformSpace TransformSpace);
    ~CRotateNodeCommand() override;

    int id() const override;
    bool mergeWith(const QUndoCommand *pkOther) override;
    void undo() override;
    void redo() override;
    bool AffectsCleanState() const override { return true; }
    static CRotateNodeCommand* End();
};

#endif // CROTATENODECOMMAND_H
