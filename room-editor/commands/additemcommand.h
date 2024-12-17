#ifndef ADDITEMCOMMAND_H
#define ADDITEMCOMMAND_H

#include "room-editor/commands/graphicsscenecommand.h"

class AddItemCommand : public GraphicsSceneCommand
{
public:
    AddItemCommand(QGraphicsScene* scene, QGraphicsItem* item, QUndoCommand* parent = nullptr)
        : GraphicsSceneCommand(scene, parent), item_(item)
    {
        setText("Add Item");
    }

    void undo() override
    {
        scene_->removeItem(item_);
    }

    void redo() override
    {
        scene_->addItem(item_);
    }

private:
    QGraphicsItem* item_;
};

#endif // ADDITEMCOMMAND_H
