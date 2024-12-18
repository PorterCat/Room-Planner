#include "redoor.h"
#include <qpainter.h>

REDoor::REDoor(REWall* wall, qreal x, qreal y, qreal width, qreal height, DoorDirection direction, const QColor& color)
    : QGraphicsItem(), wall_(wall), direction_(direction), width_(width), height_(height)
{
    setPos(x, y);
}

QJsonObject REDoor::toJson() const
{
    QJsonObject json;
    json["type"] = typeName();
    json["x"] = pos().x();
    json["y"] = pos().y();
    json["width"] = width_;
    json["height"] = height_;
    json["direction"] = direction_;
    return json;
}

REDoor* REDoor::fromJson(const QJsonObject& json, REWall* wall)
{
    qreal x = json["x"].toDouble();
    qreal y = json["y"].toDouble();
    qreal width = json["width"].toDouble();
    qreal height = json["height"].toDouble();
    DoorDirection direction = static_cast<DoorDirection>(json["direction"].toInt());

    return new REDoor(wall, x, y, width, height, direction);
}

void REDoor::setDirection(DoorDirection direction)
{
    direction_ = direction;
    update();
}

QRectF REDoor::boundingRect() const
{
    return QRectF(0, 0, width_, height_);
}

void REDoor::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
    QPen pen(Qt::black, 2);
    painter->setPen(pen);

    //painter->drawLine(startPoint_, endPoint_);
}
