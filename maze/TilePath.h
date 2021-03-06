//------------------------------------------------------------------------------
// TilePath.h
//
// Group: Group 13624, study assistant Angela Promitzer
//
// Authors: Jonas Juffinger (1531253)
//          Matthias Klotz (1530653)
//          Johannes Kopf (1431505)
//------------------------------------------------------------------------------
//

#ifndef MAZE_ALL_TILEPATH_H
#define MAZE_ALL_TILEPATH_H


#include "Tile.h"

//------------------------------------------------------------------------------
// Tile Path
//
// class representing a path (' ') on the map
//
class TilePath : public Tile
{
  private:
    //--------------------------------------------------------------------------
    // Private copy constructor
    //
    TilePath(const TilePath &) = delete;

    //--------------------------------------------------------------------------
    // Private assignment operator
    //
    TilePath &operator=(const TilePath &) = delete;

  public:
    //--------------------------------------------------------------------------
    // Constructor
    //
    TilePath(Vector2d position);

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


#endif //MAZE_ALL_TILEPATH_H
