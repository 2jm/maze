//
// Created by jonas on 3/25/16.
//

#ifndef MAZE_GAME_H
#define MAZE_GAME_H


#include "Map.h"
#include "Player.h"
#include "GameState.h"

class Game
{
  private:
    Map map_;
    Player player_;
    int steps_left_;
    GameState game_state_;

  public:
    Game();
};


#endif //MAZE_GAME_H
