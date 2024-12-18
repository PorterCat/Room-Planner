#ifndef REDOOR_H
#define REDOOR_H

#include <QGraphicsItem>

#include "iroomeditorobject.h"
#include "room-editor/scene-objects/rewall.h"

class REDoor : public QGraphicsItem, public virtual IRoomEditorObject
{
public:
    enum DoorDirection {
        DirectionOutward,
        DirectionInward,
        DirectionLeft,
        DirectionRight
    };

    REDoor(REWall* wall, qreal x, qreal y, qreal width, qreal height, DoorDirection direction, const QColor& color = Qt::blue);

    int type() const override { return REDoorType; }
    QString typeName() const override { return "REDoor"; }

    QJsonObject toJson() const override;
    static REDoor* fromJson(const QJsonObject& json, REWall* wall);

    DoorDirection direction() const { return direction_; }
    void setDirection(DoorDirection direction);

protected:
    QRectF boundingRect() const override;
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;

private:
    REWall* wall_;
    DoorDirection direction_;
    qreal width_;
    qreal height_;
};

#endif // REDOOR_H
