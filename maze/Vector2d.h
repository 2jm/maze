//------------------------------------------------------------------------------
// Vector2d.h
//
// Group: Group 13624, study assistant Angela Promitzer
//
// Authors: Jonas Juffinger (1531253)
//          Matthias Klotz (1530653)
//          Johannes Kopf (1431505)
//------------------------------------------------------------------------------
//

#ifndef MAZE_VECTOR2D_H
#define MAZE_VECTOR2D_H


#include "Direction.h"

//----------------------------------------------------------------------------
// Vector 2D
//
// class representing a point (x, y) in the 2d space
//
class Vector2d
{
  private:
    //--------------------------------------------------------------------------
    // x coordinate
    //
    int x_;
    //--------------------------------------------------------------------------
    // y coordinate
    //
    int y_;

  public:
    const static Vector2d UP;
    const static Vector2d RIGHT;
    const static Vector2d DOWN;
    const static Vector2d LEFT;
    const static Vector2d OTHER;

    //--------------------------------------------------------------------------
    // Constructor
    //
    Vector2d();

    //--------------------------------------------------------------------------
    // Constructor
    // @param x The initial x coordinate
    // @param y The initial y coordinate
    //
    Vector2d(int x, int y);

    //--------------------------------------------------------------------------
    // Constructor
    // @param direction Pointing either up, right, down, left or other
    //
    Vector2d(Direction direction);

    //--------------------------------------------------------------------------
    // Constructor
    // @param character Character that is representing either up, right, down,
    //                  left or other
    //
    Vector2d(char character);

    //--------------------------------------------------------------------------
    // Copy Constructor
    // Makes a copy of another Vector2d Object.
    // @param original Original to copy.
    //
    Vector2d(const Vector2d &original);

    //--------------------------------------------------------------------------
    // Getter Methods
    //
    int getX() const;

    int getY() const;

    int x() const;

    int y() const;

    //--------------------------------------------------------------------------
    // Setter Methods
    //
    void setX(int x);

    void setY(int y);

    //--------------------------------------------------------------------------
    // Overloaded Operators
    //
    bool operator==(const Vector2d &other) const;

    Vector2d operator+(const Vector2d &other);

    Vector2d operator-(const Vector2d &other);

    void operator+=(const Vector2d &other);

    operator Direction() const;
};


#endif //MAZE_VECTOR2D_H
