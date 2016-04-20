//
// Created by jonas on 3/25/16.
//

#ifndef MAZE_MAP_H
#define MAZE_MAP_H

#include <string>
#include <memory>
#include "Matrix.h"
#include "Tile.h"
#include "Message.h"

class Game;

class Map : public Matrix<std::shared_ptr<Tile>>
{
  private:
    Matrix &matrix_;
    bool is_loaded_;
    std::shared_ptr<Tile> start_tile_, end_tile_;
    int start_once_, end_once_;     //-1 --> doesn't exist; 0 --> exists once
    int teleporter_pair_[26];       //-1 --> doesn't exist; 0 --> exists once; 1 --> exists twice, size is 26 -> every char of the alphabet

    bool check();

  public:
    Map();

    bool loadFromString(std::string map_string, Game &game);

    operator std::string() const;

    std::string toStringWithPlayer(Vector2d player_position);

    void clear();

    void reset();

    bool isLoaded() const;

    std::shared_ptr<Tile> getEndTile() const;

    std::shared_ptr<Tile> getStartTile() const;
};


#endif //MAZE_MAP_H
