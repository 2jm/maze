//
// Created by John on 26.03.2016.
//

#ifndef MAZE_ALL_TILESTART_H
#define MAZE_ALL_TILESTART_H


#include "Tile.h"

class TileStart : public Tile
{
  public:
    TileStart(Vector2d position);

    bool enter(Vector2d &source_position);
};


#endif //MAZE_ALL_TILESTART_H
