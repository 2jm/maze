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
      NO_MORE_STEPS
    };

  private:
    Map play_map_, load_test_map_, *map_;
    Player play_player_, load_test_player_, *player_;
    int play_steps_left_, load_test_steps_left_, *steps_left_, initial_steps_left_;
    State game_state_;
    std::string auto_save_filename_;
    std::vector<Direction> move_history_, fast_move_move_history_;
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
    void setAutoSave(const std::string file_name);

    //--------------------------------------------------------------------------
    // Load file method
    // Loads the file file_name
    //
    Message::Code loadFile(const std::string file_name);

    //--------------------------------------------------------------------------
    // Load file method
    // Loads the file file_name
    //
    Message::Code saveFile(const std::string file_name);

    //--------------------------------------------------------------------------
    // Move player method
    // move the player by direction
    //
    bool movePlayer(const Direction direction);

    bool startFastMove();

    void completeFastMove();

    void cancelFastMove();

    void reset();

    void show(const bool show_more = false);

    State getState() const;

    void wonGame();

    void lostGame();

    int getStepsLeft() const;

    void setStepsLeft(int steps_left);

    // TODO: only needed for test cases!
    Player &getPlayer() const;
};


#endif //MAZE_GAME_H
