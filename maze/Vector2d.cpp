//
// Created by John on 22.03.2016.
//

#include "Vector2d.h"


const Vector2d Vector2d::UP(Vector2d(0, -1));
const Vector2d Vector2d::RIGHT(Vector2d(1, 0));
const Vector2d Vector2d::DOWN(Vector2d(0, 1));
const Vector2d Vector2d::LEFT(Vector2d(-1, 0));


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
  if(direction == Direction::UP)
    *this = UP;

  if(direction == Direction::RIGHT)
    *this = RIGHT;

  if(direction == Direction::DOWN)
    *this = DOWN;

  if(direction == Direction::LEFT)
    *this = LEFT;
}

Vector2d::Vector2d(char sign)
{
  if(sign == '^')
    *this = UP;

  if(sign == '>')
    *this = RIGHT;

  if(sign == 'v')
    *this = DOWN;

  if(sign == '<')
    *this = LEFT;
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


Vector2d::operator Direction() const
{
  if(*this == UP)
    return Direction::UP;

  if(*this == RIGHT)
    return Direction::RIGHT;

  if(*this == DOWN)
    return Direction::DOWN;

  if(*this == LEFT)
    return Direction::LEFT;

  return Direction::OTHER;
}






















