#ifndef WALLTOOL_H
#define WALLTOOL_H

#include "itool.h"

#include <QGraphicsScene>

class WallTool : public ITool
{
  public:
	WallTool();
	~WallTool();
	void mousePressEvent(QMouseEvent *event) override;
	void mouseMoveEvent(QMouseEvent *event) override;
	void mouseReleaseEvent(QMouseEvent *event) override;

  private:
	QGraphicsScene *scene;
	QGraphicsLineItem *previewWall;
	QPointF startPoint;
	bool isDrawingWall;

	QPointF snapToGrid(const QPointF &point);
};

#endif // WALLTOOL_H
