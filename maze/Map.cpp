//------------------------------------------------------------------------------
// Map.cpp
//
// Group: Group 13624, study assistant Angela Promitzer
//
// Authors: Jonas Juffinger (1531253)
//          Matthias Klotz (1530653)
//          Johannes Kopf (1431505)
//------------------------------------------------------------------------------
//

#include "Map.h"
#include "TileWall.h"
#include "TileStart.h"
#include "TilePath.h"
#include "TileFinish.h"
#include "TileTeleport.h"
#include "TileBonus.h"
#include "TileIce.h"
#include "TileOneWay.h"
#include "TileQuicksand.h"
#include "TileHole.h"
#include "TileCounter.h"
#include "PathTree.h"


using std::string;

//------------------------------------------------------------------------------
Map::Map() : matrix_(*this)
{

}

//------------------------------------------------------------------------------
bool Map::loadFromString(string map_string, Game &game)
{
  int x = 0;
  int y = 0;
  int string_position = 0;
  int pair_nr;

  start_once_ = -1;
  end_once_ = -1;

  std::vector<std::shared_ptr<TileHole>> hole_tiles;
  std::vector<std::shared_ptr<TileTeleport>> tiles_teleport(SIZE_OF_ALPHABET);

  std::fill(teleporter_pair_, teleporter_pair_ + SIZE_OF_ALPHABET, -1);

  clear();

  while(map_string[string_position])
  {
    x = 0;
    while(map_string[string_position] != '\n')
    {
      Vector2d tile_position(x, y);

      if(map_string[string_position] == '#')
      {
        put(std::make_shared<TileWall>(tile_position), tile_position);
      }
      else if(map_string[string_position] >= 'A' &&
              map_string[string_position] <= 'Z')
      {
        std::shared_ptr<TileTeleport> tile_teleport =
                std::make_shared<TileTeleport>(
                        tile_position, map_string[string_position]);
        pair_nr = map_string[string_position] - 'A';  //character - ascii(A)
        teleporter_pair_[pair_nr]++;

        if(tiles_teleport[pair_nr] == nullptr)
          tiles_teleport[pair_nr] = tile_teleport;
        else
        {
          tiles_teleport[pair_nr]->
                  setCorrespondingTeleport(tile_teleport.get());
          tile_teleport->
                  setCorrespondingTeleport(tiles_teleport[pair_nr].get());
        }

        put(tile_teleport, tile_position);
      }
      else if(map_string[string_position] == 'o')
      {
        start_once_++;

        start_tile_ = std::make_shared<TileStart>(tile_position);

        put(start_tile_, tile_position);
      }
      else if(map_string[string_position] == 'x')
      {
        end_once_++;

        end_tile_ = std::make_shared<TileFinish>(tile_position, game);

        put(end_tile_, tile_position);
      }
      else if(map_string[string_position] >= 'a' &&
              map_string[string_position] <= 'e')
      {
        put(std::make_shared<TileBonus>(tile_position,
                                        map_string[string_position],
                                        game), tile_position);
      }
      else if(map_string[string_position] >= 'f' &&
              map_string[string_position] <= 'j')
      {
        put(std::make_shared<TileQuicksand>(tile_position,
                                            map_string[string_position],
                                            game), tile_position);
      }
      else if(map_string[string_position] == 's')
      {
        auto hole_tile = std::make_shared<TileHole>(tile_position);
        hole_tiles.push_back(hole_tile);
        put(hole_tile, tile_position);
      }
      else if(map_string[string_position] == ' ')
      {
        put(std::make_shared<TilePath>(tile_position), tile_position);
      }
      else if(map_string[string_position] == '+')
      {
        put(std::make_shared<TileIce>(tile_position), tile_position);
      }
      else if(map_string[string_position] == '<' ||
              map_string[string_position] == '>' ||
              map_string[string_position] == 'v' ||
              map_string[string_position] == '^')
      {
        put(std::make_shared<TileOneWay>(tile_position,
                                         map_string[string_position]),
            tile_position);
      }
      else if(map_string[string_position] >= '0' &&
              map_string[string_position] <= '9')
      {
        put(std::make_shared<TileCounter>(tile_position,
                                          map_string[string_position]),
            tile_position);
      }
      else
      {
        return false;
      }

      x++;
      string_position++;
    }
    y++;
    string_position++;
  }

  for(auto hole_tile : hole_tiles)
    hole_tile->setStartTile(start_tile_.get());

  return isValidMap();
}

