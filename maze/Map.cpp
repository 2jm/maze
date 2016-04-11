//
// Created by jonas on 3/25/16.
//

#include "Map.h"

using std::string;

bool Map::loadFromString(string map_string)
{
  //jede Zeile des Spielfelds muss mit # aufhören.
  is_loaded_ = true;
  return true;
}

string Map::saveToString()
{
  string res;
  return "";
}

void Map::clear()
{
  // remove the map
  is_loaded_ = false;
}

void Map::check(std::string map_string)
{
  int map_char = 0;
  int lines = 0;
  int line_length;
  int pair_nr;
  int line_pos;
  start_once_ = -1;
  end_once_ = -1;

  while(map_string[map_char] != '\n')  //check if the first line is a wall, and get the line_length
  {
    if(map_string[map_char] != '#')
      Message::print(ResultCode::INVALID_FILE);
    map_char++;
  }

  line_length = map_char;
  map_char++;  //increment to jump over the \n

  while (map_char < map_string.length())
  {
    //check if the first sign in line is a wall
    if(map_string[map_char] != '#')
      Message::print(ResultCode::INVALID_FILE);



    wall_only_ = 0;
    for (line_pos = 0; line_pos < line_length; ++line_pos)
    {
      wall_only_=1;
      if(map_string[map_char] == '#')    //check if only wall in one line(just important for last line)
        wall_only_ = 0;
      else if(map_string[map_char] >= 'A' && map_string[map_char] <= 'Z')
      {
        pair_nr= map_string[map_char] - 65;  //character - ascii(A)
        teleporter_pair_[pair_nr]++;
      }
      else if(map_string[map_char] == 'o')
      {
        start_once_++;
        //set start_Tile_
      }
      else if(map_string[map_char] == 'x')
      {
        end_once_++;
        //set end_Tile_
      }
      else if(map_string[map_char] <= 'a' && map_string[map_char] <= 'z')
      {
        Message::print(ResultCode::INVALID_FILE);
      }


      map_char++;
    }


    //check if the last sign in line(one before the \n) is a wall
    if(map_string[map_char-1] != '#')
      Message::print(ResultCode::INVALID_FILE);
    //check if line length is correct
    if(map_string[map_char] != '\n')
      Message::print(ResultCode::INVALID_FILE);
    //check if exact one start-tile
    if(start_once_ != 0)
      Message::print(ResultCode::INVALID_FILE);
    //check if exact one end-tile
    if(end_once_ != 0)
      Message::print(ResultCode::INVALID_FILE);
    //check if if teleporter_pairs are correct
    for(int i = 0; i < 26; i++)
    {
      if(teleporter_pair_[i] != -1 && teleporter_pair_[i] != 1)
      {
        Message::print(ResultCode::INVALID_FILE);
        break;
      }

    }

    lines++; //number of lines
    map_char++; //increment to jump over the \n
  }


  //the last line needs to be a wall
  if(wall_only_ != 0)
    Message::print(ResultCode::INVALID_FILE);
}

Tile Map::getTeleporterPair(char name) // returns the corresponding second match of the teleporter tile with the given name
{
  int pair_count = name - 65; // 'A' = 65, 'B' = 66, ..
  if(teleporter_pair_[pair_count] == 1) // exsits twice
  {
    std::map<int, int>::iterator pair_iterator = teleporter_pair_map_.find(pair_count);
    if(pair_iterator != teleporter_pair_map_.end()) // found value by key
    {
      int matching_teleporter = pair_iterator->second;
      int row = matching_teleporter / this->getSize().x();
      int col = matching_teleporter % this->getSize().x();
      return this->at(row, col);
    }
  }
  else if(teleporter_pair_[pair_count] == 0) // exists once
  {

  }
  else if(teleporter_pair_[pair_count] == -1) // doesn't exist
  {

  }
}


