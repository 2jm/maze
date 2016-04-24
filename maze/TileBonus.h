//------------------------------------------------------------------------------
// TileBonus.h
//
// Group: Group 13624, study assistant Angela Promitzer
//
// Authors: Jonas Juffinger (1531253)
//          Matthias Klotz (1530653)
//          Johannes Kopf (1431505)
//------------------------------------------------------------------------------
//

#ifndef MAZE_ALL_TILEBONUS_H
#define MAZE_ALL_TILEBONUS_H


#include "Tile.h"
#include "Game.h"

//----------------------------------------------------------------------------
// Tile Bonus
// class representing a bonus ('a' - 'e') on the map
//
class TileBonus : public Tile
{
  private:
    Game &board_;
    bool used_;

  public:
    //--------------------------------------------------------------------------
    // Constructor
    TileBonus(Vector2d position, char character, Game &board);

    //--------------------------------------------------------------------------
    // Called when the player enters a tile
    // @param source_position The initial player position
    // @return EnterResult Tells if it was a valid/invalid move or if the
    //         player should move again (call enter on the new tile again,
    //         needed for the ice tile)
    EnterResult enter(Vector2d &source_position);

    //--------------------------------------------------------------------------
    // Called when a tile should be reset, e.g. during a map reset
    void reset();

    //--------------------------------------------------------------------------
    // Called when a tile should be reset, e.g. during a map reset
    // @param original
    // @return char Representing the tile on the map
    virtual char toChar(bool original = true);
};


#endif //MAZE_ALL_TILEBONUS_H
