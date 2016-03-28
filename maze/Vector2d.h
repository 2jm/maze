//
// Created by John on 22.03.2016.
//

#ifndef MAZE_VECTOR2D_H
#define MAZE_VECTOR2D_H

#include "Direction.h"

class Vector2d
{
  private:
    int x_;
    int y_;

  public:
    const static Vector2d UP;
    const static Vector2d RIGHT;
    const static Vector2d DOWN;
    const static Vector2d LEFT;

    Vector2d();
    Vector2d(int x, int y);

    Vector2d(Direction direction);

    int getX() const
    {
      return x_;
    }
    int getY() const
    {
      return y_;
    }
    int x() const
    {
      return getX();
    }
    int y() const
    {
      return getY();
    }

    void setX(int x)
    {
      x_ = x;
    }
    void setY(int y)
    {
      y_ = y;
    }

    bool operator==(const Vector2d &other);
    Vector2d operator+(const Vector2d &other);

    operator Direction() const;

//    Vector2d operator+(Vector2d lhs, const Vector2d& rhs)
//    {
//      return lhs *= rhs;
//    }
};


#endif //MAZE_VECTOR2D_H
