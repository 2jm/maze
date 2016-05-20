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

#ifndef MAZE_ALL_TILECOUNTER_H
#define MAZE_ALL_TILECOUNTER_H

#include "Tile.h"

//------------------------------------------------------------------------------
// Tile Hole
//
// class representing a hole ('s') on the map
//
class TileCounter : public Tile
{
  private:
    //--------------------------------------------------------------------------
    // Private copy constructor
    //
    TileCounter(const TileCounter &) = delete;

    //--------------------------------------------------------------------------
    // Private assignment operator
    //
    TileCounter &operator=(const TileCounter &) = delete;

    //--------------------------------------------------------------------------
    // Private assignment operator
    //
    int counter_value_;


  public:
    //--------------------------------------------------------------------------
    // Constructor
    //
    TileCounter(Vector2d position, char character);

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
    // Called when the player leaves a tile
    //
    // @param move_direction The current moving direction of the player
    //
    // @return bool Tells if the player is allowed to move away from this tile
    //
    bool leave(const Direction move_direction) override;

    //--------------------------------------------------------------------------
    // Called when a tile should be reset, e.g. during a map reset
    //
    void reset();

    //--------------------------------------------------------------------------
    // Called when a tile should be reset, e.g. during a map reset
    //
    // @param original
    //
    // @return char Representing the tile on the map
    //
    virtual char toChar(bool original = true);
};


#endif //MAZE_ALL_TILECOUNTER_H
