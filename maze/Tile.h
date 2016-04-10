//
// Created by jonas on 3/25/16.
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
    //TileType tileType_;
    //int add_;
  public:
    //Tile(TileType tiletype);

    // return value tells, if on the new tile enter should be called again (needed for the ice tile, if the player should move from tile to tile without having a chance to interact (move) again
    virtual bool enter(Vector2d source_position, Vector2d new_position);
};


#endif //MAZE_TILE_H
