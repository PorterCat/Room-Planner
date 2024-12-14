#include "roomeditor.h"

RoomEditor::RoomEditor(int gridWidth, int gridHeight, QWidget *parent)
	: QWidget(parent), gridWidth_(gridWidth), gridHeight_(gridHeight)
{
	scene = new QGraphicsScene(this);
	view = new ZoomableGraphicsView(scene, this);

	view->setRenderHint(QPainter::Antialiasing);
	view->setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
	view->setDragMode(QGraphicsView::ScrollHandDrag);

	view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

	view->setFixedSize(800, 600);
	setLayout(new QVBoxLayout);
	layout()->addWidget(view);

	zoomLabel = new PopupLabel(this);
	zoomLabel->setStyleSheet("background-color: rgba(0, 0, 0, 128); color: white; padding: 5px;");
	zoomLabel->setAlignment(Qt::AlignCenter);
	zoomLabel->hide();

	connect(view, &ZoomableGraphicsView::zoomChanged, this, &RoomEditor::onZoomChanged);

	connect(zoomLabel, &PopupLabel::clicked, this, &RoomEditor::onZoomLabelClicked);

	this->drawGrid();
}

void RoomEditor::onZoomLabelClicked()
{
	bool ok;
	int newZoom = QInputDialog::getInt(this, "Set Zoom Level", "Enter zoom percentage:", 100, 10, 1000, 10, &ok);
	if (ok) {
		setZoomLevel(newZoom);
	}
}

void RoomEditor::setGridSize(int width, int height)
{
	gridWidth_ = width;
	gridHeight_ = height;
	drawGrid();
}

void RoomEditor::drawGrid()
{
	scene->clear();
	for (int i = 0; i <= gridWidth_; ++i)
	{
		//scene->addEllipse(i * sideLength - halfSideLength, 0, sideLength, sideLength, QPen(Qt::gray));
		scene->addLine(i * 25, 0, i * 25, gridHeight_ * 25, QPen(Qt::gray));
	}
	for (int i = 0; i <= gridHeight_; ++i)
	{
		//scene->addEllipse(0, i * sideLength - halfSideLength, sideLength, sideLength, QPen(Qt::gray));
		scene->addLine(0, i * 25, gridWidth_ * 25, i * 25, QPen(Qt::gray));
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
