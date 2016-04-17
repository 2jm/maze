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
  return x_ == other.x_ && y_ == other.y_;
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

bool operator==(const Vector2d& lhs, const Vector2d& rhs)
{
  return lhs.x() == rhs.x() && lhs.y() == rhs.y();
}

Vector2d::operator Direction() const
{
  if(*this == Vector2d::UP)
    return Direction::UP;
  else if(*this == Vector2d::RIGHT)
    return  Direction::RIGHT;
  else if(*this == Vector2d::DOWN)
    return  Direction::DOWN;
  else if(*this == Vector2d::LEFT)
    return  Direction::LEFT;
  else
    return Direction::OTHER;
  /*
  switch(*this) //switch((Direction) *this) -> would call the operator again
  {
    case Direction::UP:
      return Direction::UP;
    case Direction::RIGHT:
      return Direction::RIGHT;
    case Direction::DOWN:
      return Direction::DOWN;
    case Direction::LEFT:
      return Direction::LEFT;
    default:
      return Direction::OTHER;
  }*/
}





























