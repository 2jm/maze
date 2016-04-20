//------------------------------------------------------------------------------
// Tile.h
//
// Group: Group 13624, study assistant Angela Promitzer
//
// Authors: Jonas Juffinger (1531253)
// Matthias Klotz (1530653)
// Johannes Kopf (1431505)
//------------------------------------------------------------------------------
//

#ifndef MAZE_TILE_H
#define MAZE_TILE_H

#include "Vector2d.h"

//enum class TileType : char
//{
//    Wall = '',
//    Path = ' ',
//    Start = 'o',<
//    Finish = 'x',
//    Ice = '+',
//    Teleport = 'A-Z',
//    OneWay = '><^v',
//    Bonus = 'a-e',
//    Quicksand ='f-j'
//};

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

    // return value tells, if on the new tile enter should be called again (needed for the ice tile, if the player should move from tile to tile without having a chance to interact (move) again
    virtual EnterResult enter(Vector2d &source_position) = 0;

    // return value tells, if the player is allowed to move away from this tile
    virtual bool leave(const Direction move_direction) const;

    Vector2d getPosition() const;

    virtual operator char() const;
};


#endif //MAZE_TILE_H
