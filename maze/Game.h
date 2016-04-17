//
// Created by jonas on 3/25/16.
//

#ifndef MAZE_GAME_H
#define MAZE_GAME_H


#include <string>
#include "Map.h"
#include "Player.h"
#include "Message.h"

class Game
{
  public:
    enum State
    {
      NO_MAZE_LOADED,
      LOADING,
      PLAYING,
      WON,
      NO_MOVES_LEFT
    };

  private:
    Map play_map_, load_test_map_, *map_;
    Player play_player_, load_test_player_, *player_;
    int play_steps_left_, load_test_steps_left, *steps_left_, initial_steps_left_;
    State game_state_;
    std::string auto_save_filename_;
    std::vector<Direction> move_history_, fast_move_move_history;
    bool fast_moving_;

    int loadAvailableSteps(std::ifstream &input_file);
    std::string loadMapString(std::ifstream &input_file);
    Message::Code doInitialFastMove(std::string &saved_moves);

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
    Message::Code loadFile(std::string file_name);

    //--------------------------------------------------------------------------
    // Load file method
    // Loads the file file_name
    //
    Message::Code saveFile(std::string file_name);

    //--------------------------------------------------------------------------
    // Move player method
    // move the player by direction
    //
    bool movePlayer(Direction direction);

    bool startFastMove();

    void completeFastMove();

    void cancelFastMove();

    void reset();

    void show(bool show_more = false);

    State getState()
    {
      return game_state_;
    }

    void wonGame()
    {
      game_state_ = State::WON;
    }

    void lostGame()
    {
      game_state_ = State::NO_MOVES_LEFT;
    }

    int getStepsLeft()
    {
      return *steps_left_;
    }

    void setStepsLeft(int steps_left)
    {
      // TODO: what is if int overflow occures? check that?
      if(steps_left < 0)
        steps_left = 0;
      *steps_left_ = steps_left;
    }

    // TODO: only needed for test cases!
    Player &getPlayer()
    {
        return *player_;
    }
};


#endif //MAZE_GAME_H
