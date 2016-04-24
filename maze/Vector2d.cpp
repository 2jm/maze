//------------------------------------------------------------------------------
// Vector2d.cpp
//
// Group: Group 13624, study assistant Angela Promitzer
//
// Authors: Jonas Juffinger (1531253)
//          Matthias Klotz (1530653)
//          Johannes Kopf (1431505)
//------------------------------------------------------------------------------
//

#include "Vector2d.h"

const Vector2d Vector2d::UP(Vector2d(0, -1));
const Vector2d Vector2d::RIGHT(Vector2d(1, 0));
const Vector2d Vector2d::DOWN(Vector2d(0, 1));
const Vector2d Vector2d::LEFT(Vector2d(-1, 0));
const Vector2d Vector2d::OTHER(Vector2d(0, 0));

//------------------------------------------------------------------------------
Vector2d::Vector2d() :
        x_(0),
        y_(0)
{

}

//------------------------------------------------------------------------------
Vector2d::Vector2d(int x, int y) :
        x_(x),
        y_(y)
{

}

//------------------------------------------------------------------------------
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

//------------------------------------------------------------------------------
Vector2d::Vector2d(char character)
{
  switch(character)
  {
    case static_cast<char>(DirectionOneWay::UP):
      *this = UP;
      break;

    case static_cast<char>(DirectionOneWay::RIGHT):
      *this = RIGHT;
      break;

    case static_cast<char>(DirectionOneWay::DOWN):
      *this = DOWN;
      break;

    case static_cast<char>(DirectionOneWay::LEFT):
      *this = LEFT;
      break;

    default:
      *this = OTHER;
  }
}

//------------------------------------------------------------------------------
Vector2d::Vector2d(const Vector2d &original) : x_(original.x_),
                                               y_(original.y_)
{

}

//------------------------------------------------------------------------------
int Vector2d::getX() const
{
  return x_;
}

//------------------------------------------------------------------------------
int Vector2d::getY() const
{
  return y_;
}

//------------------------------------------------------------------------------
int Vector2d::x() const
{
  return getX();
}

//------------------------------------------------------------------------------
int Vector2d::y() const
{
  return getY();
}

//------------------------------------------------------------------------------
void Vector2d::setX(int x)
{
  x_ = x;
}

//------------------------------------------------------------------------------
void Vector2d::setY(int y)
{
  y_ = y;
}

//------------------------------------------------------------------------------
bool Vector2d::operator==(const Vector2d &other) const
{
  return x_ == other.x_ && y_ == other.y_;
}

//------------------------------------------------------------------------------
Vector2d Vector2d::operator+(const Vector2d &other)
{
  return Vector2d(other.x_ + x_, other.y_ + y_);
}

//------------------------------------------------------------------------------
Vector2d Vector2d::operator-(const Vector2d &other)
{
  return Vector2d(other.x_ - x_, other.y_ - y_);
}

//------------------------------------------------------------------------------
void Vector2d::operator+=(const Vector2d &other)
{
  x_ += other.x_;
  y_ += other.y_;
}

//------------------------------------------------------------------------------
Vector2d::operator Direction() const
{
  if(*this == Vector2d::UP)
    return Direction::UP;
  else if(*this == Vector2d::RIGHT)
    return Direction::RIGHT;
  else if(*this == Vector2d::DOWN)
    return Direction::DOWN;
  else if(*this == Vector2d::LEFT)
    return Direction::LEFT;
  else
    return Direction::OTHER;
}
