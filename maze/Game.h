//
// Created by jonas on 3/25/16.
//

#ifndef MAZE_GAME_H
#define MAZE_GAME_H


#include <string>
#include "Map.h"
#include "Player.h"
#include "GameState.h"
#include "ResultCode.h"

class Game
{
  private:
    Map map_, fast_move_map_copy_;
    Player player_, fast_move_player_copy_;
    int steps_left_, fast_moving_steps_left_;
    GameState game_state_;
    std::string auto_save_filename_;
    std::vector<Direction> move_history_, fast_move_move_history;
    bool fast_moving_;

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
    ResultCode loadFile(std::string file_name);

    //--------------------------------------------------------------------------
    // Load file method
    // Loads the file file_name
    //
    ResultCode saveFile(std::string file_name);

    //--------------------------------------------------------------------------
    // Move player method
    // move the player by direction
    //
    bool movePlayer(Direction direction);

    bool startFastMove();

    void completeFastMove();

    void cancelFastMove();

    void reset();

    void show();

    GameState getState()
    {
      return game_state_;
    }

    void wonGame()
    {
      game_state_ = GameState::WON;
    }

    void lostGame()
    {
      game_state_ = GameState::NO_MOVES_LEFT;
    }

    int getStepsLeft()
    {
      return steps_left_;
    }

    void setStepsLeft(int steps_left)
    {
      // TODO: what is if int overflow occures? check that?
      if(steps_left < 0)
        steps_left = 0;
      steps_left_ = steps_left;
    }
};


#endif //MAZE_GAME_H
