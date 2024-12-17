#pragma once

#include <QVector>
#include <QGraphicsScene>
#include <room-editor/interactive-point/gridpoint.h>

class InteractingGrid 
{
public:
	InteractingGrid(QGraphicsScene *scene_, int rows, int cols);
	~InteractingGrid();
	void setUpGridPoints(qreal lineSize, qreal dotSize);

	GridPoint* getPoint(int row, int col) const;
	void setInteractive(bool interactive);

	int getWidth() { return gridWidth_; }
	int getHeight() { return gridHeight_; }

private:
	QVector<QVector<GridPoint*>> _grid;
	int gridWidth_;
	int gridHeight_;
	QGraphicsScene *scene_;
	bool isInteractive_;
};
