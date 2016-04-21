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


Game::Game() : map_(&play_map_),
               play_player_(play_map_),
               load_test_player_(load_test_map_),
               player_(&play_player_),
               game_state_(NO_MAZE_LOADED),
               fast_moving_(false)
{

}

Message::Code Game::loadFile(const std::string file_name)
{
  std::string saved_moves;
  Message::Code return_code;
  int steps_left;
  std::string map_string;

  std::ifstream input_file(file_name, std::ifstream::binary);

  if(input_file.fail())
    return Message::FILE_COULD_NOT_BE_OPENED;

  std::getline(input_file, saved_moves);

  if((steps_left = loadAvailableSteps(input_file)) == -1)
    return Message::INVALID_FILE;

  if((map_string = loadMapString(input_file)) == "")
    return Message::INVALID_FILE;

  steps_left_ = &load_test_steps_left_;
  *steps_left_ = steps_left;
  map_ = &load_test_map_;

  State previous_game_state = game_state_;

  game_state_ = State::TESTING_MAP;

  if(!map_->loadFromString(map_string, *this))
  {
    map_ = &play_map_;
    game_state_ = previous_game_state;
    return Message::INVALID_FILE;
  }

  player_ = &load_test_player_;

  if((return_code = doInitialFastMove(saved_moves)) != Message::SUCCESS)
  {
    map_ = &play_map_;
    player_ = &play_player_;
    game_state_ = previous_game_state;
    return return_code;
  }

  game_state_ = State::LOADING;

  steps_left_ = &play_steps_left_;
  map_ = &play_map_;
  player_ = &play_player_;

  *steps_left_ = steps_left;
  initial_steps_left_ = steps_left;
  map_->loadFromString(map_string, *this);
  doInitialFastMove(saved_moves);

  game_state_ = State::PLAYING;

  autoSave();
  show();

  return Message::SUCCESS;
}


Message::Code Game::saveFile(const std::string file_name)
{
  std::ofstream
          output_file(file_name, std::ifstream::binary | std::ofstream::trunc);

  if(output_file.fail())
    return Message::FILE_COULD_NOT_BE_WRITTEN;

  for(auto move : move_history_)
    output_file << static_cast<char>(move);
  output_file << '\n';

  output_file << initial_steps_left_ << '\n';

  output_file << static_cast<std::string>(play_map_);

  return Message::SUCCESS;
}


Message::Code Game::movePlayer(const Direction direction)
{
  // TODO reihenfolge der fehler
  if(game_state_ == WON)
    return Message::INVALID_MOVE;

  if(game_state_ == NO_MORE_STEPS)
  {
    fullReset();
    return Message::NO_MORE_STEPS;
  }

  if(game_state_ == NO_MAZE_LOADED)
    return Message::NO_MAZE_LOADED;


  if(fast_moving_ && player_->move(direction))
  {
    (*steps_left_)--;

    if(*steps_left_ < 0)
      return Message::INVALID_MOVE;

    fast_move_move_history_.push_back(direction);
    return Message::SUCCESS;
  }
  else if(!fast_moving_ && player_->move(direction))
  {
    // decrement 1 step for a single move
    (*steps_left_)--;

    if(game_state_ != WON && *steps_left_ <= 0) // steps_left_ could be -1, if Quicksand has already set the step left counter to 0
      lostGame();

    move_history_.push_back(direction);
    autoSave();
    show();

    if(game_state_ == WON)
      Message::print(Message::WON);

    return Message::SUCCESS;
  }

  return Message::INVALID_MOVE;
}


bool Game::startFastMove()
{
  if(game_state_ == NO_MAZE_LOADED)
    return false;

  fast_moving_ = true;
  fast_move_move_history_.clear();

  return true;
}


void Game::completeFastMove()
{
  fast_moving_ = false;

  if(game_state_ != TESTING_MAP)
  {
    for(auto move : fast_move_move_history_)
      move_history_.push_back(move);
  }

  if(game_state_ != LOADING && game_state_ != TESTING_MAP)
  {
    autoSave();
    show();
  }

  if(player_->getPosition() == map_->getEndTile()->getPosition())
    Message::print(Message::WON);

  else if(*steps_left_ <= 0)
    lostGame();
}


void Game::cancelFastMove()
{
  reset();

  //redo all moves
  for(auto direction : move_history_)
    movePlayer(direction);

  fast_moving_ = false;
}

void Game::reset()
{
  *steps_left_ = initial_steps_left_;
  map_->reset();
  player_->setPosition(map_->getStartTile()->getPosition());
}

void Game::fullReset()
{
  reset();
  move_history_.clear();
  autoSave();
  game_state_ = PLAYING;
}

void Game::setAutoSave(const std::string file_name)
{
  auto_save_filename_ = file_name;

  if(game_state_ == PLAYING)
    autoSave();
}

void Game::show(const bool show_more)
{
  if(show_more)
  {
    // TODO make constants for strings
    std::cout << "Remaining Steps: " << *steps_left_ << '\n';
    std::cout << "Moved Steps: ";
    for(auto move : move_history_)
      std::cout << static_cast<char>(move);
    std::cout << '\n';
  }
  //std::cout << player_.getPosition().x() << " " << player_.getPosition().y() << std::endl;
  std::cout << map_->toStringWithPlayer(player_->getPosition());
}



Game::State Game::getState() const
{
  return game_state_;
}

void Game::wonGame()
{
  if(!fast_moving_)
    game_state_ = WON;
}

void Game::lostGame()
{
  game_state_ = NO_MORE_STEPS;
}

int Game::getStepsLeft() const
{
  return *steps_left_;
}

void Game::setStepsLeft(int steps_left)
{
  // TODO: what is if int overflow occures? check that?
  if(steps_left < 0)
    steps_left = 0;
  *steps_left_ = steps_left;
}

// TODO: only needed for test cases!
Player& Game::getPlayer() const
{
  return *player_;
}



int Game::loadAvailableSteps(std::ifstream &input_file)
{
  std::string available_steps_string;

  std::getline(input_file, available_steps_string);
  if(available_steps_string == "")
    return -1;  // TODO konstante einführen

  try //convert available_steps
  {
    int available_steps;
    available_steps = Convert::toUnsignedInt(available_steps_string);
    return available_steps;
  }
  catch(const std::exception &e)
  {
    return -1;
  }
}

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

Message::Code Game::doInitialFastMove(std::string &saved_moves)
{
  player_->setPosition(map_->getStartTile()->getPosition());

  if(saved_moves != "")
  {
    CommandFastMove fastMove;
    std::vector<std::string> fast_move_params;
    fast_move_params.push_back(saved_moves);

    if(fastMove.execute(*this, fast_move_params) != Message::SUCCESS)
      return Message::print(Message::INVALID_PATH);
  }

  return Message::SUCCESS;
}

void Game::autoSave()
{
  if(auto_save_filename_ != "")
    Message::print(saveFile(auto_save_filename_));
}





















