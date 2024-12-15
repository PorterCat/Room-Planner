#ifndef DRAGTOOL_H
#define DRAGTOOL_H

#include "itool.h"

class DragTool : public ITool
{
  public:
	DragTool();
	~DragTool();
	void mousePressEvent(QMouseEvent *event) override;
	void mouseMoveEvent(QMouseEvent *event) override;
	void mouseReleaseEvent(QMouseEvent *event) override;
};

#endif // DRAGTOOL_H
