//
// Created by jonas on 3/25/16.
//

#ifndef MAZE_MAP_H
#define MAZE_MAP_H

#include "Matrix.h"
#include "Tile.h"
#include "Message.h"
#include <string>
#include <map>

class Map : public Matrix<Tile>
{
  private:
    bool is_loaded_;
    Tile start_tile_, end_tile_;
    int start_once_, end_once_;     //-1 --> doesn't exist; 0 --> exists once
    bool wall_only_;                //0 if only '#' in this line
    int teleporter_pair_[26];       //-1 --> doesn't exist; 0 --> exists once; 1 --> exists twice, size is 26 -> every char of the alphabet
    std::map<int, int> teleporter_pair_map_; // stores the corresponding teleporter pairs

  public:
    Map() : is_loaded_(false)
    {
    }

    bool loadFromString(std::string map_string);

    std::string saveToString();

    void clear();

    bool isLoaded()
    {
      return is_loaded_;
    }

    void check(std::string map_string);

    Tile getEndTile()
    {
        return end_tile_;
    }

    Tile getStartTile()
    {
        return start_tile_;
    }

    Tile getTeleporterPair(char name) // returns the corresponding second match of the teleporter tile with the given name
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
};


#endif //MAZE_MAP_H
