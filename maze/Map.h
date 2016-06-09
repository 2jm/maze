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

    //--------------------------------------------------------------------------
    // Depth of the find with bonus tiles recursion
    //
    const static int MAX_SOLVE_RECURSION_DEPTH = 2;

    //--------------------------------------------------------------------------
    // If true, the counter tiles are not reset on a reset
    //
    bool dont_reset_counter_tiles_;

    //--------------------------------------------------------------------------
    // Vector containing all counter tiles that must be zero in order that the
    // maze is solveable
    //
    std::vector<std::shared_ptr<TileCounter>> counter_tiles_to_zero_;

    //--------------------------------------------------------------------------
    // Vector containing the start values of the above counters
    //
    std::vector<int> counter_tiles_to_zero_start_values_;

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
    // True if there is at least one bonus or quicksand field on the map
    //
    bool bonus_or_quicksand_on_map;

    //--------------------------------------------------------------------------
    // Checks if the map is valid
    //
    // @return true if the map is valid
    //
    bool isValidMap();

    //--------------------------------------------------------------------------
    // Solve From Bonus Tiles Method
    // Tries to solve the maze from an path with bonus tiles recursively to
    // find the best path
    //
    // @param tree The path tree that has been already walked
    // @param path_length The length of the shortest possible path
    // @param path_tree The path tree that will perhaps contain the shortest
    //                  path if one is found
    // @param recursion_depth The depth of the recursion
    // @param available_steps The steps that are available
    //
    void solveFromBonusTiles(PathTree &tree, int &path_length,
                             std::shared_ptr<PathTree> &path_tree,
                             int recursion_depth, int available_steps);

    //--------------------------------------------------------------------------
    // Fill Tree With Already Moved Steps Method
    // Fill the provided tree with the user moved steps
    //
    // @param tree The tree to fill
    // @param moved_steps The user moved_steps
    // @param counter_tiles This vector is filled with the counter tiles on
    //        the path
    // @param counter_tiles_start_values The values of the counter tiles
    //
    void fillTreeWithAlreadyMovedSteps(
            PathTree &tree,
            const std::vector<Direction> moved_steps,
            std::vector<std::shared_ptr<TileCounter>> &counter_tiles,
            std::vector<int> &counter_tiles_start_values);

    //--------------------------------------------------------------------------
    // Find Path Method
    // Tries to find the path from the leave from tree to the target tile
    //
    // @param tree The tree to use
    // @param target The tile that should be find the path to
    // @param available_steps The steps that are available
    // @param counter_tiles This vector is filled with the counter tiles on
    //        the path
    // @param counter_tiles_start_values The values of the counter tiles
    //
    void findPath(PathTree &tree, std::shared_ptr<Tile> target,
                  int available_steps,
                  std::vector<std::shared_ptr<TileCounter>> *counter_tiles =
                  nullptr,
                  std::vector<int> *counter_tiles_start_values = nullptr);

    //--------------------------------------------------------------------------
    // Reconstruct Moves Method
    // Reconstructs the fastmove string from the tree and adds extra moves to
    // bring counter tiles that must be walls to zero
    //
    // @param tree The path tree to reconstruct
    //
    std::string reconstructMoves(PathTree &tree);

    //--------------------------------------------------------------------------
    // Reset Reach Times Method
    // Resets the reach times of all tiles
    //
    void resetReachTimes();

    //--------------------------------------------------------------------------
    // Get Counter Tiles Method
    // Return all counter tiles that are in the map
    //
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

    //--------------------------------------------------------------------------
    // Solve Method
    // Tries to solve the maze from the current position of the player
    //
    // @return The found fastmove string to solve the maze or an empty string
    //         if no path was found
    //
    std::string solve(const std::vector<Direction> moved_steps,
                      int available_steps);
};


#endif //MAZE_MAP_H
