#ifndef WALLTOOL_H
#define WALLTOOL_H

#include "itool.h"
#include "room-editor/roomeditor.h"

#include <QGraphicsView>

class WallTool : public ITool
{
  public:
	WallTool();
	~WallTool();
	void mousePressEvent(QMouseEvent* event, RoomEditor* sender) override;
	void mouseMoveEvent(QMouseEvent* event, RoomEditor* sender) override;
	void mouseReleaseEvent(QMouseEvent* event, RoomEditor* sender) override;

  private:
	QGraphicsScene *scene_;
	QGraphicsRectItem *previewWall_;
	//QPointF startPoint;
	//bool isDrawingWall_;

	//QPointF snapToGrid(const QPointF &point);
};

#endif // WALLTOOL_H
