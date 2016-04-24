//------------------------------------------------------------------------------
// Map.h
//
// Group: Group 13624, study assistant Angela Promitzer
//
// Authors: Jonas Juffinger (1531253)
//          Matthias Klotz (1530653)
//          Johannes Kopf (1431505)
//------------------------------------------------------------------------------
//

#ifndef MAZE_MAP_H
#define MAZE_MAP_H


#include <string>
#include <memory>
#include "Matrix.h"
#include "Tile.h"

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
    //--------------------------------------------------------------------------
    // Constructor
    //
    Map();

    //--------------------------------------------------------------------------
    // Loads the map out of a string into the game matrix
    //
    // @param map_string string in which the map is saved
    // @param game game object in which the needed matrix exists
    //
    // @return true if it is a valid map
    //
    bool loadFromString(std::string map_string, Game &game);

    //--------------------------------------------------------------------------
    // Writes the map from a matrix into a string
    //
    // @param original says if the original sign or the actual sign is written
    //                 (needed for the bonus tiles)
    //
    // @return string with the map
    //
    std::string toString(bool original = true) const;

    //--------------------------------------------------------------------------
    // Writes the map from a matrix into a string and draws a * at the position
    // of the player
    //
    // @param player_position actual position of the player
    //
    // @return string with the map(player included)
    //
    std::string toStringWithPlayer(Vector2d player_position) const;

    //--------------------------------------------------------------------------
    // sets the whole map to a size of (0,0)
    //
    void clear();

    //--------------------------------------------------------------------------
    // reset all tiles to the start-status
    //
    void reset();

    //--------------------------------------------------------------------------
    // returns if isLoaded is set
    //
    // @return is_loaded_
    //
    bool isLoaded() const;

    //--------------------------------------------------------------------------
    // returns the position of the EndTile
    //
    // @return is_loaded_
    //
    std::shared_ptr<Tile> getEndTile() const;

    //--------------------------------------------------------------------------
    // returns the position of the EndTile
    //
    // @return is_loaded_
    //
    std::shared_ptr<Tile> getStartTile() const;
};


#endif //MAZE_MAP_H
