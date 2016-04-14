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

class Game;

class Map : public Matrix<Tile*>
{
  private:
    Matrix &matrix;
    bool is_loaded_;
    Tile *start_tile_, *end_tile_;
    int start_once_, end_once_;     //-1 --> doesn't exist; 0 --> exists once
    bool wall_only_;                //0 if only '#' in this line
    int teleporter_pair_[26];       //-1 --> doesn't exist; 0 --> exists once; 1 --> exists twice, size is 26 -> every char of the alphabet
    std::map<int, int> teleporter_pair_map_; // stores the corresponding teleporter pairs


  public:
    Map() : matrix(*this),
            is_loaded_(false)
    {}

    bool loadFromString(std::string map_string, Game &game);

    // use static_cast<std::string>(matrix) instead
    //std::string saveToString();

    void clear();

    bool isLoaded()
    {
      return is_loaded_;
    }

    void check(std::string map_string);

    Tile* getEndTile()
    {
        return end_tile_;
    }

    Tile* getStartTile()
    {
        return start_tile_;
    }

    Tile* getTeleporterPair(char name);
};


#endif //MAZE_MAP_H
