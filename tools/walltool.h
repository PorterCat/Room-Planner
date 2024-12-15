#ifndef WALLTOOL_H
#define WALLTOOL_H

#include "itool.h"

#include <QGraphicsView>

class WallTool : public ITool
{
  public:
	WallTool();
	~WallTool();
	void mousePressEvent(QMouseEvent *event) override;
	void mouseMoveEvent(QMouseEvent *event) override;
	void mouseReleaseEvent(QMouseEvent *event) override;

  private:
	QGraphicsScene *scene_;
	QGraphicsRectItem *previewWall_;
	//QPointF startPoint;
	//bool isDrawingWall_;

	//QPointF snapToGrid(const QPointF &point);
};

#endif // WALLTOOL_H
