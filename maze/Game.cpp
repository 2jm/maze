//
// Created by jonas on 3/25/16.
//

#include "Game.h"
#include <iostream>
#include <fstream>
#include "Message.h"
#include "CommandFastMove.h"
#include "Convert.h"

Game::Game() : player_(map_),
               fast_move_player_copy_(fast_move_map_copy_),
               game_state_(GameState::NO_MAZE_LOADED),
               fast_moving_(false)
{

}


void Game::setAutoSave(std::string file_name)
{
  auto_save_filename_ = file_name;
}


ResultCode Game::loadFile(std::string file_name)
{
  std::string saved_moves;
  std::string available_steps;
  std::string map_string;

  std::ifstream input_file(file_name, std::ifstream::binary);

  if(input_file.fail())
    return Message::print(ResultCode::FILE_COULD_NOT_BE_OPENED);


  std::getline(input_file, saved_moves);

  std::getline(input_file, available_steps);
  if(available_steps == "")
    return Message::print(ResultCode::INVALID_FILE);

  try //convert available_steps
  {
    steps_left_ = Convert::toUInt(available_steps);
  }
  catch(const std::exception &e)
  {
    return Message::print(ResultCode::INVALID_FILE);
  }

  // read the map
  // calculate the size of the map in bytes
  long map_start = input_file.tellg();
  input_file.seekg(0, std::ios::end);
  long map_size = input_file.tellg() - map_start;

  if(map_size == 0)
    return Message::print(ResultCode::INVALID_FILE);

  // resize the map_string to this size
  map_string.resize(map_size);
  // read the map into the string, starting from where the map starts
  input_file.seekg(map_start);
  input_file.read(&map_string[0], map_size);
  // close the file
  input_file.close();

  if(!map_.loadFromString(map_string, *this))
    return Message::print(ResultCode::INVALID_FILE);

  player_.setPosition(map_.getStartTile()->getPosition());

  if(saved_moves != "")
  {
    CommandFastMove fastMove;
    std::vector<std::string> fast_move_params;
    fast_move_params.push_back(saved_moves);

    if(fastMove.execute(*this, fast_move_params) != ResultCode::SUCCESS)
      return Message::print(ResultCode::INVALID_PATH);
  }

  game_state_ = GameState::PLAYING;

  return ResultCode::SUCCESS;
}


ResultCode Game::saveFile(std::string file_name)
{
  std::ofstream
          output_file(file_name, std::ifstream::binary | std::ofstream::trunc);

  if(output_file.fail())
    return Message::print(ResultCode::FILE_COULD_NOT_BE_WRITTEN);
  
  for(auto move : move_history_)
    output_file << static_cast<char>(move);
  output_file << '\n';

  output_file << steps_left_ << '\n';

  output_file << static_cast<std::string>(map_);

  return ResultCode::SUCCESS;
}


bool Game::movePlayer(Direction direction)
{
  // TODO: only move, when Game hasn't been already won!

  if(fast_moving_ && fast_move_player_copy_.move(direction))
  {
    fast_move_move_history.push_back(direction);
    return true;
  }
  else if(!fast_moving_ && player_.move(direction))
  {
    // decrement 1 step for a single move
    steps_left_--;

    //TODO: game lost when no steps are left and game hasn't been won
    if(game_state_ != GameState::WON && steps_left_ <= 0) // steps_left_ could be -1, if Quicksand has already set the step left counter to 0
      lostGame();

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
  if(game_state_ == GameState::NO_MAZE_LOADED)
    return false;

  fast_moving_ = true;
  fast_move_map_copy_ = map_;
  fast_move_player_copy_.setPosition(player_.getPosition());
}


void Game::completeFastMove()
{
  fast_moving_ = false;
  map_ = fast_move_map_copy_;
  player_.setPosition(fast_move_player_copy_.getPosition());
  steps_left_ = fast_moving_steps_left_;
  }


void Game::cancelFastMove()
{
  fast_moving_ = false;
}

void Game::reset()
{
  map_.clear();
  game_state_ = GameState::NO_MAZE_LOADED;
}

void Game::show(bool show_more)
{
  if(show_more)
  {
    std::cout << "Remaining Steps: " << steps_left_ << '\n';
    std::cout << "Moved Steps: ";
    for(auto move : move_history_)
      std::cout << static_cast<char>(move);
    std::cout << '\n';
  }
  //std::cout << player_.getPosition().x() << " " << player_.getPosition().y() << std::endl;
  std::cout << map_.toStringWithPlayer(player_.getPosition());
}














