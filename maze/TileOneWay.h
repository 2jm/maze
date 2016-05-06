//------------------------------------------------------------------------------
// TileOneWay.h
//
// Group: Group 13624, study assistant Angela Promitzer
//
// Authors: Jonas Juffinger (1531253)
//          Matthias Klotz (1530653)
//          Johannes Kopf (1431505)
//------------------------------------------------------------------------------
//

#ifndef MAZE_ALL_TILEONEWAY_H
#define MAZE_ALL_TILEONEWAY_H


#include "Tile.h"

//----------------------------------------------------------------------------
// Tile One Way
//
// class representing a one way ('^', '>', 'v', '<') on the map
//
class TileOneWay : public Tile
{
  private:
    //--------------------------------------------------------------------------
    // Private copy constructor
    //
    TileOneWay(const TileOneWay &) = delete;

    //--------------------------------------------------------------------------
    // Private assignment operator
    //
    TileOneWay &operator=(const TileOneWay &) = delete;

  public:
    //--------------------------------------------------------------------------
    // Constructor
    //
    TileOneWay(Vector2d position, char character);

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
    bool leave(const Direction move_direction) const override;
};


#endif //MAZE_ALL_TILEONEWAY_H
