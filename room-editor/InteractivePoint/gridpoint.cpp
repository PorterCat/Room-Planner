#include "gridpoint.h"

GridPoint::GridPoint(qreal x, qreal y, qreal size, QGraphicsItem* parent)
	: QGraphicsEllipseItem(x, y, size, size, parent)
{
	brush_ = QBrush(QColor(0, 0, 230, 255));
	setPen(QPen(Qt::NoPen));
	setBrush(QBrush(QColor(0, 0, 230, 0)));
	setAcceptHoverEvents(true);
}