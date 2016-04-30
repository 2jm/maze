//------------------------------------------------------------------------------
// Game.cpp
//
// Group: Group 13624, study assistant Angela Promitzer
//
// Authors: Jonas Juffinger (1531253)
//          Matthias Klotz (1530653)
//          Johannes Kopf (1431505)
//------------------------------------------------------------------------------
//

#include <fstream>
#include <iostream>
#include "Game.h"
#include "CommandFastMove.h"
#include "Convert.h"
#include "FileHandler.h"

//------------------------------------------------------------------------------
Game::Game() : map_(&play_map_),
               play_player_(play_map_),
               load_test_player_(load_test_map_),
               player_(&play_player_),
               game_state_(State::NO_MAZE_LOADED),
               fast_moving_(false)
{

}

//------------------------------------------------------------------------------
Game::~Game()
{

}

//------------------------------------------------------------------------------
Message::Code Game::loadFile(const std::string file_name)
{
  std::string saved_moves;
  Message::Code return_code;
  int steps_left;
  std::string map_string;

  std::ifstream input_file;
  if((return_code = FileHandler::getInputFile(file_name, input_file))
      != Message::SUCCESS)
    return return_code;

  std::getline(input_file, saved_moves);

  if((steps_left = loadAvailableSteps(input_file)) == -1)
    return Message::INVALID_FILE;

  if((map_string = loadMapString(input_file)) == "")
    return Message::INVALID_FILE;

  switchState(State::TESTING_MAP);
  *remaining_steps_ = steps_left;

  if(!map_->loadFromString(map_string, *this))
  {
    switchState(State::PREVIOUS);
    return Message::INVALID_FILE;
  }

  if((return_code = doInitialFastMove(saved_moves)) != Message::SUCCESS)
  {
    switchState(State::PREVIOUS);
    return return_code;
  }

  switchState(State::LOADING);

  *remaining_steps_ = steps_left;
  available_steps_ = steps_left;

  // we already know that the file is valid
  map_->loadFromString(map_string, *this);
  doInitialFastMove(saved_moves);

  if(game_state_ != State::WON)
    switchState(State::PLAYING);

  autoSave();
  show();

  if(game_state_ == State::WON)
    Message::print(Message::WON);

  return Message::SUCCESS;
}

//------------------------------------------------------------------------------
Message::Code Game::saveFile(const std::string file_name)
{
  if(game_state_ == State::NO_MAZE_LOADED)
    return Message::NO_MAZE_LOADED;

  Message::Code return_code;

  std::ofstream output_file;
  if((return_code = FileHandler::getOutputFile(file_name, output_file))
     != Message::SUCCESS)
    return return_code;

  for(auto move : move_history_)
    output_file << static_cast<char>(move);
  output_file << '\n';

  output_file << available_steps_ << '\n';

  output_file << play_map_.toString(true);

  return Message::SUCCESS;
}

//------------------------------------------------------------------------------
Message::Code Game::movePlayer(const Direction direction)
{
  if(game_state_ == State::WON)
    return Message::INVALID_MOVE;

  if(game_state_ == State::NO_MORE_STEPS)
  {
    fullReset();
    return Message::NO_MORE_STEPS;
  }

  if(game_state_ == State::NO_MAZE_LOADED)
    return Message::NO_MAZE_LOADED;


  if(fast_moving_ && player_->move(direction))
  {
    (*remaining_steps_)--;

    if(*remaining_steps_ < 0)
      return Message::INVALID_MOVE;

    fast_move_move_history_.push_back(direction);
    return Message::SUCCESS;
  }
  else if(!fast_moving_ && player_->move(direction))
  {
    // decrement 1 step for a single move
    (*remaining_steps_)--;

    if(game_state_ != State::WON && *remaining_steps_ <= 0)
      lostGame();

    move_history_.push_back(direction);
    autoSave();
    show();

    if(game_state_ == State::WON)
      Message::print(Message::WON);

    return Message::SUCCESS;
  }

  return Message::INVALID_MOVE;
}

//------------------------------------------------------------------------------
bool Game::startFastMove()
{
  if(game_state_ == State::NO_MAZE_LOADED)
    return false;

  fast_moving_ = true;
  fast_move_move_history_.clear();

  return true;
}

//------------------------------------------------------------------------------
void Game::completeFastMove()
{
  fast_moving_ = false;

  if(game_state_ != State::TESTING_MAP)
  {
    for(auto move : fast_move_move_history_)
      move_history_.push_back(move);
  }

  if(game_state_ != State::LOADING && game_state_ != State::TESTING_MAP)
  {
    autoSave();
    show();
  }

  if(player_->getPosition() == map_->getEndTile()->getPosition())
  {
    if(game_state_ != State::LOADING && game_state_ != State::TESTING_MAP)
      Message::print(Message::WON);

    wonGame();
  }
  else if(*remaining_steps_ <= 0)
    lostGame();
}

//------------------------------------------------------------------------------
void Game::cancelFastMove()
{
  if(game_state_ == State::WON)
    return;

  reset();

  //redo all moves
  for(auto direction : move_history_)
    movePlayer(direction);

  fast_moving_ = false;
}

