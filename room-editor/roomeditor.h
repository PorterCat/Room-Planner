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
#include "room-editor/actiongraphicsscene.h"
#include "zoomablegraphicsview.h"
#include "tools/itool.h"
#include "interactive-point/interactinggrid.h"
#include "room-editor//scene-objects/roomeditorobject.h"

class RoomEditor : public QWidget
{
	Q_OBJECT

  public:
	explicit RoomEditor(int gridWidth, int gridHeight, QWidget *parent = nullptr, MainWindow* mainWindow = nullptr);
	~RoomEditor();

	//tools
	void setCurrentTool(ITool* tool) {currentTool_ = tool; }
	void setDragMode(bool);
	void setSelectPointsMode(bool);

	ITool* getCurrentTool() { return currentTool_; }

	void writeInfoLabel(const QString);
	void writeErrorLabel(const QString);

    ActionGraphicsScene* getScene() { return scene_; }
	ZoomableGraphicsView* getView() { return view_; }

  protected:
	void mouseMoveEvent(QMouseEvent* event) override;
	void mouseReleaseEvent(QMouseEvent* event) override;
	void mousePressEvent(QMouseEvent* event) override;

  private:
    ActionGraphicsScene *scene_;
	ZoomableGraphicsView *view_;
	ITool *currentTool_;

	void drawGrid();

	//information 
	PopupLabel *zoomLabel;
	PopupLabel *infoLabel;
	PopupLabel *errorLabel;

	void showZoomLevel();
	void setZoomLevel(int zoomPercentage);

	MainWindow* mainWindow_;

	InteractingGrid* interactingGrid_;

	QVector<RoomEditorObject*> roomEditorObjects;

  private slots:
	void onZoomChanged();
	void onZoomLabelClicked();
	void onCurrentToolChanged(ITool* newTool);
};

#endif // ROOMEDITOR_H
