#ifndef DIRECTION_H
#define DIRECTION_H

#include <cstdint>

#include <QException>
#include <qvectornd.h>

namespace WallPoint
{
	enum Direction : uint8_t
	{
		None        = 0,
		Up          = 1 << 0,
		UpRight     = 1 << 1,
		Right       = 1 << 2,
		BottomRight = 1 << 3,
		Bottom      = 1 << 4,
		BottomLeft  = 1 << 5,
		Left        = 1 << 6,
		UpLeft      = 1 << 7,
	};

	Direction OppositeDirection(Direction dir)
	{
		switch(dir)
		{
			case Direction::Up:          return Direction::Bottom;
			case Direction::UpRight:     return Direction::BottomLeft;
			case Direction::Right:       return Direction::Left;
			case Direction::BottomRight: return Direction::UpLeft;
			case Direction::Bottom:      return Direction::Up;
			case Direction::BottomLeft:  return Direction::UpRight;
			case Direction::Left:        return Direction::Right;
			case Direction::UpLeft:      return Direction::BottomRight;
			default: throw std::runtime_error("Direction was not provided");;
		}
	}

	QVector2D GetOffsetToDirection(Direction dir)
	{
		switch(dir)
		{
		case Direction::Up:          return QVector2D(-1.0f,  0.0f);
		case Direction::UpRight:     return QVector2D(-1.0f,  1.0f);
		case Direction::Right:       return QVector2D( 0.0f,  1.0f);
		case Direction::BottomRight: return QVector2D( 1.0f,  1.0f);
		case Direction::Bottom:      return QVector2D( 1.0f,  0.0f);
		case Direction::BottomLeft:  return QVector2D( 1.0f, -1.0f);
		case Direction::Left:        return QVector2D( 0.0f, -1.0f);
		case Direction::UpLeft:      return QVector2D(-1.0f, -1.0f);
		default: throw std::runtime_error("Direction was not provided");;
		}
	}
}

#endif // DIRECTION_H
