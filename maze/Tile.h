//
// Created by jonas on 3/25/16.
//

#ifndef MAZE_TILE_H
#define MAZE_TILE_H

#include <string>
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
    Tile(Vector2d position, char character);

    // return value tells, if on the new tile enter should be called again (needed for the ice tile, if the player should move from tile to tile without having a chance to interact (move) again
    virtual bool enter(Vector2d source_position, Vector2d &new_position) = 0;

    // return value tells, if the player is allowed to move away from this tile
    virtual bool leave(Direction move_direction) const;

    Vector2d getPosition() const;

    virtual operator char() const;
};


#endif //MAZE_TILE_H
