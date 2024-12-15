#ifndef ROOMEDITOR_H
#define ROOMEDITOR_H

#include <QWidget>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QVBoxLayout>
#include <QWheelEvent>
#include <QLabel>
#include <QTimer>
#include <QTransform>
#include <QInputDialog>

#include "popuplabel.h"
#include "zoomablegraphicsview.h"
#include "tools/itool.h"

class RoomEditor : public QWidget
{
	Q_OBJECT

  public:
	explicit RoomEditor(int gridWidth, int gridHeight, QWidget *parent = nullptr);
	void setGridSize(int width, int height);
	~RoomEditor();

	void setCurrentTool(ITool* tool) {currentTool_ = tool; }

  private:
	QGraphicsScene *scene;
	ZoomableGraphicsView *view;
	int gridWidth_;
	int gridHeight_;
	ITool *currentTool_;

	void drawGrid();

	PopupLabel *zoomLabel;
	PopupLabel *errorLabel;

	void showZoomLevel();
	void setZoomLevel(int zoomPercentage);

  private slots:
	void onZoomChanged();
	void onZoomLabelClicked();
};

#endif // ROOMEDITOR_H
