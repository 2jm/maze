//
// Created by jonas on 3/25/16.
//

#ifndef MAZE_PLAYER_H
#define MAZE_PLAYER_H

#include "Vector2d.h"
#include "Direction.h"

class Map;

class Player
{
  private:
    Vector2d position_;
    Map &map_;

  public:
    Player(Map &map);

    void move(Direction direction);
};


#endif //MAZE_PLAYER_H
