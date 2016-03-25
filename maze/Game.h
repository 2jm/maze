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

    //--------------------------------------------------------------------------
    // Set auto save method
    // When this method is called the game should be saved after each step in
    // file file_name
    //
    void setAutoSave(const char *file_name);

    //--------------------------------------------------------------------------
    // Load file method
    // Loads the file file_name
    //
    void loadFile(const char *file_name);
};


#endif //MAZE_GAME_H
