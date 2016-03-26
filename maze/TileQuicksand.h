//
// Created by John on 26.03.2016.
//

#ifndef MAZE_ALL_TILEQUICKSAND_H
#define MAZE_ALL_TILEQUICKSAND_H


#include "Tile.h"

class TileQuicksand : public Tile
{
  public:
    TileQuicksand(int steps);
    int steps_;
};


#endif //MAZE_ALL_TILEQUICKSAND_H
