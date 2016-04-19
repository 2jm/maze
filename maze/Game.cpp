//
// Created by jonas on 3/25/16.
//

#include "Game.h"
#include <iostream>
#include <fstream>
#include <string>
#include "Message.h"
#include "CommandFastMove.h"
#include "Convert.h"

Game::Game() : map_(&play_map_),
               play_player_(play_map_),
               load_test_player_(load_test_map_),
               player_(&play_player_),
               game_state_(Game::NO_MAZE_LOADED),
               fast_moving_(false)
{

}


void Game::setAutoSave(std::string file_name)
{
  auto_save_filename_ = file_name;
}


Message::Code Game::loadFile(std::string file_name)
{
  std::string saved_moves;
  Message::Code return_code;
  int steps_left;
  std::string map_string;

  std::ifstream input_file(file_name, std::ifstream::binary);

  if(input_file.fail())
    return Message::print(Message::FILE_COULD_NOT_BE_OPENED);

  std::getline(input_file, saved_moves);

  if((steps_left = loadAvailableSteps(input_file)) == -1)
    return Message::print(Message::INVALID_FILE);

  if((map_string = loadMapString(input_file)) == "")
    return Message::print(Message::INVALID_FILE);

  steps_left_ = &load_test_steps_left;
  *steps_left_ = steps_left;
  map_ = &load_test_map_;

  if(!map_->loadFromString(map_string, *this))
  {
    map_ = &play_map_;
    return Message::print(Message::INVALID_FILE);
  }

  player_ = &load_test_player_;

  State previous_game_state = game_state_;
  game_state_ = State::LOADING;

  if((return_code = doInitialFastMove(saved_moves)) != Message::SUCCESS)
  {
    map_ = &play_map_;
    player_ = &play_player_;
    game_state_ = previous_game_state;
    return Message::print(return_code);
  }

  steps_left_ = &play_steps_left_;
  map_ = &play_map_;
  player_ = &play_player_;

  *steps_left_ = steps_left;
  map_->loadFromString(map_string, *this);
  doInitialFastMove(saved_moves);

  game_state_ = State::PLAYING;

  return Message::SUCCESS;
}


Message::Code Game::saveFile(std::string file_name)
{
  std::ofstream
          output_file(file_name, std::ifstream::binary | std::ofstream::trunc);

  if(output_file.fail())
    return Message::print(Message::FILE_COULD_NOT_BE_WRITTEN);

  for(auto move : move_history_)
    output_file << static_cast<char>(move);
  output_file << '\n';

  output_file << *steps_left_ << '\n';

  output_file << static_cast<std::string>(play_map_);

  return Message::SUCCESS;
}


bool Game::movePlayer(Direction direction)
{
  // TODO: only move, when Game hasn't been already won!
  if(game_state_ == Game::NO_MORE_STEPS)
  {
    Message::print(Message::NO_MORE_STEPS);
    reset();
    return true;
  }

  if(game_state_ == Game::NO_MAZE_LOADED)
  {
    Message::print(Message::NO_MAZE_LOADED);
    return true;
  }

  if(fast_moving_ && player_->move(direction))
  {
    (*steps_left_)--;
    fast_move_move_history_.push_back(direction);
    return true;
  }
  else if(!fast_moving_ && player_->move(direction))
  {
    // decrement 1 step for a single move
    (*steps_left_)--;

    //TODO: game lost when no steps are left and game hasn't been won
    if(game_state_ != Game::WON && *steps_left_ <= 0) // steps_left_ could be -1, if Quicksand has already set the step left counter to 0
    {
      lostGame();
      return true;
    }
    move_history_.push_back(direction);

    show();

    if(auto_save_filename_ != "")
      saveFile(auto_save_filename_);

    return true;
  }

  return false;
}


bool Game::startFastMove()
{
  if(game_state_ == Game::NO_MAZE_LOADED)
    return false;

  fast_moving_ = true;

  return true;
}


void Game::completeFastMove()
{
  fast_moving_ = false;
  for(auto move : fast_move_move_history_)
    move_history_.push_back(move);

  if(game_state_ != Game::LOADING)
    show();
}


void Game::cancelFastMove()
{
  //reset the game
  *steps_left_ = initial_steps_left_;
  map_->reset();
  player_->setPosition(play_map_.getStartTile()->getPosition());

  //redo all moves
  for(auto direction : move_history_)
    movePlayer(direction);

  fast_moving_ = false;
}

void Game::reset()
{
  map_->clear();
  game_state_ = Game::NO_MAZE_LOADED;
}

void Game::show(bool show_more)
{
  if(show_more)
  {
    std::cout << "Remaining Steps: " << *steps_left_ << '\n';
    std::cout << "Moved Steps: ";
    for(auto move : move_history_)
      std::cout << static_cast<char>(move);
    std::cout << '\n';
  }
  //std::cout << player_.getPosition().x() << " " << player_.getPosition().y() << std::endl;
  std::cout << map_->toStringWithPlayer(player_->getPosition());
}



Game::State Game::getState()
{
  return game_state_;
}

void Game::wonGame()
{
  game_state_ = State::WON;
}

void Game::lostGame()
{
  game_state_ = State::NO_MORE_STEPS;
}

int Game::getStepsLeft()
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
Player& Game::getPlayer()
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
    available_steps = Convert::toUInt(available_steps_string);
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
  long map_start = input_file.tellg();
  input_file.seekg(0, std::ios::end);
  unsigned long map_size = static_cast<unsigned long>(input_file.tellg() - map_start);

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

  State previous_game_state = game_state_;
  game_state_ = Game::LOADING;

  if(saved_moves != "")
  {
    CommandFastMove fastMove;
    std::vector<std::string> fast_move_params;
    fast_move_params.push_back(saved_moves);

    if(fastMove.execute(*this, fast_move_params) != Message::SUCCESS)
    {
      game_state_ = previous_game_state;
      return Message::print(Message::INVALID_PATH);
    }
  }
}



















