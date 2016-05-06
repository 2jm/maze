//------------------------------------------------------------------------------
// TileTeleport.h
//
// Group: Group 13624, study assistant Angela Promitzer
//
// Authors: Jonas Juffinger (1531253)
//          Matthias Klotz (1530653)
//          Johannes Kopf (1431505)
//------------------------------------------------------------------------------
//

#ifndef MAZE_ALL_TILETELEPORT_H
#define MAZE_ALL_TILETELEPORT_H


#include <memory>
#include "Tile.h"

//------------------------------------------------------------------------------
// Tile Teleport
//
// class representing a teleport ('A' - 'Z') on the map
//
class TileTeleport : public Tile
{
  private:
    //--------------------------------------------------------------------------
    // Private copy constructor
    //
    TileTeleport(const TileTeleport &) = delete;

    //--------------------------------------------------------------------------
    // Private assignment operator
    //
    TileTeleport &operator=(const TileTeleport &) = delete;

    //--------------------------------------------------------------------------
    // Reference to the corresponding teleport tile
    //
    TileTeleport *corresponding_teleport_;

  public:
    //--------------------------------------------------------------------------
    // Constructor
    //
    TileTeleport(Vector2d position, char character);

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
    // Set a reference to the corresponding teleporter on the map
    //
    // @param teleport The corresponding teleport tile
    //
    void setCorrespondingTeleport(TileTeleport *teleport);
};


#endif //MAZE_ALL_TILETELEPORT_H
