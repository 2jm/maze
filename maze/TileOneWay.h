//
// Created by John on 26.03.2016.
//

#ifndef MAZE_ALL_TILEONEWAY_H
#define MAZE_ALL_TILEONEWAY_H


#include "Tile.h"

class TileOneWay : public Tile
{
  public:
    TileOneWay(Vector2d position, char character) : Tile(position, character)
    {}

    bool enter(Vector2d source_position, Vector2d &new_position);
    bool leave(Direction move_direction) const override;
};


#endif //MAZE_ALL_TILEONEWAY_H
