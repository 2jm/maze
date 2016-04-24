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

//----------------------------------------------------------------------------
// Tile Finish
// class representing the finish ('x') on the map
//
class TileFinish : public Tile
{
  private:
    Game &board_;

  public:
    //--------------------------------------------------------------------------
    // Constructor
    TileFinish(Vector2d position, Game &board);

    //--------------------------------------------------------------------------
    // Called when the player enters a tile
    // @param source_position The initial player position
    // @return EnterResult Tells if it was a valid/invalid move or if the
    //         player should move again (call enter on the new tile again,
    //         needed for the ice tile)
    EnterResult enter(Vector2d &source_position);
};


#endif //MAZE_ALL_TILEFINISH_H
