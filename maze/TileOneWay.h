//
// Created by John on 26.03.2016.
//

#ifndef MAZE_ALL_TILEONEWAY_H
#define MAZE_ALL_TILEONEWAY_H


#include "Tile.h"

class TileOneWay : public Tile
{
  private:
    Vector2d tile_direction_;
  public:
    TileOneWay(char);
    bool enter(Vector2d source_position, Vector2d new_position) override;
};


#endif //MAZE_ALL_TILEONEWAY_H
