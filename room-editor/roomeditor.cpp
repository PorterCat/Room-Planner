#include "roomeditor.h"

#include <QActionGroup>
#include <QGraphicsLineItem>

RoomEditor::RoomEditor(int gridWidth, int gridHeight, QWidget *parent)
	: QWidget(parent), gridWidth_(gridWidth), gridHeight_(gridHeight)
{
	scene = new QGraphicsScene(this);

	view = new ZoomableGraphicsView(scene, this);
	view->setMouseTracking(true);

	view->setRenderHint(QPainter::Antialiasing);
	view->setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
	view->setDragMode(QGraphicsView::ScrollHandDrag);

	view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

	setLayout(new QVBoxLayout);
	layout()->addWidget(view);

	zoomLabel = new PopupLabel(this);
	zoomLabel->setStyleSheet("background-color: rgba(0, 0, 0, 128); color: white; padding: 5px;");
	zoomLabel->setAlignment(Qt::AlignCenter);
	zoomLabel->hide();

	connect(view, &ZoomableGraphicsView::zoomChanged, this, &RoomEditor::onZoomChanged);
	connect(zoomLabel, &PopupLabel::clicked, this, &RoomEditor::onZoomLabelClicked);
	// connect(, &QActionGroup::triggered, this, &RoomEditor::onCurrentToolChanged);

	this->drawGrid();

	scene->setBackgroundBrush(Qt::white);

	// QGraphicsLineItem* wall = new QGraphicsLineItem(1, 1, 10, 10);
	// wall->setPen(QPen(Qt::black, 10));
	// scene->addItem(wall);

}

void RoomEditor::onZoomLabelClicked()
{
	bool ok;
	int newZoom = QInputDialog::getInt(this, "Set Zoom Level", "Enter zoom percentage:", 100, 10, 1000, 10, &ok);
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

	QPen linesPen(QColor(LineBrightness, LineBrightness, LineBrightness, 255));
	QPen dotsPen(QColor(0, 0, 230, 255));

	for (int i = 0; i <= gridWidth_; ++i)
	{
		scene->addLine(i * LineSize, 0, i * LineSize, gridHeight_ * LineSize, linesPen);
	}
	for (int i = 0; i <= gridHeight_; ++i)
	{
		scene->addLine(0, i * LineSize, gridWidth_ * LineSize, i * LineSize, linesPen);
	}

	for(int x = 0; x < gridWidth_ + 1; ++x)
	{
		for(int y = 0; y < gridHeight_ + 1; ++y)
		{
			scene->addEllipse(x * LineSize - HalfDotSize, y * LineSize - HalfDotSize, DotSize, DotSize, dotsPen);
		}
	}
}

void RoomEditor::setZoomLevel(int zoomPercentage)
{
	qreal scaleFactor = zoomPercentage / 100.0;
	view->setTransform(QTransform::fromScale(scaleFactor, scaleFactor));
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

RoomEditor::~RoomEditor() {}
