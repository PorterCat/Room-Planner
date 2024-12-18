#ifndef REWALL_H
#define REWALL_H

#include <QGraphicsItem>
#include "iroomeditorobject.h"

class REWall : public QGraphicsLineItem, public virtual IRoomEditorObject
{
public:
    REWall(qreal x1, qreal y1, qreal x2, qreal y2, const QColor& color = Qt::black);

    int type() const override { return REWallType; }
    QString typeName() const override { return "REWall"; }

    QJsonObject toJson() const override
    {
        QJsonObject json;
        json["type"] = typeName();
        json["x1"] = line().x1();
        json["y1"] = line().y1();
        json["x2"] = line().x2();
        json["y2"] = line().y2();

        return json;
    }

    static REWall* fromJson(const QJsonObject& json)
    {
        qreal x1 = json["x1"].toDouble();
        qreal y1 = json["y1"].toDouble();
        qreal x2 = json["x2"].toDouble();
        qreal y2 = json["y2"].toDouble();

        return new REWall(x1, y1, x2, y2);
    }
};

#endif // REWALL_H
