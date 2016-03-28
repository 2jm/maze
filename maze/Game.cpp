//
// Created by jonas on 3/25/16.
//

#include "Game.h"
#include "FileLoadException.h"
#include <iostream>
#include <fstream>
#include "CommandFastMove.h"

Game::Game() : player_(map_), fast_move_player_copy_(fast_move_map_copy_)
{

}


void Game::setAutoSave(std::string file_name)
{
  auto_save_filename_ = file_name;
}


void Game::loadFile(std::string file_name)
{
  std::string saved_moves;
  std::string available_steps;
  std::string map_string;

  std::ifstream input_file(file_name, std::ifstream::binary);

  if(input_file.fail())
    throw FileLoadException(RESULT_CODE::FILE_COULD_NOT_BE_OPENED);


  std::getline(input_file, saved_moves);

  std::getline(input_file, available_steps);
  if(available_steps == "")
    throw FileLoadException(RESULT_CODE::INVALID_FILE);

  try //convert available_steps
  {
    steps_left_ = std::stoi(available_steps);

    if(steps_left_ < 0)
      throw std::exception();
  }
  catch(const std::exception &e)
  {
    throw FileLoadException(RESULT_CODE::INVALID_FILE);
  }


  // read the map
  // calculate the size of the map in bytes
  long map_start = input_file.tellg();
  input_file.seekg(0, std::ios::end);
  long map_size = input_file.tellg() - map_start;

  if(map_size == 0)
    throw FileLoadException(RESULT_CODE::INVALID_FILE);


  // resize the map_string to this size
  map_string.resize(map_size);
  // read the map into the string, starting from where the map starts
  input_file.seekg(map_start);
  input_file.read(&map_string[0], map_size);
  // close the file
  input_file.close();

  if(!map_.loadFromString(map_string))
    throw FileLoadException(RESULT_CODE::INVALID_FILE);

  CommandFastMove fastMove;
  std::vector<std::string> fast_move_params;
  fast_move_params.push_back(saved_moves);

  if(fastMove.execute(*this, fast_move_params) != RESULT_CODE::SUCCESS)
    throw FileLoadException(RESULT_CODE::INVALID_PATH);
}


void Game::saveFile(std::string file_name)
{
  std::ofstream
          output_file(file_name, std::ifstream::binary | std::ofstream::trunc);

  if(output_file.fail())
    throw FileLoadException(RESULT_CODE::FILE_COULD_NOT_BE_WRITTEN);


  int move_history_index;
  for(move_history_index = 0; move_history_index < move_history_.size();
      move_history_index++)
    output_file << static_cast<char>(move_history_[move_history_index]);
  output_file << '\n';

  output_file << steps_left_ << '\n';

  output_file << map_.saveToString();
}


bool Game::movePlayer(Direction direction)
{
  if(fast_moving_ && fast_move_player_copy_.move(direction))
  {
    fast_move_move_history.push_back(direction);
    return true;
  }
  else if(!fast_moving_ && player_.move(direction))
  {
    move_history_.push_back(direction);

    if(auto_save_filename_ != "")
      saveFile(auto_save_filename_);

    return true;
  }

  return false;
}


void Game::startFastMove()
{
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














