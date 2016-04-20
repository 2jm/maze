//------------------------------------------------------------------------------
// <Filename>.cpp
//
// Group: Group 13624, study assistant Angela Promitzer
//
// Authors: Jonas Juffinger (1531253)
// Matthias Klotz (1530653)
// Johannes Kopf (1431505)
//------------------------------------------------------------------------------
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

    bool enter(Vector2d &source_position);
};


#endif //MAZE_ALL_TILEQUICKSAND_H
