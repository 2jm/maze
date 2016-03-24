//
// Created by John on 22.03.2016.
//

#ifndef MAZE_VECTOR2D_H
#define MAZE_VECTOR2D_H


class Vector2d
{
  private:
    int x;
    int y;
  public:
    int getX();
    int getY();
    void setX(int x);
    void setY(int y);

    Vector2d operator+(const Vector2d &other);
    Vector2d operator=(const Vector2d &other);

//    Vector2d operator+(Vector2d lhs, const Vector2d& rhs)
//    {
//      return lhs *= rhs;
//    }
};


#endif //MAZE_VECTOR2D_H
