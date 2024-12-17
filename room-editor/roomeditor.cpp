#include "roomeditor.h"

#include <QActionGroup>
#include <QGraphicsLineItem>
#include <QObject>

#include "mainwindow.h"
#include "room-editor/interactive-point/gridpoint.h"
#include "tools/dragtool.h"
#include "tools/walltool.h"

constexpr qreal LineSize = 25.0;

constexpr qreal DotSize = LineSize / 2.0;

constexpr int LineBrightness = 64;

RoomEditor::RoomEditor(int gridWidth, int gridHeight, QWidget *parent, MainWindow* mainWindow)
    : QWidget(parent), scene_(new ActionGraphicsScene(this)), mainWindow_(mainWindow)
{
	scene_->setBackgroundBrush(Qt::white);
	// scene->setSceneRect(0, 0, 1000, 1000); For more space and better dragging mode to do
	scene_->setItemIndexMethod(QGraphicsScene::NoIndex);

	view_ = new ZoomableGraphicsView(scene_, currentTool_, this);
	view_->setMouseTracking(true);
	//setMouseTracking(true);

	view_->setRenderHint(QPainter::Antialiasing);
	view_->setTransformationAnchor(QGraphicsView::AnchorUnderMouse);

	view_->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	view_->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

	setLayout(new QVBoxLayout);
	layout()->addWidget(view_);

	zoomLabel = new PopupLabel(this, 1000);
	zoomLabel->setStyleSheet("background-color: rgba(0, 0, 0, 128); color: white; padding: 5px;");
	zoomLabel->setAlignment(Qt::AlignCenter);
	zoomLabel->hide();
	zoomLabel->move(10, 10);

	infoLabel = new PopupLabel(this, 1000);
    infoLabel->setStyleSheet("background-color: rgba(0, 0, 0, 128); color: white; padding: 5px;");
    infoLabel->setAlignment(Qt::AlignCenter);
	infoLabel->hide();
	infoLabel->move(10, 50);

	connect(view_, &ZoomableGraphicsView::zoomChanged, this, &RoomEditor::onZoomChanged);
	connect(zoomLabel, &PopupLabel::clicked, this, &RoomEditor::onZoomLabelClicked);
	connect(mainWindow_, &MainWindow::currentToolChanged, this, &RoomEditor::onCurrentToolChanged);

	interactingGrid_ = new InteractingGrid(scene_, gridWidth, gridHeight);

	currentTool_ = mainWindow->currentTool();
	if (dynamic_cast<DragTool*>(currentTool_))
		setDragMode(true);
	view_->setCurrentTool(currentTool_);

	this->drawGrid();
}

void RoomEditor::drawGrid()
{
	scene_->clear();

	QPen linesPen(QColor(LineBrightness, LineBrightness, LineBrightness, 100));

	for (int i = 0; i <= interactingGrid_->getWidth(); ++i)
		scene_->addLine(i * LineSize, 0, i * LineSize, interactingGrid_->getHeight() * LineSize, linesPen);
	for (int i = 0; i <= interactingGrid_->getHeight(); ++i)
		scene_->addLine(0, i * LineSize, interactingGrid_->getWidth() * LineSize, i * LineSize, linesPen);

	interactingGrid_->setUpGridPoints(LineSize, DotSize);
}

#pragma region ZoomView

void RoomEditor::setZoomLevel(int zoomPercentage)
{
	qreal scaleFactor = zoomPercentage / 100.0;
	view_->setZoomLevel(scaleFactor);
	showZoomLevel();
}

void RoomEditor::showZoomLevel()
{
	qreal scaleFactor = view_->transform().m11();
	int zoomPercentage = qRound(scaleFactor * 100);
	zoomLabel->setText(QString("Zoom: %1%").arg(zoomPercentage));
	zoomLabel->adjustSize();
	zoomLabel->move(10, 10);
	zoomLabel->showWithTimer();
}

void RoomEditor::onZoomLabelClicked()
{
	bool ok;
	int newZoom = QInputDialog::getInt(this, "Set Zoom Level", "Enter zoom percentage:", 100, 10, 500, 10, &ok);

	if (ok)
		setZoomLevel(newZoom);
}

void RoomEditor::onZoomChanged() { showZoomLevel(); }

#pragma endregion

#pragma region Tools

void RoomEditor::mouseMoveEvent(QMouseEvent* event) 
{ 
	currentTool_->mouseMoveEvent(event, this); 
}

void RoomEditor::mousePressEvent(QMouseEvent* event) 
{ 
	currentTool_->mousePressEvent(event, this); 
}

void RoomEditor::mouseReleaseEvent(QMouseEvent* event) 
{ 
	currentTool_->mouseReleaseEvent(event, this); 
}

void RoomEditor::setDragMode(bool choice)
{
	if (choice) view_->setDragMode(QGraphicsView::ScrollHandDrag);
	else view_->setDragMode(QGraphicsView::NoDrag);
}

void RoomEditor::setSelectPointsMode(bool choice) 
{ 
	interactingGrid_->setInteractive(choice);
}

// Problems with timer duration: I made it custom but I considered it nowhere
void RoomEditor::writeInfoLabel(const QString string)
{
	infoLabel->setText(string);
	infoLabel->adjustSize();
	infoLabel->showWithTimer();
}

// Complete it
void RoomEditor::writeErrorLabel(const QString)
{
	errorLabel->adjustSize();
}

void RoomEditor::onCurrentToolChanged(ITool* newTool)
{
	currentTool_ = newTool;
	view_->setCurrentTool(newTool);

	if (dynamic_cast<WallTool*>(newTool))
	{
		writeInfoLabel("Стены");
	}
	else if (dynamic_cast<DragTool*>(newTool))
	{
		writeInfoLabel("Перетаскивание");
	}
}

#pragma endregion

RoomEditor::~RoomEditor() {}
