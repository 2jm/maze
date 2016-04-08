//
// Created by John on 26.03.2016.
//

#ifndef MAZE_ALL_TILEBONUS_H
#define MAZE_ALL_TILEBONUS_H


#include "Tile.h"

class TileBonus : public Tile
{
  private:
    int steps_;
    bool used_;
  public:
    TileBonus(int steps);
    bool enter(Vector2d source_position, Vector2d new_position) override;
};


#endif //MAZE_ALL_TILEBONUS_H
