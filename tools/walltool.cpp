#include "walltool.h"

WallTool::WallTool() {}

void WallTool::mouseMoveEvent(QMouseEvent* event)
{
	// QPointF scenePos = scene_->views().first()->mapToScene(event->pos());

	// if (!previewWall_) {
	// 	previewWall_ = new QGraphicsRectItem(-25, -25, 50, 50);
	// 	previewWall_->setPen(QPen(Qt::black, 2));
	// 	previewWall_->setBrush(QBrush(Qt::lightGray, Qt::Dense4Pattern));
	// 	scene_->addItem(previewWall_);
	// }

	// previewWall_->setPos(scenePos.x() - 25, scenePos.y() - 25);
}

void WallTool::mousePressEvent(QMouseEvent* event)
{
	// if (event->button() == Qt::LeftButton) {
	// 	QPointF scenePos = scene_->views().first()->mapToScene(event->pos());

	// 		   // Создаем новый квадрат и добавляем его на сцену
	// 	QGraphicsRectItem* square = new QGraphicsRectItem(scenePos.x() - 25, scenePos.y() - 25, 50, 50);
	// 	square->setPen(QPen(Qt::black, 2));
	// 	square->setBrush(QBrush(Qt::lightGray));
	// 	scene_->addItem(square);

	// 		   // Удаляем предпоказ
	// 	if (previewWall_) {
	// 		scene_->removeItem(previewWall_);
	// 		delete previewWall_;
	// 		previewWall_ = nullptr;
	// 	}
	// }
}

void WallTool::mouseReleaseEvent(QMouseEvent* event)
{

}

WallTool::~WallTool()
{
	if (previewWall_) {
		delete previewWall_;
	}
}
