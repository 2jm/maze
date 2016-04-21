//------------------------------------------------------------------------------
// TileFinish.h
//
// Group: Group 13624, study assistant Angela Promitzer
//
// Authors: Jonas Juffinger (1531253)
//          Matthias Klotz (1530653)
//          Johannes Kopf (1431505)
//------------------------------------------------------------------------------
//

#ifndef MAZE_ALL_TILEFINISH_H
#define MAZE_ALL_TILEFINISH_H


#include "Tile.h"
#include "Game.h"

class TileFinish : public Tile
{
  private:
    Game &board_;

  public:
    TileFinish(Vector2d position, Game &board);

    EnterResult enter(Vector2d &source_position);
};


#endif //MAZE_ALL_TILEFINISH_H
