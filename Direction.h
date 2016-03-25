//
// Created by jonas on 3/25/16.
//

#ifndef MAZE_DIRECTION_H
#define MAZE_DIRECTION_H

#include "Vector2d.h"

class Direction
{
  private:
    Direction()
    {
    }

  public:
    const static Vector2d UP;
    const static Vector2d RIGHT;
    const static Vector2d DOWN;
    const static Vector2d LEFT;
};

#endif //MAZE_DIRECTION_H
