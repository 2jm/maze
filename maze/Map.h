//
// Created by jonas on 3/25/16.
//

#ifndef MAZE_MAP_H
#define MAZE_MAP_H

#include "Matrix.h"
#include "Tile.h"
#include "Message.h"
#include <string>
//#include <string>

class Map : public Matrix<Tile>
{
  //private:

/*  public:
    void loadFromString(std::string string);
    void check();
    Tile getEndTile();
    Tile getStartTile();
    Tile getTeleporterPair(char name);*/

  private:
    bool is_loaded_;
    Tile start_tile_, end_tile_;
    int start_once_, end_once_;     //-1 --> doesn't exist; 0 --> exists once
    bool wall_only_;                //0 if only '#' in this line
    int teleporter_pair_[26];       //-1 --> doesn't exist; 0 --> exists once; 1 --> exists twice

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
};


#endif //MAZE_MAP_H
