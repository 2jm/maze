//
// Created by John on 22.03.2016.
//

#include "Vector2d.h"


const Vector2d Vector2d::UP(Vector2d(0, -1));
const Vector2d Vector2d::RIGHT(Vector2d(1, 0));
const Vector2d Vector2d::DOWN(Vector2d(0, 1));
const Vector2d Vector2d::LEFT(Vector2d(-1, 0));
const Vector2d Vector2d::OTHER(Vector2d(0, 0));


Vector2d::Vector2d()
{

}

Vector2d::Vector2d(int x, int y) :
        x_(x),
        y_(y)
{

}

Vector2d::Vector2d(Direction direction)
{
  switch(direction)
  {
    case Direction::UP:
      *this = UP;
      break;

    case Direction::RIGHT:
      *this = RIGHT;
      break;

    case Direction::DOWN:
      *this = DOWN;
      break;

    case Direction::LEFT:
      *this = LEFT;
      break;

    case Direction::OTHER:
      *this = OTHER;
  }
}

Vector2d::Vector2d(char sign)
{
  switch(sign)
  {
    case '^':
      *this = UP;
      break;

    case '>':
      *this = RIGHT;
      break;

    case 'v':
      *this = DOWN;
      break;

    case '<':
      *this = LEFT;
      break;

    default:
      *this = OTHER;
  }
}


bool Vector2d::operator==(const Vector2d &other)
{
  return (x_ == other.x_ && y_ == other.y_);
}

Vector2d Vector2d::operator+(const Vector2d &other)
{
  return Vector2d(other.x_ + x_, other.y_ + y_);
}

Vector2d Vector2d::operator-(const Vector2d &other)
{
  return Vector2d(other.x_ - x_, other.y_ - y_);
}

Vector2d Vector2d::operator+=(const Vector2d &other)
{
  x_ += other.x_;
  y_ += other.y_;
}


Vector2d::operator Direction() const
{
  switch((Direction)*this)
  {
    case Direction::UP:
      return UP;
    case Direction::RIGHT:
      return RIGHT;
    case Direction::DOWN:
      return DOWN;
    case Direction::LEFT:
      return LEFT;
    default:
      return Direction::OTHER;
  }
}





























