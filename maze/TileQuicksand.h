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
    Game &board_;

  public:
    TileQuicksand(Vector2d position, char character, Game &board);

    bool enter(Vector2d source_position, Vector2d &new_position);
};


#endif //MAZE_ALL_TILEQUICKSAND_H
