#include "walltool.h"

#include "room-editor/scene-objects/rewall.h"

WallTool::WallTool() :
	isDrawingWall_(false), previewWall_(nullptr), distanceText_(nullptr), startPoint_(nullptr)
{

}

void WallTool::mouseMoveEvent(QMouseEvent* event, QWidget* sender)
{
	if (auto view = dynamic_cast<ZoomableGraphicsView*>(sender))
	{
		if (isDrawingWall_)
		{
			if (previewWall_)
			{
				view->scene()->removeItem(previewWall_);
				delete previewWall_;
				previewWall_ = nullptr;
			}

			if (distanceText_)
			{
				view->scene()->removeItem(distanceText_);
				delete distanceText_;
				distanceText_ = nullptr;
			}

			QGraphicsItem* item = view->scene()->itemAt(view->mapToScene(event->pos()), QTransform());
			if (auto gridPoint = dynamic_cast<GridPoint*>(item))
			{
				previewWall_ = new QGraphicsLineItem(startPoint_->getX() + startPoint_->getSize()/2, 
					startPoint_->getY() + startPoint_->getSize() / 2,
					gridPoint->getX() + startPoint_->getSize() / 2, gridPoint->getY() + gridPoint->getSize() / 2);
				previewWall_->setPen(QPen(Qt::gray, 5));
				view->scene()->addItem(previewWall_);

				qreal distance = GridPoint::calculateDistance(startPoint_, gridPoint);
				distanceText_ = new QGraphicsTextItem(QString::number(distance/100, 'f', 2) + " m");
				distanceText_->setDefaultTextColor(Qt::black);
				distanceText_->setPos(gridPoint->getX(), gridPoint->getY() - 20);
				distanceText_->setZValue(120);
				view->scene()->addItem(distanceText_);
			}
		}
	}
}

void WallTool::mousePressEvent(QMouseEvent* event, QWidget* sender)
{
	if (auto view = dynamic_cast<ZoomableGraphicsView*>(sender))
	{
		QGraphicsItem* item = view->scene()->itemAt(view->mapToScene(event->pos()), QTransform());
		if (auto gridPoint = dynamic_cast<GridPoint*>(item))
		{
			if (isDrawingWall_ && startPoint_ != nullptr)
			{
				startPoint_->hoverMode(true);
				startPoint_->transparentIt();

				isDrawingWall_ = false;

				view->scene()->addItemWithUndo(new REWall(startPoint_->getX() + startPoint_->getSize() / 2,
					startPoint_->getY() + startPoint_->getSize() / 2,
					gridPoint->getX() + startPoint_->getSize() / 2, gridPoint->getY() + gridPoint->getSize() / 2));

				if (previewWall_)
				{
					view->scene()->removeItem(previewWall_);
					delete previewWall_;
					previewWall_ = nullptr;
				}

				if (distanceText_)
				{
					view->scene()->removeItem(distanceText_);
					delete distanceText_;
					distanceText_ = nullptr;
				}
			}
			else
			{
				gridPoint->hoverMode(false);
				startPoint_ = gridPoint;
				isDrawingWall_ = true;
			}
		}
	}
}

void WallTool::mouseReleaseEvent(QMouseEvent* event, QWidget* sender) {}

WallTool::~WallTool()
{
	if (previewWall_)
		delete previewWall_;
}
