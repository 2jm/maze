//------------------------------------------------------------------------------
// Game.h
//
// Group: Group 13624, study assistant Angela Promitzer
//
// Authors: Jonas Juffinger (1531253)
//          Matthias Klotz (1530653)
//          Johannes Kopf (1431505)
//------------------------------------------------------------------------------
//

#ifndef MAZE_GAME_H
#define MAZE_GAME_H

#include <string>
#include "Map.h"
#include "Player.h"
#include "Message.h"

//------------------------------------------------------------------------------
// Game class
//
//
//
//
//
class Game
{
  public:
    enum State
    {
      NO_MAZE_LOADED,
      TESTING_MAP,
      LOADING,
      PLAYING,
      WON,
      NO_MORE_STEPS
    };

  private:
    Map play_map_, load_test_map_, *map_;
    Player play_player_, load_test_player_, *player_;
    int play_steps_left_, load_test_steps_left_, *steps_left_,
            initial_steps_left_;
    State game_state_;
    std::string auto_save_filename_;
    std::vector<Direction> move_history_, fast_move_move_history_;
    bool fast_moving_;

    int loadAvailableSteps(std::ifstream &input_file);
    std::string loadMapString(std::ifstream &input_file);
    Message::Code doInitialFastMove(std::string &saved_moves);

    void autoSave();

  public:
    Game();

    //--------------------------------------------------------------------------
    // Set auto save method
    // When this method is called the game should be saved after each step in
    // file file_name
    //
    // @param string with savingpath
    //
    void setAutoSave(const std::string file_name);

    //--------------------------------------------------------------------------
    // Load file method
    // Loads the file file_name
    //
    // @param string with loadingpath
    //
    // @return MessageCode FILE_COULD_NOT_BE_OPENED,
    //                     INVALID_FILE,
    //                     INVALID_FILE,
    //                     SUCCESS
    //
    Message::Code loadFile(const std::string file_name);

    //--------------------------------------------------------------------------
    // Load file method
    // Loads the file file_name
    //
    // @param string with savingpath
    //
    // @return MessageCode FILE_COULD_NOT_BE_WRITTEN,
    //                     SUCCESS
    //
    Message::Code saveFile(const std::string file_name);

    //--------------------------------------------------------------------------
    // Move player method
    // move the player by direction
    //
    // @param direction in which the player should be moved
    //
    // @return MessageCode INVALID_MOVE,
    //                     NO_MORE_STEPS,
    //                     NO_MAZE_LOADED,
    //                     SUCCESS
    //
    Message::Code movePlayer(const Direction direction);

    //--------------------------------------------------------------------------
    // Sets fastmoving true if a maze is loaded
    //
    // @return MessageCode true if a maze is loaded
    //                     false if no maze is loaded
    //
    bool startFastMove();

    //--------------------------------------------------------------------------
    // Sets fastmoving false and writes fast_move_history into move_history
    //
    void completeFastMove();

    //--------------------------------------------------------------------------
    // Resets the Map to start status and redos the move_history
    //
    void cancelFastMove();


    void reset();

    void fullReset();

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
