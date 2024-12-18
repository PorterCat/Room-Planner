#include "rewall.h"
#include <room-editor/interactive-point/gridpoint.h>

REWall::REWall(qreal x1, qreal y1, qreal x2, qreal y2, const QColor& color)
    : QGraphicsLineItem(x1, y1, x2, y2)
{
    setPen(QPen(color, 5));
}
