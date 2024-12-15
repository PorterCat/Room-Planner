#ifndef DIRECTION_H
#define DIRECTION_H

#include <cstdint>

#include <QException>
#include <qvectornd.h>

namespace Walls
{
	using WallPointDirection_t = uint8_t;

	// Ugly way to use bit flags and avoid warnings
	namespace WallPointDirection
	{
		constexpr WallPointDirection_t None        = 0;
		constexpr WallPointDirection_t Up          = 1 << 0;
		constexpr WallPointDirection_t UpRight     = 1 << 1;
		constexpr WallPointDirection_t Right       = 1 << 2;
		constexpr WallPointDirection_t BottomRight = 1 << 3;
		constexpr WallPointDirection_t Bottom      = 1 << 4;
		constexpr WallPointDirection_t BottomLeft  = 1 << 5;
		constexpr WallPointDirection_t Left        = 1 << 6;
		constexpr WallPointDirection_t UpLeft      = 1 << 7;
	}

	WallPointDirection_t OppositeDirection(WallPointDirection_t dir)
	{
		switch(dir)
		{
			case WallPointDirection::Up:          return WallPointDirection::Bottom;
			case WallPointDirection::UpRight:     return WallPointDirection::BottomLeft;
			case WallPointDirection::Right:       return WallPointDirection::Left;
			case WallPointDirection::BottomRight: return WallPointDirection::UpLeft;
			case WallPointDirection::Bottom:      return WallPointDirection::Up;
			case WallPointDirection::BottomLeft:  return WallPointDirection::UpRight;
			case WallPointDirection::Left:        return WallPointDirection::Right;
			case WallPointDirection::UpLeft:      return WallPointDirection::BottomRight;
			default: throw std::runtime_error("Direction was not provided");;
		}
	}

	QVector2D GetOffsetToDirection(WallPointDirection_t dir)
	{
		switch(dir)
		{
			case WallPointDirection::Up:          return QVector2D(-1.0f,  0.0f);
			case WallPointDirection::UpRight:     return QVector2D(-1.0f,  1.0f);
			case WallPointDirection::Right:       return QVector2D( 0.0f,  1.0f);
			case WallPointDirection::BottomRight: return QVector2D( 1.0f,  1.0f);
			case WallPointDirection::Bottom:      return QVector2D( 1.0f,  0.0f);
			case WallPointDirection::BottomLeft:  return QVector2D( 1.0f, -1.0f);
			case WallPointDirection::Left:        return QVector2D( 0.0f, -1.0f);
			case WallPointDirection::UpLeft:      return QVector2D(-1.0f, -1.0f);
			default: throw std::runtime_error("Direction was not provided");;
		}
	}
}

#endif // DIRECTION_H
