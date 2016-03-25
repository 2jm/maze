//
// Created by jonas on 3/25/16.
//

#ifndef MAZE_GAME_H
#define MAZE_GAME_H


#include <string>
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
    std::string auto_save_filename_;
    std::vector<Direction> move_history_;

  public:
    Game();

    //--------------------------------------------------------------------------
    // Set auto save method
    // When this method is called the game should be saved after each step in
    // file file_name
    //
    void setAutoSave(std::string file_name);

    //--------------------------------------------------------------------------
    // Load file method
    // Loads the file file_name
    //
    void loadFile(std::string file_name);

    //--------------------------------------------------------------------------
    // Load file method
    // Loads the file file_name
    //
    void saveFile(std::string file_name);

    //--------------------------------------------------------------------------
    // Move player method
    // move the player by direction
    //
    void movePlayer(Direction direction);
};


#endif //MAZE_GAME_H
