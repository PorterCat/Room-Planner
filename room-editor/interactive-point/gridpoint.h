﻿#ifndef GRIDPOINT_H
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
		setBrush(transparentBrush_);
		QGraphicsEllipseItem::hoverLeaveEvent(event);
	}

	void hoverMode(bool choice)
	{
		setAcceptHoverEvents(choice);
	}

	void colorIt() { setBrush(brush_); }
	void transparentIt() { setBrush(transparentBrush_); }

	QPointF getRealPoint() { return QPointF{ x_, y_ }; }
	qreal getX() { return x_; }
	qreal getY() { return y_; }
	qreal getSize() { return size_; }

	static qreal calculateDistance(GridPoint* start, GridPoint* end)
	{
		qreal dx = end->getX() - start->getX();
		qreal dy = end->getY() - start->getY();
		return qSqrt(dx * dx + dy * dy);
	}

  private:
	const QBrush transparentBrush_ = QBrush(QColor(0, 0, 230, 0));

	QBrush brush_;
	qreal x_;
	qreal y_;
	qreal size_;
};

#endif // GRIDPOINT_H
