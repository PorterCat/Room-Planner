#ifndef GRIDPOINT_H
#define GRIDPOINT_H

#include <QGraphicsEllipseItem>
#include <QPen>

class GridPoint : public QGraphicsEllipseItem
{
  public:
	GridPoint(qreal x, qreal y, qreal size, QGraphicsItem* parent = nullptr);

	void hoverEnterEvent(QGraphicsSceneHoverEvent* event) override
	{
		setBrush(brush_);
		QGraphicsEllipseItem::hoverEnterEvent(event);
	}

	void hoverLeaveEvent(QGraphicsSceneHoverEvent* event) override
	{
		setBrush(QBrush(QColor(0, 0, 230, 0)));
		QGraphicsEllipseItem::hoverLeaveEvent(event);
	}

  private:
	QBrush brush_;
};

#endif // GRIDPOINT_H
