#ifndef GRAPHICSSCENECOMMAND_H
#define GRAPHICSSCENECOMMAND_H

#include <QUndoCommand>
#include <QGraphicsScene>

class GraphicsSceneCommand : public QUndoCommand
{
public:
    GraphicsSceneCommand(QGraphicsScene* scene, QUndoCommand* parent = nullptr)
        : QUndoCommand(parent), scene_(scene) {}

protected:
    QGraphicsScene* scene_;
};

#endif // GRAPHICSSCENECOMMAND_H
