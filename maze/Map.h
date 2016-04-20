//------------------------------------------------------------------------------
// <Filename>.cpp
//
// Group: Group 13624, study assistant Angela Promitzer
//
// Authors: Jonas Juffinger (1531253)
// Matthias Klotz (1530653)
// Johannes Kopf (1431505)
//------------------------------------------------------------------------------
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
