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
	virtual void mousePressEvent(QMouseEvent *event) = 0;
	virtual void mouseMoveEvent(QMouseEvent *event) = 0;
	virtual void mouseReleaseEvent(QMouseEvent *event) = 0;
	// virtual void prepareScene(RoomEditor* scene, ITool* tool) = 0;
};

#endif // ITOOL_H
