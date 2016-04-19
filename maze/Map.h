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
    Matrix &matrix_;
    bool is_loaded_;
    Tile *start_tile_, *end_tile_;
    int start_once_, end_once_;     //-1 --> doesn't exist; 0 --> exists once
    int teleporter_pair_[26];       //-1 --> doesn't exist; 0 --> exists once; 1 --> exists twice, size is 26 -> every char of the alphabet


  public:
    Map();

    bool loadFromString(std::string map_string, Game &game);

    // use static_cast<std::string>(matrix) instead
    std::string toStringWithPlayer(Vector2d player_position);

    void clear();

    void reset();

    bool isLoaded()
    {
      return is_loaded_;
    }

    bool check();

    Tile* getEndTile() const
    {
        return end_tile_;
    }

    Tile* getStartTile() const
    {
        return start_tile_;
    }
};


#endif //MAZE_MAP_H
