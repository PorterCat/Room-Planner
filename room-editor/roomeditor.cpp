#include "roomeditor.h"

#include <QActionGroup>
#include <QGraphicsLineItem>

#include "mainwindow.h"
#include "room-editor/InteractivePoint/gridpoint.h"

RoomEditor::RoomEditor(int gridWidth, int gridHeight, QWidget *parent, MainWindow* mainWindow)
	: QWidget(parent), gridWidth_(gridWidth), gridHeight_(gridHeight), mainWindow_(mainWindow)
{
	scene = new QGraphicsScene(this);
	scene->setBackgroundBrush(Qt::white);
	// scene->setSceneRect(0, 0, 1000, 1000); For more space and better dragging mode to do
	scene->setItemIndexMethod(QGraphicsScene::NoIndex);

	view = new ZoomableGraphicsView(scene, this);
	view->setMouseTracking(true);

	view->setRenderHint(QPainter::Antialiasing);
	view->setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
	// view->setDragMode(QGraphicsView::ScrollHandDrag); TODO: make it with DragTool

	view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

	setLayout(new QVBoxLayout);
	layout()->addWidget(view);

	zoomLabel = new PopupLabel(this, 5000);
	zoomLabel->setStyleSheet("background-color: rgba(0, 0, 0, 128); color: white; padding: 5px;");
	zoomLabel->setAlignment(Qt::AlignCenter);
	zoomLabel->hide();

	infoLabel = new PopupLabel(this, 5000);
	infoLabel->setStyleSheet("background-color: rgba(0, 0, 0, 128); color: blue; padding: 5px;");
	infoLabel->setAlignment(Qt::AlignBottom);
	infoLabel->hide();

	connect(view, &ZoomableGraphicsView::zoomChanged, this, &RoomEditor::onZoomChanged);
	connect(zoomLabel, &PopupLabel::clicked, this, &RoomEditor::onZoomLabelClicked);
	connect(mainWindow_, &MainWindow::currentToolChanged, this, &RoomEditor::onCurrentToolChanged);

	currentTool_ = mainWindow->currentTool();

	this->drawGrid();
}

void RoomEditor::onZoomLabelClicked()
{
	bool ok;
	int newZoom = QInputDialog::getInt(this, "Set Zoom Level", "Enter zoom percentage:", 100, 10, 500, 10, &ok);
	if (ok) {
		setZoomLevel(newZoom);
	}
}

constexpr double LineSize = 25.0;

constexpr double DotSize = LineSize / 3.0;
constexpr double HalfDotSize = DotSize / 2.0;

constexpr int LineBrightness = 64;

void RoomEditor::setGridSize(int width, int height)
{
	gridWidth_ = width;
	gridHeight_ = height;
	drawGrid();
}

void RoomEditor::drawGrid()
{
	scene->clear();

	QPen linesPen(QColor(LineBrightness, LineBrightness, LineBrightness, 100));
	QPen dotsPen(QColor(0, 0, 230, 255));

	for (int i = 0; i <= gridWidth_; ++i)
	{
		scene->addLine(i * LineSize, 0, i * LineSize, gridHeight_ * LineSize, linesPen);
	}
	for (int i = 0; i <= gridHeight_; ++i)
	{
		scene->addLine(0, i * LineSize, gridWidth_ * LineSize, i * LineSize, linesPen);
	}

	for (int x = 0; x < gridWidth_ + 1; ++x)
	{
		for (int y = 0; y < gridHeight_ + 1; ++y)
		{
			GridPoint* point = new GridPoint(x * LineSize - HalfDotSize, y * LineSize - HalfDotSize, DotSize);
			scene->addItem(point);
		}
	}
}

void RoomEditor::mouseMoveEvent(QMouseEvent* event)
{
	currentTool_->mouseMoveEvent(event);
}

void RoomEditor::mousePressEvent(QMouseEvent* event)
{
	currentTool_->mousePressEvent(event);
}

void RoomEditor::mouseReleaseEvent(QMouseEvent* event)
{
	currentTool_->mouseReleaseEvent(event);
}

void RoomEditor::setZoomLevel(int zoomPercentage)
{
	qreal scaleFactor = zoomPercentage / 100.0;
	view->setZoomLevel(scaleFactor);
	showZoomLevel();
}

void RoomEditor::showZoomLevel()
{
	qreal scaleFactor = view->transform().m11();
	int zoomPercentage = qRound(scaleFactor * 100);
	zoomLabel->setText(QString("Zoom: %1%").arg(zoomPercentage));
	zoomLabel->adjustSize();
	zoomLabel->move(10, 10);
	zoomLabel->showWithTimer();
}

void RoomEditor::onZoomChanged() { showZoomLevel(); }

void RoomEditor::onCurrentToolChanged(ITool* newTool)
{
	currentTool_ = newTool;
	infoLabel->setText("New tool!");
	infoLabel->adjustSize();
	infoLabel->move(10, 10);
	infoLabel->showWithTimer();
}

RoomEditor::~RoomEditor() {}
