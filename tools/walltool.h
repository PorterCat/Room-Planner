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
	void mousePressEvent(QMouseEvent* event, QWidget* sender) override;
	void mouseMoveEvent(QMouseEvent* event, QWidget* sender) override;
	void mouseReleaseEvent(QMouseEvent* event, QWidget* sender) override;

  private:
	// QGraphicsScene *scene_;
	QGraphicsLineItem *previewWall_;
	QGraphicsTextItem *distanceText_;

	GridPoint *startPoint_;
	bool isDrawingWall_;

	//QPointF snapToGrid(const QPointF &point);
};

#endif // WALLTOOL_H
