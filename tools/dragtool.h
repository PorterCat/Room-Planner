#ifndef DRAGTOOL_H
#define DRAGTOOL_H

#include "itool.h"
#include "room-editor/roomeditor.h"

// Why I need this class at all?

class DragTool : public ITool
{
  public:
	DragTool();
	~DragTool();
	void mousePressEvent(QMouseEvent* event, QWidget* sender) override;
	void mouseMoveEvent(QMouseEvent* event, QWidget* sender) override;
	void mouseReleaseEvent(QMouseEvent* event, QWidget* sender) override;
};

#endif // DRAGTOOL_H
