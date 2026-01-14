#ifndef CTRANSLATENODECOMMAND_H
#define CTRANSLATENODECOMMAND_H

#include "Editor/Undo/IUndoCommand.h"
#include "Editor/Undo/ObjReferences.h"

#include <QList>
#include <span>

class CSceneNode;
class CVector3f;
class INodeEditor;

class CTranslateNodeCommand : public IUndoCommand
{
    struct SNodeTranslate;

    QList<SNodeTranslate> mNodeList;
    INodeEditor *mpEditor = nullptr;
    bool mCommandEnded = false;

public:
    CTranslateNodeCommand();
    CTranslateNodeCommand(INodeEditor *pEditor, std::span<CSceneNode*> nodes, const CVector3f& rkDelta, ETransformSpace TransformSpace);
    ~CTranslateNodeCommand() override;

    int id() const override;
    bool mergeWith(const QUndoCommand *pkOther) override;
    void undo() override;
    void redo() override;
    bool AffectsCleanState() const override { return true; }
    static CTranslateNodeCommand* End();
};

#endif // CTRANSLATENODECOMMAND_H
