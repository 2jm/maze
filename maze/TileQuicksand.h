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

class Game;

//------------------------------------------------------------------------------
// Tile Quicksand
//
// class representing a quicksand ('f' - 'j') on the map
//
class TileQuicksand : public Tile
{
  private:
    //--------------------------------------------------------------------------
    // Private copy constructor
    //
    TileQuicksand(const TileQuicksand &) = delete;

    //--------------------------------------------------------------------------
    // Private assignment operator
    //
    TileQuicksand &operator=(const TileQuicksand &) = delete;

    //--------------------------------------------------------------------------
    // Reference to the current game
    //
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

    // TODO
    int getStepChange();
};


#endif //MAZE_ALL_TILEQUICKSAND_H
