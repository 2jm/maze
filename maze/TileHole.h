//------------------------------------------------------------------------------
// TileHole.h
//
// Group: Group 13624, study assistant Angela Promitzer
//
// Authors: Jonas Juffinger (1531253)
//          Matthias Klotz (1530653)
//          Johannes Kopf (1431505)
//------------------------------------------------------------------------------
//

#ifndef MAZE_ALL_TILEHOLE_H
#define MAZE_ALL_TILEHOLE_H


#include <memory>
#include "Tile.h"

//------------------------------------------------------------------------------
// Tile Hole
//
// class representing a hole ('s') on the map
//
class TileHole : public Tile
{
  private:
    //--------------------------------------------------------------------------
    // Private copy constructor
    //
    TileHole(const TileHole &) = delete;

    //--------------------------------------------------------------------------
    // Private assignment operator
    //
    TileHole &operator=(const TileHole &) = delete;

    //--------------------------------------------------------------------------
    // Reference to the start tile
    //
    Tile *start_tile_;

  public:
    //--------------------------------------------------------------------------
    // Constructor
    //
    TileHole(Vector2d position);

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

    //--------------------------------------------------------------------------
    // Set a reference to the start tile on the map
    //
    // @param start The start tile
    //
    void setStartTile(Tile *start);
};


#endif //MAZE_ALL_TILEHOLE_H
