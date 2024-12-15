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

#include "mainwindow.h"
#include "popuplabel.h"
#include "zoomablegraphicsview.h"
#include "tools/itool.h"

class RoomEditor : public QWidget
{
	Q_OBJECT

  public:
	explicit RoomEditor(int gridWidth, int gridHeight, QWidget *parent = nullptr, MainWindow* mainWindow = nullptr);
	void setGridSize(int width, int height);
	~RoomEditor();

	void setCurrentTool(ITool* tool) {currentTool_ = tool; }

  protected:
	void mouseMoveEvent(QMouseEvent* event) override;
	void mouseReleaseEvent(QMouseEvent* event) override;
	void mousePressEvent(QMouseEvent* event) override;

  private:
	QGraphicsScene *scene;
	ZoomableGraphicsView *view;
	int gridWidth_;
	int gridHeight_;
	ITool *currentTool_;

	void drawGrid();

	PopupLabel *zoomLabel;
	PopupLabel *infoLabel;
	PopupLabel *errorLabel;

	void showZoomLevel();
	void setZoomLevel(int zoomPercentage);

	MainWindow* mainWindow_;

  private slots:
	void onZoomChanged();
	void onZoomLabelClicked();
	void onCurrentToolChanged(ITool* newTool);
};

#endif // ROOMEDITOR_H
