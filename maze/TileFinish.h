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

class Game;

//----------------------------------------------------------------------------
// Tile Finish
//
// class representing the finish ('x') on the map
//
class TileFinish : public Tile
{
  private:
    //--------------------------------------------------------------------------
    // Private copy constructor
    //
    TileFinish(const TileFinish &) = delete;

    //--------------------------------------------------------------------------
    // Private assignment operator
    //
    TileFinish &operator=(const TileFinish &) = delete;

    //--------------------------------------------------------------------------
    // Reference to the current game
    //
    Game &game_;

  public:
    //--------------------------------------------------------------------------
    // Constructor
    //
    TileFinish(Vector2d position, Game &game);

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


#endif //MAZE_ALL_TILEFINISH_H
