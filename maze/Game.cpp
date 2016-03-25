//
// Created by jonas on 3/25/16.
//

#include "Game.h"
#include "FileLoadException.h"
#include <iostream>
#include <fstream>

Game::Game() : player_(map_)
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
  {
    throw FileLoadException(FileLoadException::COULD_NOT_BE_OPENED);
  }

  std::getline(input_file, saved_moves);


  std::getline(input_file, available_steps);
  if(available_steps == "")
    throw FileLoadException(FileLoadException::INVALID_FILE);

  try //convert available_steps
  {
    steps_left_ = std::stoi(available_steps);

    if(steps_left_ < 0)
      throw std::exception();
  }
  catch(const std::exception &e)
  {
    throw FileLoadException(FileLoadException::INVALID_FILE);
  }


  // read the map
  // calculate the size of the map in bytes
  long map_start = input_file.tellg();
  input_file.seekg(0, std::ios::end);
  long map_size = input_file.tellg() - map_start;

  if(map_size == 0)
  {
    throw FileLoadException(FileLoadException::INVALID_FILE);
  }

  // resize the map_string to this size
  map_string.resize(map_size);
  // read the map into the string, starting from where the map starts
  input_file.seekg(map_start);
  input_file.read(&map_string[0], map_size);
  // close the file
  input_file.close();
}

void Game::saveFile(std::string file_name)
{

}

void Game::movePlayer(Direction direction)
{
  player_.move(direction);

  move_history_.push_back(direction);

  if(auto_save_filename_ != "")
    saveFile(auto_save_filename_);
}








