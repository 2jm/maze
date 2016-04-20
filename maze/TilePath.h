//
// Created by John on 26.03.2016.
//

#ifndef MAZE_ALL_TILEPATH_H
#define MAZE_ALL_TILEPATH_H


#include "Tile.h"

class TilePath : public Tile
{
  public:
    TilePath(Vector2d position);

    bool enter(Vector2d &source_position);
};


#endif //MAZE_ALL_TILEPATH_H
