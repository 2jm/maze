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
// This class holds the complete game with it's map and the player. It loads the
// files, counts the steps and lets the user win or loose.
//
class Game
{
  public:
    //--------------------------------------------------------------------------
    // State enum
    //
    // The game works like a state machine. When the game is started the state
    // is NO_MAZE_LOADED.
    // When the user loads a map the first thing Game does is testing the map
    // if it is valid. While doing this it is in the sate TESTING_MAP.
    // When the file is valid it loads the map to be playable while in state
    // LOADING.
    // After the map is loaded the state is PLAYING till such time as the user
    // wins the game -> state WON or no more steps are available -> state
    // NO_MORE_STEPS
    // The reset command brings the game back to the state PLAYING.
    // Loading a new file brings the game to state TESTING_MAP.
    //
    // PREVIOUS it no state it is used to switch to the previous state.
    //
    enum class State
    {
      NO_MAZE_LOADED,
      TESTING_MAP,
      LOADING,
      PLAYING,
      WON,
      NO_MORE_STEPS,
      PREVIOUS
    };

  private:
    //--------------------------------------------------------------------------
    // Private deleted copy constructor
    //
    Game(const Game &) = delete;

    //--------------------------------------------------------------------------
    // Private deleted assignment operator
    //
    Game &operator=(const Game &) = delete;

    //--------------------------------------------------------------------------
    // For map, player and steps left (now *) exists a object play_* and
    // load_test_* and a pointer *, for the following reason:
    // While the game is loading a file it first tests it if it is valid.
    // During the TESTING_MAP state the pointers * point to the load_test_*
    // objects and so all operations are performed on these.
    // When the file testing is finished and the file is valid, the pointers *
    // are changed to point to the play_* objects.
    // Now the load operations are performed on these and when they are finished
    // the user plays with the play_* objects.
    //
    Map play_map_, load_test_map_, *map_;
    Player play_player_, load_test_player_, *player_;
    int play_remaining_steps_, load_test_remaining_steps_, *remaining_steps_;

    //--------------------------------------------------------------------------
    // Available steps left for the player to move
    //
    int available_steps_;

    //--------------------------------------------------------------------------
    // In previous_game_state_ is the previous game state saved. It is used by
    // switchState(PREVIOUS)
    //
    State game_state_, previous_game_state_;

    //--------------------------------------------------------------------------
    // If auto_save_filename_ is empty no auto save is made, if it is not empty
    // the game is auto saved to the file.
    //
    std::string auto_save_filename_;

    //--------------------------------------------------------------------------
    // The move_history_ contains all valid steps the user made.
    // The fast_move_move_history_ contains all steps of a single fast move.
    //
    std::vector<Direction> move_history_, fast_move_move_history_;

    //--------------------------------------------------------------------------
    // If fast_moving_ is true no implicit show or auto save is executed after a
    // valid move.
    //
    bool fast_moving_;

    //--------------------------------------------------------------------------
    // Constant the method loadAvailableSteps(std::ifstream &input_file) can
    // return.
    //
    const int INVALID_AVAILABLE_STEPS = -1;

    //--------------------------------------------------------------------------
    // Loads number of available steps out of a file
    //
    // @param input_file string of the input file
    //
    int loadAvailableSteps(std::ifstream &input_file);

    //--------------------------------------------------------------------------
    // Loads number of available steps out of a file
    //
    // @param input_file string of the input file
    //
    std::string loadMapString(std::ifstream &input_file);

    //--------------------------------------------------------------------------
    // Run the fastmove command with the saved moves in a file, while the file
    // is loading.
    //
    // @param saved_moves The moves saved in the file.
    //
    Message::Code doInitialFastMove(std::string &saved_moves);

    //--------------------------------------------------------------------------
    // Checks if auto_save_filename_ is empty and saves the file if it's not.
    // This method is called after a successful load, move or reset.
    //
    void autoSave();

    //--------------------------------------------------------------------------
    // Switches the state of game.
    //
    // @param new_state The new state
    //
    void switchState(State new_state);

  public:
    //--------------------------------------------------------------------------
    // Constructor
    //
    Game();

    //--------------------------------------------------------------------------
    // Destructor
    //
    ~Game();

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

    //--------------------------------------------------------------------------
    // Resets the Map to start status
    //
    void reset();

    //--------------------------------------------------------------------------
    // Resets the Map to start status and clears the move_history
    //
    Message::Code fullReset();

    //--------------------------------------------------------------------------
    // Prints the complete map with the actual player position
    //
    // @param show_more set to false that no additional information is printed
    //                  out
    // @param show_no_path set to false that moved steps is printed out
    //
    Message::Code show(const bool show_more = false,
                       const bool show_no_path = false);

    //--------------------------------------------------------------------------
    // Prints the complete map with the actual player position
    //
    // @param silent set to false that the found path is printed out
    //
    Message::Code solve(const bool silent = false);


    //--------------------------------------------------------------------------
    // Sets the game state to WON if it is allowed
    //
    void wonGame();

    //--------------------------------------------------------------------------
    // Sets the game state to NO_MORE_STEPS
    //
    void lostGame();

    //--------------------------------------------------------------------------
    // Getter Methods
    //
    int getRemainingSteps() const;

    //--------------------------------------------------------------------------
    // Setter Methods
    //
    void setRemainingSteps(int remaining_steps);

    //--------------------------------------------------------------------------
    // Decrement steps left
    //
    // @param amount The amount to decrement the steps left
    //
    void decrementRemainingSteps(int amount);

    int dijk(int A, int B, std::vector<std::vector<int>> adj, std::string
    &path, Vector2d size_vector);

    int getPathCost(char tile_char) const;
};


#endif //MAZE_GAME_H
