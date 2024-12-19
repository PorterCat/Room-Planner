#include "doortool.h"
#include <room-editor/zoomablegraphicsview.h>

DoorTool::DoorTool()
    : previewDoor_(nullptr), previewLine_(nullptr), perpendicularDirectionRight_(true)
{

}

DoorTool::~DoorTool()
{
	if (previewLine_)
		delete previewLine_;
    if (previewDoor_)
        delete previewDoor_;
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

		if (previewDoor_)
		{
			view->scene()->removeItem(previewDoor_);
			delete previewDoor_;
			previewDoor_ = nullptr;
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
            previewLine_->setPen(QPen(Qt::gray, 5));
            view->scene()->addItem(previewLine_);

            qreal doorWidth = 80; // Ширина двери (перпендикулярно перпендикуляру)
            qreal doorThickness = 10; // Толщина двери (вдоль стены)

            // Определяем направление двери относительно перпендикуляра
            QPointF doorDirectionVector = perpendicularVector * (doorDirectionRight_ ? 1 : -1);

            // Вычисляем точки для прямоугольника двери
            QPointF doorStart = mousePos - doorDirectionVector * (doorWidth / 2);
            QPointF doorEnd = mousePos + doorDirectionVector * (doorWidth / 2);

            // Вычисляем нормализованный вектор стены
            qreal wallVectorLength = sqrt(wallVector.x() * wallVector.x() + wallVector.y() * wallVector.y());
            QPointF wallNormal(wallVector.y() / wallVectorLength, -wallVector.x() / wallVectorLength);

            // Вычисляем точки для прямоугольника двери
            QPointF doorTopLeft = doorStart - wallNormal * (doorThickness / 2);
            QPointF doorBottomRight = doorEnd + wallNormal * (doorThickness / 2);

            QRectF doorRect(doorTopLeft, doorBottomRight);

            previewDoor_ = new QGraphicsRectItem(doorRect);
            previewDoor_->setPen(QPen(Qt::black));
            previewDoor_->setBrush(QBrush(Qt::gray));
            //view->scene()->addItem(previewDoor_);
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
