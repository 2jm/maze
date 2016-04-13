//
// Created by John on 26.03.2016.
//

#ifndef MAZE_ALL_TILEICE_H
#define MAZE_ALL_TILEICE_H


#include "Tile.h"

class TileIce : public Tile
{
    TileIce(Vector2d position) : Tile(position, '+')
    {}

    bool enter(Vector2d source_position, Vector2d &new_position);
};


#endif //MAZE_ALL_TILEICE_H
