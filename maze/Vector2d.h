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
    const static Vector2d OTHER;

    Vector2d();
    Vector2d(int x, int y);

    Vector2d(Direction direction);
    Vector2d(char sign);

    int getX() const;
    int getY() const;
    int x() const;
    int y() const;

    void setX(int x);
    void setY(int y);

    bool operator==(const Vector2d &other) const;
    Vector2d operator+(const Vector2d &other);
    Vector2d operator-(const Vector2d &other);
    Vector2d operator+=(const Vector2d &other);

    operator Direction() const;
};


#endif //MAZE_VECTOR2D_H
