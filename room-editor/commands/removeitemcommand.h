#ifndef REMOVEITEMCOMMAND_H
#define REMOVEITEMCOMMAND_H

#include "room-editor/commands/graphicsscenecommand.h"

class RemoveItemCommand : public GraphicsSceneCommand
{
public:
    RemoveItemCommand(QGraphicsScene* scene, QGraphicsItem* item, QUndoCommand* parent = nullptr)
        : GraphicsSceneCommand(scene, parent), item_(item)
    {
        setText("Remove Item");
    }

    void undo() override
    {
        scene_->addItem(item_);
    }

    void redo() override
    {
        scene_->removeItem(item_);
    }

private:
    QGraphicsItem* item_;
};

#endif // REMOVEITEMCOMMAND_H
