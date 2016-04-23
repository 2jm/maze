//------------------------------------------------------------------------------
// Tile.h
//
// Group: Group 13624, study assistant Angela Promitzer
//
// Authors: Jonas Juffinger (1531253)
//          Matthias Klotz (1530653)
//          Johannes Kopf (1431505)
//------------------------------------------------------------------------------
//

#ifndef MAZE_TILE_H
#define MAZE_TILE_H


#include "Vector2d.h"

// Possible tile types:
//    Wall = '#',
//    Path = ' ',
//    Start = 'o',
//    Finish = 'x',
//    Ice = '+',
//    Teleport = 'A-Z',
//    OneWay = '><^v',
//    Bonus = 'a-e',
//    Quicksand ='f-j'

class Tile
{
  protected:
    Vector2d position_;
    char character_;

  public:
    // TODO find better name
    enum EnterResult
    {
      INVALID_MOVE,
      VALID_MOVE,
      MOVE_AGAIN
    };

    Tile(Vector2d position, char character);

    //--------------------------------------------------------------------------
    // Called when the player enters a tile
    // @param source_position The initial player position
    // @return EnterResult Tells if it was a valid/invalid move or if the
    // player should move again (call enter on the new tile again, needed for
    // the ice tile)
    virtual EnterResult enter(Vector2d &source_position) = 0;

    //--------------------------------------------------------------------------
    // Called when the player leaves a tile
    // @param move_direction The current moving direction of the player
    // @return bool Tells if the player is allowed to move away from this tile
    virtual bool leave(const Direction move_direction) const;

    virtual void reset();

    Vector2d getPosition() const;

    virtual char toChar(bool original = true);

    virtual operator char() const;
};


#endif //MAZE_TILE_H
