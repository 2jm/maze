//------------------------------------------------------------------------------
// TileQuicksand.h
//
// Group: Group 13624, study assistant Angela Promitzer
//
// Authors: Jonas Juffinger (1531253)
//          Matthias Klotz (1530653)
//          Johannes Kopf (1431505)
//------------------------------------------------------------------------------
//

#ifndef MAZE_ALL_TILEQUICKSAND_H
#define MAZE_ALL_TILEQUICKSAND_H


#include "Tile.h"
#include "Game.h"

//----------------------------------------------------------------------------
// Tile Quicksand
//
// class representing a quicksand ('f' - 'j') on the map
//
class TileQuicksand : public Tile
{
  private:
    Game &game_;

  public:
    //--------------------------------------------------------------------------
    // Constructor
    //
    TileQuicksand(Vector2d position, char character, Game &game);

    //--------------------------------------------------------------------------
    // Called when the player enters a tile
    //
    // @param source_position The initial player position
    //
    // @return EnterResult Tells if it was a valid/invalid move or if the
    //         player should move again (call enter on the new tile again,
    //         needed for the ice tile)
    //
    EnterResult enter(Vector2d &source_position);
};


#endif //MAZE_ALL_TILEQUICKSAND_H
