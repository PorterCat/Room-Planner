#ifndef ITOOL_H
#define ITOOL_H

#include <QObject>
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QMouseEvent>

class RoomEditor;

class ITool : public QObject
{
	Q_OBJECT
  public:
	virtual ~ITool() {}
	virtual void mousePressEvent(QMouseEvent* event, RoomEditor* sender) = 0;
	virtual void mouseMoveEvent(QMouseEvent* event, RoomEditor* sender) = 0;
	virtual void mouseReleaseEvent(QMouseEvent* event, RoomEditor* sender) = 0;
};

#endif // ITOOL_H