//------------------------------------------------------------------------------
bool Map::isValidMap()
{
  int line_length, column_height;

  line_length = size_.getX();
  column_height = size_.getY();

  for(int row_number = 0; row_number < column_height; row_number++)
  {
    if(matrix_[0][row_number] == nullptr ||
       matrix_[line_length - 1][row_number] == nullptr ||
       *(matrix_[0][row_number]) != '#' ||
       *(matrix_[line_length - 1][row_number]) != '#')
      return false;
  }

  for(int column_number = 0; column_number < line_length; column_number++)
  {
    if(matrix_[column_number][0] == nullptr ||
       matrix_[column_number][column_height - 1] == nullptr ||
       *(matrix_[column_number][0]) != '#' ||
       *(matrix_[column_number][column_height - 1]) != '#')
      return false;
  }

  //check if exact one start-tile
  if(start_once_ != 0)
    return false;
  //check if exact one end-tile
  if(end_once_ != 0)
    return false;
  //check if if teleporter_pairs are correct
  for(int pair = 0; pair < 26; pair++)
  {
    if(teleporter_pair_[pair] != -1 && teleporter_pair_[pair] != 1)
      return false;
  }

  return true;
}

//------------------------------------------------------------------------------
std::string Map::toString(bool original) const
{
  std::string matrix_string;

  for(int row_number = 0; row_number < size_.getY(); row_number++)
  {
    for(int column_number = 0; column_number < size_.getX(); column_number++)
      matrix_string += columns_[column_number][row_number]->toChar(original);

    matrix_string += '\n';
  }

  return matrix_string;
}

//------------------------------------------------------------------------------
std::string Map::toStringWithPlayer(Vector2d player_position) const
{
  std::string map_string;

  for(int row_number = 0; row_number < size_.getY(); row_number++)
  {
    for(int column_number = 0; column_number < size_.getX();
        column_number++)
    {
      if(player_position == Vector2d(column_number, row_number))
        map_string += '*';
      else
        map_string += columns_[column_number][row_number]->toChar(false);
    }
    map_string += '\n';
  }

  return map_string;
}

//------------------------------------------------------------------------------
void Map::clear()
{
  resize(0, 0);
}

//------------------------------------------------------------------------------
void Map::reset()
{
  // reset all tiles
  for(auto &column : columns_)
  {
    for(auto &element : column)
      element->reset();
  }
}

//------------------------------------------------------------------------------
std::shared_ptr<Tile> Map::getEndTile() const
{
  return end_tile_;
}

//------------------------------------------------------------------------------
std::shared_ptr<Tile> Map::getStartTile() const
{
  return start_tile_;
}

