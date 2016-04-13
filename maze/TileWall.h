//
// Created by John on 26.03.2016.
//

#ifndef MAZE_ALL_TILEWALL_H
#define MAZE_ALL_TILEWALL_H


#include "Tile.h"

class TileWall : public Tile
{
  public:
    TileWall(Vector2d position) : Tile(position, '#')
    {}

    bool enter(Vector2d source_position, Vector2d &new_position);
};


#endif //MAZE_ALL_TILEWALL_H
