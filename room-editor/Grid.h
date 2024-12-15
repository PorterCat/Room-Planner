#ifndef GRID_H
#define GRID_H

#include <vector>

#include "WallPoint/Direction.h"

namespace Walls
{

class Grid
{
  public:
	Grid(size_t width, size_t height): width_(width), height_(height)
	{
		wallPoints_ = std::vector<WallPointDirection_t>(width_ * height_, WallPointDirection::None);
	}

	size_t getWidth() const { return width_; }
	size_t getHeight() const { return height_; }

	void setPoint(size_t row, size_t column, WallPointDirection_t dir, int length = 1)
	{
		size_t size = wallPoints_.size();
		if(getIndex(row, column) >= size)
			throw std::invalid_argument("Target point is out of grid bounds");

		QVector2D lastPoint = QVector2D(row, column) + (GetOffsetToDirection(dir) * length);
		if(getIndex(lastPoint.x(), lastPoint.y()) >= size)
			throw std::invalid_argument("Last affected point is out of grid bounds");

		WallPointDirection_t opposite = OppositeDirection(dir);

		addWallPointDir(row, column, dir);

		auto middleDir = static_cast<WallPointDirection_t>(dir | opposite);
		for(size_t i = 1; i < length - 1; ++i)
		{
			QVector2D point = QVector2D(row, column) + (GetOffsetToDirection(dir) * i);
			addWallPointDir(point.x(), point.y(), middleDir);
		}

		addWallPointDir(lastPoint.x(), lastPoint.y(), opposite);
	}

  private:

	size_t getIndex(size_t row, size_t column) const
	{
		return row * height_ + column;
	}

	WallPointDirection_t getWallPointDir(size_t row, size_t column) const
	{
		return wallPoints_[getIndex(row, column)];
	}

	void addWallPointDir(size_t row, size_t column, WallPointDirection_t value)
	{
		WallPointDirection_t d = getWallPointDir(row, column);
		d = static_cast<WallPointDirection_t>(d |value);
		setWallPoint(row, column, d);
	}

	void setWallPoint(size_t row, size_t column, WallPointDirection_t value)
	{
		wallPoints_[getIndex(row, column)] = value;
	}

	std::vector<WallPointDirection_t> wallPoints_;
	size_t width_;
	size_t height_;
};

}

#endif // GRID_H
