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

class ZoomableGraphicsView : public QGraphicsView
{
	Q_OBJECT

  public:
	ZoomableGraphicsView(QGraphicsScene* scene, QWidget* parent = nullptr)
		: QGraphicsView(scene, parent), currentScale(1.0) // Инициализируем масштаб как 100%
	{
	}

	void setZoomLevel(double scaleFactor)
	{
		if (scaleFactor > maxScale) {
			scaleFactor = maxScale;
		}
		currentScale = scaleFactor;
		setTransform(QTransform::fromScale(currentScale, currentScale));
		emit zoomChanged();
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

  signals:
	void zoomChanged();

  private:
	double currentScale;
	static constexpr double maxScale = 5.0;
};

#endif // ZOOMABLEGRAPHICSVIEW_H
