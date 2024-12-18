#ifndef ZOOMABLEGRAPHICSVIEW_H
#define ZOOMABLEGRAPHICSVIEW_H

#include <QWidget>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QVBoxLayout>
#include <QPen>
#include <QBrush>
#include <QWheelEvent>
#include <QLabel>
#include <QTimer>
#include <QTransform>

#include "actiongraphicsscene.h"
#include <tools/ikeytool.h>

class ZoomableGraphicsView : public QGraphicsView
{
	Q_OBJECT

  public:
    ZoomableGraphicsView(ActionGraphicsScene* scene, ITool* tool, QWidget* parent = nullptr)
		: QGraphicsView(scene, parent), currentScale(1.0), currentTool_(tool), scene_(scene)
	{
        this->setMouseTracking(true);
	}

	ActionGraphicsScene* scene() const { return scene_; }

	void setZoomLevel(double scaleFactor)
	{
		if (scaleFactor > maxScale) {
			scaleFactor = maxScale;
		}
		currentScale = scaleFactor;
		setTransform(QTransform::fromScale(currentScale, currentScale));
		emit zoomChanged();
	}

	void setCurrentTool(ITool* tool)
	{
		currentTool_ = tool;
	}

  protected:
	void wheelEvent(QWheelEvent* event) override
	{
		QPoint numDegrees = event->angleDelta() / 8;
		if (!numDegrees.isNull()) {
			QPoint numSteps = numDegrees / 15;
			if (numSteps.y() > 0) {
				scale(1.1, 1.1);
			} else if (numSteps.y() < 0) {
				scale(0.9, 0.9);
			}

			currentScale *= (numSteps.y() > 0) ? 1.1 : 0.9;

			if (currentScale > maxScale) {
				currentScale = maxScale;
				setTransform(QTransform::fromScale(maxScale, maxScale));
			}

			emit zoomChanged();
		}
		event->accept();
	}

	void mouseMoveEvent(QMouseEvent* event) override 
	{
		if (auto tool = dynamic_cast<ITool*>(currentTool_))
		{
			tool->mouseMoveEvent(event, this);
		}
		QGraphicsView::mouseMoveEvent(event);
	}

	void mousePressEvent(QMouseEvent* event) override 
	{
		if (auto tool = dynamic_cast<ITool*>(currentTool_))
		{
			tool->mousePressEvent(event, this);
		}
		QGraphicsView::mousePressEvent(event);
	}

	void mouseReleaseEvent(QMouseEvent* event) override 
	{
		if (auto tool = dynamic_cast<ITool*>(currentTool_))
		{
			tool->mouseReleaseEvent(event, this);
		}
		QGraphicsView::mouseReleaseEvent(event);
	}

	void keyPressEvent(QKeyEvent* event) override
	{
		if (auto tool = dynamic_cast<IKeyTool*>(currentTool_))
		{
			tool->keyPressEvent(event, this);
		}
		QGraphicsView::keyPressEvent(event);
	}

	void keyReleaseEvent(QKeyEvent* event) override
	{
		if (auto tool = dynamic_cast<IKeyTool*>(currentTool_))
		{
			tool->keyReleaseEvent(event, this);
		}
		QGraphicsView::keyReleaseEvent(event);
	}

  signals:
	void zoomChanged();

  private:
	double currentScale;
	static constexpr double maxScale = 5.0;

	ActionGraphicsScene* scene_;

	ITool* currentTool_;
};

#endif // ZOOMABLEGRAPHICSVIEW_H
