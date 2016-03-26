//
// Created by John on 26.03.2016.
//

#ifndef MAZE_ALL_TILEBONUS_H
#define MAZE_ALL_TILEBONUS_H


#include "Tile.h"

class TileBonus : public Tile
{
  public:
    TileBonus(int steps);
    int steps_;
};


#endif //MAZE_ALL_TILEBONUS_H
