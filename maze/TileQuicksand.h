//
// Created by John on 26.03.2016.
//

#ifndef MAZE_ALL_TILEQUICKSAND_H
#define MAZE_ALL_TILEQUICKSAND_H


#include "Tile.h"
#include "Game.h"

class TileQuicksand : public Tile
{
  private:
    int remove_steps_;
    Game *board_;
  public:
    TileQuicksand(Game &board, int remove_steps);
    bool enter(Vector2d source_position, Vector2d new_position) override;
};


#endif //MAZE_ALL_TILEQUICKSAND_H