//------------------------------------------------------------------------------
void Game::reset()
{
  *remaining_steps_ = available_steps_;
  map_->reset();
  player_->setPosition(map_->getStartTile()->getPosition());
}

//------------------------------------------------------------------------------
Message::Code Game::fullReset()
{
  if(game_state_ == State::NO_MAZE_LOADED)
    return Message::NO_MAZE_LOADED;

  reset();
  move_history_.clear();
  autoSave();
  switchState(State::PLAYING);

  return Message::SUCCESS;
}

//------------------------------------------------------------------------------
void Game::setAutoSave(const std::string file_name)
{
  auto_save_filename_ = file_name;

  if(game_state_ == State::PLAYING)
    autoSave();
}

//------------------------------------------------------------------------------
Message::Code Game::show(const bool show_more)
{
  if(game_state_ == State::NO_MAZE_LOADED)
    return Message::NO_MAZE_LOADED;

  if(show_more)
  {
    Message::print(Message::REMAINING_STEPS);
    std::cout << *remaining_steps_ << '\n';

    Message::print(Message::MOVED_STEPS);
    for(auto move : move_history_)
      std::cout << static_cast<char>(move);
    std::cout << '\n';
  }

  std::cout << map_->toStringWithPlayer(player_->getPosition());

  return Message::SUCCESS;
}

//------------------------------------------------------------------------------
Game::State Game::getState() const
{
  return game_state_;
}

//------------------------------------------------------------------------------
void Game::wonGame()
{
  if(!fast_moving_ && game_state_ != State::TESTING_MAP)
    switchState(State::WON);
}

//------------------------------------------------------------------------------
void Game::lostGame()
{
  switchState(State::NO_MORE_STEPS);

}

//------------------------------------------------------------------------------
int Game::getStepsLeft() const
{
  return *remaining_steps_;
}

//------------------------------------------------------------------------------
void Game::setStepsLeft(int steps_left)
{
  if(steps_left < 0)
    steps_left = 0;
  *remaining_steps_ = steps_left;
}

//------------------------------------------------------------------------------
int Game::loadAvailableSteps(std::ifstream &input_file)
{
  std::string available_steps_string;

  std::getline(input_file, available_steps_string);
  if(available_steps_string == "")
    return INVALID_AVAILABLE_STEPS;

  try //convert available_steps
  {
    int available_steps;
    available_steps = Convert::toUnsignedInt(available_steps_string);

    if(available_steps == 0)
      return INVALID_AVAILABLE_STEPS;

    return available_steps;
  }
  catch(const std::exception &e)
  {
    return INVALID_AVAILABLE_STEPS;
  }
}

//------------------------------------------------------------------------------
std::string Game::loadMapString(std::ifstream &input_file)
{
  std::string map_string;
  // read the map
  // calculate the size of the map in bytes
  std::streampos map_start = input_file.tellg();
  input_file.seekg(0, std::ios::end);
  unsigned long map_size =
          static_cast<unsigned long>(input_file.tellg() - map_start);

  if(map_size == 0)
    return "";

  // resize the map_string to this size
  map_string.resize(map_size);
  // read the map into the string, starting from where the map starts
  input_file.seekg(map_start);
  input_file.read(&map_string[0], map_size);
  // close the file
  input_file.close();

  if(map_string.back() != '\n')
    return "";

  return map_string;
}

//------------------------------------------------------------------------------
Message::Code Game::doInitialFastMove(std::string &saved_moves)
{
  player_->setPosition(map_->getStartTile()->getPosition());

  if(saved_moves != "")
  {
    CommandFastMove fastMove;
    std::vector<std::string> fast_move_params;
    fast_move_params.push_back(saved_moves);

    Message::Code return_code;

    if((return_code = fastMove.execute(*this, fast_move_params))
       != Message::SUCCESS)
    {
      if(game_state_ == State::TESTING_MAP)
      {
        if(return_code == Message::WRONG_PARAMETER)
          return_code = Message::INVALID_FILE;

        if(return_code == Message::INVALID_MOVE)
          return_code = Message::INVALID_PATH;
      }
      return return_code;
    }
  }
  return Message::SUCCESS;
}

//------------------------------------------------------------------------------
void Game::autoSave()
{
  if(auto_save_filename_ != "")
    Message::print(saveFile(auto_save_filename_));
}

//------------------------------------------------------------------------------
void Game::switchState(State new_state)
{
  if(new_state != State::PREVIOUS)
    previous_game_state_ = game_state_;

  switch(new_state)
  {
    case State::NO_MAZE_LOADED:
      break;

    case State::TESTING_MAP:
      map_ = &load_test_map_;
      player_ = &load_test_player_;
      remaining_steps_ = &load_test_remaining_steps_;
      game_state_ = State::TESTING_MAP;
      break;

    case State::LOADING:
      remaining_steps_ = &play_remaining_steps_;
      map_ = &play_map_;
      player_ = &play_player_;
      game_state_ = State::LOADING;
      move_history_.clear();
      break;

    case State::PLAYING:
      game_state_ = State::PLAYING;
      break;

    case State::WON:
      game_state_ = State::WON;
      break;

    case State::NO_MORE_STEPS:
      game_state_ = State::NO_MORE_STEPS;
      break;

    case State::PREVIOUS:
      switchState(previous_game_state_);
      break;
  }
}