std::string Map::solve(Vector2d start_position)
{
  int time = 0;   // in the first step the time is equal to the steps

  // the history stores all nodes from each time
  std::vector<std::vector<std::shared_ptr<PathTree::Node>>> history;

  // some other variables
  bool endReached = false;
  bool movesPossible = true;
  std::vector<Direction> directions;
  directions.push_back(Direction::UP);
  directions.push_back(Direction::RIGHT);
  directions.push_back(Direction::DOWN);
  directions.push_back(Direction::LEFT);

  // get the start tile and set its reachTime to 0
  std::shared_ptr<Tile> startTile = matrix_[start_position];
  startTile->setReachTime(time);

  // the end node if it is found
  PathTree::Node *end_node = nullptr;

  // create the path tree with the startTile as root node
  PathTree tree(startTile);

  // add the root node to the history
  history.push_back(
          std::vector<std::shared_ptr<PathTree::Node>>(1, tree.getRootNode()));


  // start the solving
  time++;

  // run until no moves are possible anymore
  while(movesPossible)
  {
    movesPossible = false;

    // add a new vector of nodes to the history, it will be filled in this step
    history.push_back(std::vector<std::shared_ptr<PathTree::Node>>());

    // a vector containg all nodes that should be add, it will also contain
    // multiple nodes pointing to the same tile. From this nodes only one
    // will be taken and pushed to the history.
    std::vector<std::shared_ptr<PathTree::Node>> nodes_to_add;

    // loop through all nodes that were added in the last step
    for(auto node : history[history.size() - 2])
    {
      // move in all 4 directions from this node
      for(auto direction : directions)
      {
        // the next lines are stolen from Player::move()
        bool valid_move = false;
        Tile::EnterResult enter_result;

        Vector2d origin = node->getTile()->getPosition();

        while((enter_result = matrix_[origin + direction]->enter(origin)) ==
              Tile::MOVE_AGAIN && matrix_[origin]->leave(direction))
        {
          if(enter_result != Tile::INVALID_MOVE)
            valid_move = true;
        }
        if(enter_result != Tile::INVALID_MOVE)
          valid_move = true;
        // until here is stolen from Player::move()

        // the player moved
        if(valid_move)
        {
          // check if he reached the end (this will not stop the solving)
          if(matrix_[origin] == getEndTile())
            endReached = true;

          // if this tile was not reached in a previous step, enter it
          if(matrix_[origin]->getReachTime() >= time)
          {
            matrix_[origin]->setReachTime(time);
            movesPossible = true;

            // create a new node on the tree
            std::shared_ptr<PathTree::Node> new_node =
                    node->addBranch(matrix_[origin], direction);

            nodes_to_add.push_back(new_node);

            // thinking about this and what the variable endReached is for...
            // but here is the end_node set
            if(getEndTile()->getPosition()
               == matrix_[origin]->getPosition())
              end_node = new_node.get();
          }

          // if the end is not reached moves are possible!
          if(!endReached)
            movesPossible = true;
        }
      }
    }


    // compare all nodes_to_add and check if some point to the same tile, if
    // they do take the one with more bonus steps of both have 0 bonus steps,
    // take the first one.
    // this can be done faster
    int i, j;  //TODO
    bool go_to_next;

    for(i = 0; i < nodes_to_add.size(); i++)
    {
      go_to_next = false;

      for(j = i + 1; j < nodes_to_add.size() && !go_to_next; j++)
      {
        if(nodes_to_add[i]->getTile()->getPosition() ==
           nodes_to_add[j]->getTile()->getPosition())
        {
          // if the bonus steps of j are higher remove i
          if(nodes_to_add[j]->getBonusSteps() >
             nodes_to_add[i]->getBonusSteps())
          {
            if(nodes_to_add[i].get() == end_node)
              end_node = nodes_to_add[j].get();

            // remove it from the tree
            nodes_to_add[i]->remove();
            // remove it from the nodes_to_add vector
            nodes_to_add.erase(nodes_to_add.begin() + i);
            i--;
            go_to_next = true;
          }
          else
          {
            if(nodes_to_add[j].get() == end_node)
              end_node = nodes_to_add[i].get();

            nodes_to_add[j]->remove();
            nodes_to_add.erase(nodes_to_add.begin() + j);
            j--;
          }
        }
      }
    }

    // add the remaining nodes to the history
    for(auto &new_node : nodes_to_add)
      history.back().push_back(new_node);

    nodes_to_add.clear();

    // print what we have got so far
    std::cout << "Time:  " << time << std::endl;
    std::cout << "Count: " << history.back().size() << std::endl;
    for(int row_number = 0; row_number < getSize().getY(); row_number++)
    {
      for(int column_number = 0; column_number < getSize().getX();
          column_number++)
        std::cout <<
        ((matrix_[column_number][row_number]->getReachTime() < 10) ? " " : "")
        << matrix_[column_number][row_number]->getReachTime() << " ";

      std::cout << std::endl;
    }


    time++;

    if(time == 100000)
      break;
  }


  // print the tree
  tree.print();

  std::cout << std::endl << " TRIM " << std::endl << std::endl;
  tree.trim();

  tree.print();

  tree.sortLeaves();
  tree.printLeaves();


  std::cout << std::endl << std::endl << " RECONSTRUCT FROM TREE " <<
  std::endl <<
  std::endl;

  reset();


  std::string fast_move_string;

  // Reconstruct moves
  if(end_node != nullptr)
  {
    std::vector<Direction> moves;

    // start from the end node and go to the root node, the directions are
    // pushed in the moves vector
    while(end_node->getParent() != nullptr)
    {
      moves.push_back(end_node->getParentDirection());
      end_node = end_node->getParent();
    }

    int move_counter;

    // print the moves from back to front, because this is the right direction
    for(move_counter = static_cast<int>(moves.size() - 1); move_counter >= 0;
        move_counter--)
      fast_move_string += static_cast<char>(moves[move_counter]);

    std::cout << std::endl;
  }

  return fast_move_string;
}

void Map::solveInternal()
{

}




