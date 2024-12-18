#ifndef ACTIONGRAPHICSSCENE_H
#define ACTIONGRAPHICSSCENE_H

#include <QGraphicsScene>
#include <QUndoStack>

#include "room-editor/commands/additemcommand.h"
#include "room-editor/commands/removeitemcommand.h"

class ActionGraphicsScene : public QGraphicsScene
{
public:
    explicit ActionGraphicsScene(QObject *parent = nullptr)
        : QGraphicsScene(parent), undoStack_(new QUndoStack(this)) {}
        
    void addItemWithUndo(QGraphicsItem* item)
    {
        undoStack_->push(new AddItemCommand(this, item));
    }

    void removeItemWithUndo(QGraphicsItem* item)
    {
        undoStack_->push(new RemoveItemCommand(this, item));
    }

    QUndoStack* undoStack() const { return undoStack_; }

private:
    QUndoStack* undoStack_;
};

#endif // ACTIONGRAPHICSSCENE_H
