//
// Created by jonas on 3/25/16.
//

#ifndef MAZE_TILE_H
#define MAZE_TILE_H

#include "Vector2d.h"
#include "Game.h"

enum TileType
{
  Wall, Path, Start, Finish, Ice, Teleport, OneWay, Bonus, Quicksand
};

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
  private:
    Vector2d position_;
    TileType tileType_;
    int add_;

  public:
    Tile(TileType tiletype);
    bool enter(Vector2d sourcePosition, Vector2d newPosition, Game &game);
};


#endif //MAZE_TILE_H
