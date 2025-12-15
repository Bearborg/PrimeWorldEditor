#ifndef CSELECTNODECOMMAND_H
#define CSELECTNODECOMMAND_H

#include "Editor/Undo/IUndoCommand.h"
#include "Editor/Undo/ObjReferences.h"

#include <Core/Scene/CSceneNode.h>

#include <QCoreApplication>

class CSelectNodeCommand : public IUndoCommand
{
    CNodePtr mpNode;
    CNodeSelection *mpSelection;

public:
    CSelectNodeCommand(CNodeSelection *pSelection, CSceneNode *pNode)
        : IUndoCommand(QCoreApplication::translate("CSelectNodeCommand", "Select"))
        , mpNode(pNode)
        , mpSelection(pSelection)
    {}

    void undo() override { mpSelection->DeselectNode(*mpNode); }
    void redo() override { mpSelection->SelectNode(*mpNode); }
    bool AffectsCleanState() const override { return false; }
};

#endif // CSELECTNODECOMMAND_H
