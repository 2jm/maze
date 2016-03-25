//
// Created by jonas on 3/25/16.
//

#include "Game.h"
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
    // todo throw exception
    std::cout << "[ERR] File could not be opened.\n" << std::endl;
  }

  std::getline(input_file, saved_moves);
  std::getline(input_file, available_steps);

  // read the map
  // calculate the size of the map in bytes
  long map_start = input_file.tellg();
  input_file.seekg(0, std::ios::end);
  long map_size = input_file.tellg() - map_start;
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








