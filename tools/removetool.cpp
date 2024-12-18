#include "removetool.h"

#include "room-editor/scene-objects/iroomeditorobject.h"
#include "room-editor/zoomablegraphicsview.h"

RemoveTool::RemoveTool() {}

RemoveTool::~RemoveTool()
{
}

void RemoveTool::mousePressEvent(QMouseEvent* event, QWidget* sender)
{
	if (auto view = dynamic_cast<ZoomableGraphicsView*>(sender))
	{
		QGraphicsItem* item = view->scene()->itemAt(view->mapToScene(event->pos()), QTransform());
		if (auto reObject = dynamic_cast<IRoomEditorObject*>(item))
		{
			view->scene()->removeItemWithUndo(dynamic_cast<QGraphicsItem*>(reObject));
		}
	}
}

void RemoveTool::mouseMoveEvent(QMouseEvent* event, QWidget* sender)
{
}

void RemoveTool::mouseReleaseEvent(QMouseEvent* event, QWidget* sender)
{
}
