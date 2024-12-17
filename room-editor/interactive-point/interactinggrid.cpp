#include "interactinggrid.h"

InteractingGrid::InteractingGrid(QGraphicsScene *scene_, int rows, int cols)
    :scene_(scene_), isInteractive_(false), gridHeight_(rows), gridWidth_(cols) {}

InteractingGrid::~InteractingGrid()
{
    for (const auto& row : _grid)
        for (GridPoint* point : row)
            delete point;
}

void InteractingGrid::setUpGridPoints(qreal lineSize, qreal dotSize)
{
    for (int row = 0; row < getHeight() + 1; ++row) {
        QVector<GridPoint*> rowPoints;
        for (int col = 0; col < getWidth() + 1; ++col)
        {

            GridPoint* point = new GridPoint(row * lineSize - (dotSize / 2.0), col * lineSize - (dotSize / 2.0), dotSize);
            point->setZValue(100);
            scene_->addItem(point);

            rowPoints.append(point);
        }
        _grid.push_back(rowPoints);
    }
}

GridPoint* InteractingGrid::getPoint(int row, int col) const
{
    if (row >= 0 && row < _grid.size() && col >= 0 && col < _grid[row].size()) 
        return _grid[row][col];
    return nullptr;
}

void InteractingGrid::setInteractive(bool interactive)
{
    isInteractive_ = interactive;

    for (const auto& row : _grid)
        for (GridPoint* point : row)
            point->setAcceptHoverEvents(interactive);
}