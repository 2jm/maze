//------------------------------------------------------------------------------
// TileWall.h
//
// Group: Group 13624, study assistant Angela Promitzer
//
// Authors: Jonas Juffinger (1531253)
//          Matthias Klotz (1530653)
//          Johannes Kopf (1431505)
//------------------------------------------------------------------------------
//

#ifndef MAZE_ALL_TILEWALL_H
#define MAZE_ALL_TILEWALL_H


#include "Tile.h"

//------------------------------------------------------------------------------
// Tile Wall
//
// class representing a wall ('#') on the map
//
class TileWall : public Tile
{
  private:
    //--------------------------------------------------------------------------
    // Private copy constructor
    //
    TileWall(const TileWall &original);

    //--------------------------------------------------------------------------
    // Private assignment operator
    //
    TileWall &operator=(const TileWall &original);

  public:
    //--------------------------------------------------------------------------
    // Constructor
    //
    TileWall(Vector2d position);

    //--------------------------------------------------------------------------
    // Called when the player enters a tile
    // @param source_position The initial player position
    // @return EnterResult Tells if it was a valid/invalid move or if the
    //         player should move again (call enter on the new tile again,
    //         needed for the ice tile)
    //
    EnterResult enter(Vector2d &source_position);
};


#endif //MAZE_ALL_TILEWALL_H
