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
	ZoomableGraphicsView(QGraphicsScene *scene, QWidget *parent = nullptr) : QGraphicsView(scene, parent) {}

  protected:
	void wheelEvent(QWheelEvent *event) override
	{
		QPoint numDegrees = event->angleDelta() / 8;
		if (!numDegrees.isNull()) {
			QPoint numSteps = numDegrees / 15;
			if (numSteps.y() > 0) {
				scale(1.1, 1.1);
			} else if (numSteps.y() < 0) {
				scale(0.9, 0.9);
			}
			emit zoomChanged();
		}
		event->accept();
	}
  public:
  signals:
	void zoomChanged();
};

#endif // ZOOMABLEGRAPHICSVIEW_H
