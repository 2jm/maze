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
#include "Direction.h"
#include "Matrix.h"
#include "Tile.h"
#include "PathTree.h"
#include "TileCounter.h"

class Game;

//------------------------------------------------------------------------------
// Map class
//
// This class represents the whole map, which consists out of a matrix, filled
// with tiles.
//
class Map : public Matrix<std::shared_ptr<Tile>>
{
  private:
    //--------------------------------------------------------------------------
    // Private copy constructor
    //
    Map(const Map &) = delete;

    //--------------------------------------------------------------------------
    // Private assignment operator
    //
    Map &operator=(const Map &) = delete;

    //--------------------------------------------------------------------------
    // Integer that represents the size of the alphabet
    //
    const static int SIZE_OF_ALPHABET = 26;

    // TODO
    const static int MAX_SOLVE_RECURSION_DEPTH = 5;

    //--------------------------------------------------------------------------
    // Reference to this class to be able to use the [] operator more easily
    // (*this)[] -> matrix[]
    //
    Matrix &matrix_;

    //--------------------------------------------------------------------------
    // Reference to the start/end tile for faster access
    //
    std::shared_ptr<Tile> start_tile_, end_tile_;

    //--------------------------------------------------------------------------
    // Integers telling if the start/end tile is exisiting once
    // -1 => doesn't exist
    //  0 => exists once
    //
    int start_once_, end_once_;

    //--------------------------------------------------------------------------
    // Array needed to check if every teleporter of a loaded map from a file
    // has a corresponding teleporter to be teleported to
    // -1 => doesn't exist
    //  0 => exists once
    //  1 => exists twice, size is 26 -> every char of the alphabet
    //
    int teleporter_pair_[SIZE_OF_ALPHABET];

    //--------------------------------------------------------------------------
    // Checks if the map is valid
    //
    // @return true if the map is valid
    //
    bool isValidMap();

    // TODO
    void solveFromBonusTiles(PathTree &tree, int &path_length,
                             std::shared_ptr<PathTree> &path_tree,
                             int recursion_depth, int available_steps);

    // TODO
    void fillTreeWithAlreadyMovedSteps(PathTree &tree,
                                       const std::vector<Direction>
                                       moved_steps);

    // TODO
    bool findPath(PathTree &tree, int available_steps,
                  std::vector<std::shared_ptr<TileCounter>> *counter_tiles =
                  nullptr);

    // TODO
    void resetReachTimes();

    std::vector<std::shared_ptr<TileCounter>> getCounterTiles();

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
    // @return string with the map (player included)
    //
    std::string toStringWithPlayer(Vector2d player_position) const;

    //--------------------------------------------------------------------------
    // Clear Method
    // Clears the map, e.g. resize it's column and rows to zero.
    //
    void clear();

    //--------------------------------------------------------------------------
    // Reset Method
    // Resets the map itself to it's initial status.
    //
    void reset();

    //--------------------------------------------------------------------------
    // Getter Methods
    //
    std::shared_ptr<Tile> getEndTile() const;

    std::shared_ptr<Tile> getStartTile() const;

    // TODO
    // returns the fastmove string
    std::string solve(const std::vector<Direction> moved_steps,
                      int available_steps);
};


#endif //MAZE_MAP_H
