#include "gridpoint.h"

GridPoint::GridPoint(qreal x, qreal y, qreal size, QGraphicsItem* parent)
	: QGraphicsEllipseItem(x, y, size, size, parent), x_(x), y_(y), size_(size)
{
	brush_ = QBrush(QColor(0, 0, 230, 255));
	setPen(QPen(Qt::NoPen));
	setBrush(transparentBrush_);
	setAcceptHoverEvents(false);
}
