#include "doortool.h"
#include <room-editor/zoomablegraphicsview.h>

DoorTool::DoorTool()
    : previewDoor_(nullptr), previewLine_(nullptr), perpendicularDirectionRight_(true)
{

}

DoorTool::~DoorTool()
{
}

void DoorTool::mousePressEvent(QMouseEvent* event, QWidget* sender) {}

void DoorTool::mouseMoveEvent(QMouseEvent* event, QWidget* sender)
{
	if (auto view = dynamic_cast<ZoomableGraphicsView*>(sender))
	{
		if (previewLine_)
		{
			view->scene()->removeItem(previewLine_);
			delete previewLine_;
			previewLine_ = nullptr;
		}

		QGraphicsItem* item = view->scene()->itemAt(view->mapToScene(event->pos()), QTransform());
		if (auto wall = dynamic_cast<REWall*>(item))
		{
            QRectF wallRect = wall->boundingRect();

            QPointF wallStart = QPointF(wall->get_x1(), wall->get_y1());
            QPointF wallEnd = QPointF(wall->get_x2(), wall->get_y2());

            QPointF mousePos = view->mapToScene(event->pos());

            QPointF wallVector = wallEnd - wallStart;

            QPointF perpendicularVector(wallVector.y() * (perpendicularDirectionRight_ ? 1 : -1), wallVector.x() * (perpendicularDirectionRight_ ? -1 : 1));

            qreal length = sqrt(perpendicularVector.x() * perpendicularVector.x() + perpendicularVector.y() * perpendicularVector.y());
            perpendicularVector /= length;

            qreal perpendicularLength = 50;

            QPointF perpendicularEnd = mousePos + perpendicularVector * perpendicularLength;

            previewLine_ = new QGraphicsLineItem(mousePos.x(), mousePos.y(), perpendicularEnd.x(), perpendicularEnd.y());
            view->scene()->addItem(previewLine_);
		}
	}
}

void DoorTool::mouseReleaseEvent(QMouseEvent* event, QWidget* sender) {}

void DoorTool::keyPressEvent(QKeyEvent* event, QWidget* sender)
{
    if (event->key() == Qt::Key_R)
    {
        perpendicularDirectionRight_ = !perpendicularDirectionRight_;
    }
}

void DoorTool::keyReleaseEvent(QKeyEvent* event, QWidget* sender)
{
}
