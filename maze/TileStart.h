//
// Created by John on 26.03.2016.
//

#ifndef MAZE_ALL_TILESTART_H
#define MAZE_ALL_TILESTART_H


#include "Tile.h"

class TileStart : public Tile
{
    TileStart(Vector2d position) : Tile(position, 'o')
    {}

    bool enter(Vector2d source_position, Vector2d &new_position);
};


#endif //MAZE_ALL_TILESTART_H
