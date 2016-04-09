//
// Created by John on 26.03.2016.
//

#ifndef MAZE_ALL_TILEBONUS_H
#define MAZE_ALL_TILEBONUS_H


#include "Tile.h"
#include "Game.h"

class TileBonus : public Tile
{
  private:
    int steps_add_;
    bool used_;
    Game *board_;
  public:
    TileBonus(int steps_add, Game &board);
    bool enter(Vector2d source_position, Vector2d new_position) override;
};


#endif //MAZE_ALL_TILEBONUS_H
