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

#include <iostream>
#include <chrono>
#include <algorithm>
#include "Map.h"
#include "Stopwatch.h"
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


using std::string;

//------------------------------------------------------------------------------
Map::Map() : dont_reset_counter_tiles_(false),
             matrix_(*this)

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

  //auto start = Stopwatch::getElapsedTime();

  std::vector<std::shared_ptr<TileHole>> hole_tiles;
  std::vector<std::shared_ptr<TileTeleport>> tiles_teleport(SIZE_OF_ALPHABET);

  std::fill(teleporter_pair_, teleporter_pair_ + SIZE_OF_ALPHABET, -1);

  bonus_or_quicksand_on_map = false;

  clear();

  resize(static_cast<unsigned int>(
                 map_string.substr(0, map_string.find('\n')).length()), 1);

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
      else if(map_string[string_position] == ' ')
      {
        put(std::make_shared<TilePath>(tile_position), tile_position);
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

        bonus_or_quicksand_on_map = true;
      }
      else if(map_string[string_position] >= 'f' &&
              map_string[string_position] <= 'j')
      {
        put(std::make_shared<TileQuicksand>(tile_position,
                                            map_string[string_position],
                                            game), tile_position);

        bonus_or_quicksand_on_map = true;
      }
      else if(map_string[string_position] == 's')
      {
        auto hole_tile = std::make_shared<TileHole>(tile_position);
        hole_tiles.push_back(hole_tile);
        put(hole_tile, tile_position);
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


  //auto end = Stopwatch::getElapsedTime();
  //std::cout << "It took me " << (end-start).count() << " microseconds." <<
  //        std::endl;

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
    {
      if(std::dynamic_pointer_cast<TileCounter>(element) == nullptr)
        element->reset();
      else if(!dont_reset_counter_tiles_)
      {
        bool dontResetCounter = false;
        for(auto counter_tile_to_zero : counter_tiles_to_zero_)
        {
          if(element == counter_tile_to_zero)
            dontResetCounter = true;
        }
        if(!dontResetCounter)
          element->reset();
      }
    }
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

std::string Map::solve(const std::vector<Direction> moved_steps,
                       int available_steps)
{
  // reset the map
  reset();

  // create the path tree with the startTile as root node
  auto tree = std::make_shared<PathTree>(getStartTile(), getEndTile().get());
  std::vector<std::shared_ptr<TileCounter>> counter_tiles;
  std::vector<int> counter_tiles_start_values;

  counter_tiles_to_zero_.clear();
  counter_tiles_to_zero_start_values_.clear();

  fillTreeWithAlreadyMovedSteps(*tree, moved_steps, counter_tiles,
                                counter_tiles_start_values);

  findPath(*tree, getEndTile(), 100000, &counter_tiles,
           &counter_tiles_start_values);


  // NO PATH FOUND
  if(tree->getTargetNode() == nullptr)
  {
    // maybe a counter is the reason
    bool no_new_counter_tile = false;
    bool finished = false;
    std::vector<std::shared_ptr<TileCounter>> already_checked_counter_tiles;

    while(!no_new_counter_tile && !finished)
    {
      no_new_counter_tile = true;
      int longest_path_length = tree->getDeepestLeave()->getDepth();
      int i = 0;

      for(auto counter_tile : counter_tiles)
      {
        bool already_checked = false;
        for(auto already_checked_counter_tile : already_checked_counter_tiles)
        {
          if(counter_tile->getPosition() ==
             already_checked_counter_tile->getPosition())
          {
            already_checked = true;
            break;
          }
        }
        if(already_checked)
          continue;

        no_new_counter_tile = false;

        reset();

        counter_tile->set0();

        tree->cut();  // retry from the beginning

        dont_reset_counter_tiles_ = true;
        findPath(*tree, getEndTile(), 100000);
        dont_reset_counter_tiles_ = false;

        if(tree->getTargetNode() != nullptr)
        {
          finished = true;
          counter_tiles_to_zero_.push_back(counter_tile);
          counter_tiles_to_zero_start_values_.push_back
                  (counter_tiles_start_values[i]);
          break;
        }

        if(tree->getDeepestLeave()->getDepth() <= longest_path_length)
          counter_tile->hardReset();

        else
        {
          counter_tiles_to_zero_.push_back(counter_tile);
          counter_tiles_to_zero_start_values_.push_back
                  (counter_tiles_start_values[i]);
        }

        already_checked_counter_tiles.push_back(counter_tile);

        i++;
      }

      if(finished)
        break;

      tree->cut();
      counter_tiles.clear();
      findPath(*tree, getEndTile(), available_steps, &counter_tiles,
               &counter_tiles_start_values);

      if(tree->getTargetNode() != nullptr)
        finished = true;
    }

    if(!finished)
      return "";
  }
  tree->trim();

  tree->sortLeaves();

  int minimal_path_length = tree->getPathLength();
  std::shared_ptr<PathTree> shortest_path = tree;

  // and now try with the bonus paths
  solveFromBonusTiles(*tree, minimal_path_length, shortest_path, 0,
                      available_steps);

  auto finish_path = shortest_path->getTargetNode()->getTreeToNode();

  if(!finish_path->checkStepCount(available_steps))
  {
    return "";
  }

  reset();

  for(auto counter_tile : getCounterTiles())
    counter_tile->hardReset();

  // add moves to zero the counter tiles that must be walls
  std::string fastmove_string = reconstructMoves(*finish_path);

  counter_tiles_to_zero_.clear();
  counter_tiles_to_zero_start_values_.clear();
  reset();

  return fastmove_string;
}



void Map::solveFromBonusTiles(PathTree &tree,
                              int &path_length,
                              std::shared_ptr<PathTree> &path_tree,
                              int recursion_depth, int available_steps)
{
  std::vector<PathTree::Node *> leaves = tree.getLeaves();

  for(auto leave : leaves)
  {
    if(*leave->getTile() != 'x')
    {
      std::shared_ptr<PathTree> leave_tree = leave->getTreeToNode();

      findPath(*leave_tree, getEndTile(), available_steps);

      if(leave_tree->getTargetNode() == nullptr)
      {
        leave_tree = leave->getTreeToNode();

        if(leave_tree->getDeepestLeave()->getDepth() > 1)
        {
          leave_tree->getDeepestLeave()->remove();

          solveFromBonusTiles(*leave_tree, path_length, path_tree,
                              recursion_depth, available_steps);
        }
      }

      if(leave_tree->getTargetNode() != nullptr)
      {
        int this_path_length = leave_tree->getPathLength();
        if(this_path_length < path_length)
        {
          auto finish_path = leave_tree->getTargetNode()->getTreeToNode();

          if(finish_path->checkStepCount(available_steps))
          {
            path_length = this_path_length;
            path_tree = leave_tree;
          }
        }

        if(recursion_depth < MAX_SOLVE_RECURSION_DEPTH)
        {
          leave_tree->trim();
          solveFromBonusTiles(*leave_tree, path_length, path_tree,
                              recursion_depth + 1, available_steps);
        }
      }
    }
  }
}




void Map::fillTreeWithAlreadyMovedSteps(
        PathTree &tree,
        const std::vector<Direction> moved_steps,
        std::vector<std::shared_ptr<TileCounter>> &counter_tiles,
        std::vector<int> &counter_tiles_start_values)
{
  PathTree::Node *node = tree.getRootNode();
  Vector2d origin;

  if(moved_steps.size() > 0)
    node->setUserMoved(true);

  for(auto direction : moved_steps)
  {
    // TODO same code is in the solve internal method
    // the next lines are stolen from Player::move()
    origin = node->getTile()->getPosition();

    while((matrix_[origin + direction]->enter(origin)) ==
          Tile::MOVE_AGAIN && matrix_[origin]->leave(direction))
    {
    }
    // until here is stolen from Player::move()
    int counter_value = 0;

    if(std::dynamic_pointer_cast<TileCounter>(matrix_[origin]))
    {
      auto counter_tile =
              std::dynamic_pointer_cast<TileCounter>(matrix_[origin]);

      counter_value = counter_tile->getValue();

      counter_tiles.push_back(counter_tile);
      counter_tiles_start_values.push_back(counter_tile->getValue());
    }

    node = node->addBranch(matrix_[origin], direction, counter_value, true);
  }
}




// fills the tree
void Map::findPath(PathTree &tree, std::shared_ptr<Tile> target,
                   int available_steps,
        std::vector<std::shared_ptr<TileCounter>> *counter_tiles,
        std::vector<int> *counter_tiles_start_values)
{
  int time = 0; // in the first step the time is equal to the steps

  // some other variables
  bool endReached = false;
  bool movesPossible = true;
  std::vector<Direction> directions;
  directions.push_back(Direction::UP);
  directions.push_back(Direction::RIGHT);
  directions.push_back(Direction::DOWN);
  directions.push_back(Direction::LEFT);

  // the history stores all nodes from each time
  std::vector<std::vector<PathTree::Node*>> history;

  // the end node if it is found
  PathTree::Node *end_node = nullptr;

  // add the root node to the history
  history.push_back(std::vector<PathTree::Node*>(1, tree.getLeaves()[0]));

  reset();
  resetReachTimes();

  tree.getLeaves()[0]->getTile()->setReachTime(time);


  // walk the path that is already in the tree
  PathTree::Node *node = tree.getRootNode(), *next_node;
  while(((next_node = node->getChild(Direction::UP))    != nullptr) ||
        ((next_node = node->getChild(Direction::RIGHT)) != nullptr) ||
        ((next_node = node->getChild(Direction::DOWN))  != nullptr) ||
        ((next_node = node->getChild(Direction::LEFT))  != nullptr))
  {
    Vector2d origin = node->getTile()->getPosition();

    node = next_node;

    Vector2d direction = node->getParentDirection();

    while((matrix_[origin + direction]->enter(origin)) ==
          Tile::MOVE_AGAIN && matrix_[origin]->leave(direction))
    {
    }
  }

  // run until no moves are possible anymore
  while(!(!movesPossible || (endReached && !bonus_or_quicksand_on_map)))
  {
    movesPossible = false;

    // add a new vector of nodes to the history, it will be filled in this step
    history.push_back(std::vector<PathTree::Node*>());

    // a vector containg all nodes that should be add, it will also contain
    // multiple nodes pointing to the same tile. From this nodes only one
    // will be taken and pushed to the history.
    std::vector<PathTree::Node*> nodes_to_add;

    // loop through all nodes that were added in the last step
    for(auto node : history[history.size() - 2])
    {
      int reach_time = node->getTile()->getReachTime() + 1;

      if(node->getDepth() - node->getBonusSteps() >= available_steps)
        continue;

      // move in all 4 directions from this node
      for(auto direction : directions)
      {
        // the next lines are stolen from Player::move()
        bool valid_move = false;
        Tile::EnterResult enter_result;

        Vector2d origin = node->getTile()->getPosition();

        if(!matrix_[origin]->leave(direction))
          continue;

        // if the tile that will be entered is a counter tile set its counter
        // value
        auto counter_tile = std::dynamic_pointer_cast<TileCounter>(
                                                 matrix_[origin + direction]);
        if(counter_tile)
        {
          auto counter_node = node->getNodeInPath(*counter_tile);
          if(counter_node)
            counter_tile->setValue(counter_node->getCounterValue());
          else
            counter_tile->reset();
        }

        while((enter_result = matrix_[origin + direction]->enter(origin)) ==
              Tile::MOVE_AGAIN && matrix_[origin]->leave(direction))
        {
          if(enter_result != Tile::INVALID_MOVE)
            valid_move = true;

          // if the tile that will be entered is a counter tile set its counter
          // value
          counter_tile = std::dynamic_pointer_cast<TileCounter>(
                  matrix_[origin + direction]);
          if(counter_tile)
          {
            auto counter_node = node->getNodeInPath(*counter_tile);
            if(counter_node)
              counter_tile->setValue(counter_node->getCounterValue());
            else
              counter_tile->reset();
          }
        }
        if(enter_result != Tile::INVALID_MOVE)
          valid_move = true;
        // until here is stolen from Player::move()

        // the player moved
        if(valid_move)
        {
          // check if he reached the end (this will not stop the solving)
          if(matrix_[origin] == target)
            endReached = true;

          counter_tile = std::dynamic_pointer_cast<TileCounter>
                  (matrix_[origin]);
          if(counter_tile)
            node->setCounterValue(counter_tile->getValue());

          // if this tile was not reached in a previous step, enter it
          if(matrix_[origin]->getReachTime() >= reach_time)
          {
            int new_reach_time = reach_time;

            if(matrix_[origin]->getStepChange() < 0)
              new_reach_time -= matrix_[origin]->getStepChange();

            matrix_[origin]->setReachTime(new_reach_time);
            movesPossible = true;

            // create a new node on the tree
            PathTree::Node* new_node =
                    node->addBranch(matrix_[origin], direction);

            nodes_to_add.push_back(new_node);

            // thinking about this and what the variable endReached is for...
            // but here is the end_node set TODO
            if(target->getPosition()
               == matrix_[origin]->getPosition())
              end_node = new_node;
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
    unsigned int i, j;  //TODO
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
            if(nodes_to_add[i] == end_node)
              end_node = nodes_to_add[j];

            // remove it from the tree
            nodes_to_add[i]->remove();
            // remove it from the nodes_to_add vector
            nodes_to_add.erase(nodes_to_add.begin() + i);
            i--;
            go_to_next = true;
          }
          else
          {
            if(nodes_to_add[j] == end_node)
              end_node = nodes_to_add[i];

            nodes_to_add[j]->remove();
            nodes_to_add.erase(nodes_to_add.begin() + j);
            j--;
          }
        }
      }
    }

    // add the remaining nodes to the history
    for(auto &new_node : nodes_to_add)
    {
      history.back().push_back(new_node);

      if(counter_tiles)   // not nullptr
      {
        auto counter_tile =
                std::dynamic_pointer_cast<TileCounter>(new_node->getTile());
        if(counter_tile)
        {
          counter_tiles->push_back(counter_tile);
          counter_tiles_start_values->push_back(counter_tile->getValue() + 1);
        }
      }
    }

    nodes_to_add.clear();

    time++;

    if(time == 100000)
      break;
  }
}


std::string Map::reconstructMoves(PathTree &tree)
{
  std::string fast_move_string;

  std::vector<Direction> directions;
  directions.push_back(Direction::UP);
  directions.push_back(Direction::RIGHT);
  directions.push_back(Direction::DOWN);
  directions.push_back(Direction::LEFT);

  PathTree::Node *node = tree.getRootNode(), *next_node;
  while(((next_node = node->getChild(Direction::UP)) != nullptr) ||
        ((next_node = node->getChild(Direction::RIGHT)) != nullptr) ||
        ((next_node = node->getChild(Direction::DOWN)) != nullptr) ||
        ((next_node = node->getChild(Direction::LEFT)) != nullptr))
  {
    node = next_node;

    auto counter_tile = std::dynamic_pointer_cast<TileCounter>(node->getTile());
    if(counter_tile)
    {
      auto counter_node = node->getNodeInPath(*counter_tile);
      if(counter_node)
        node->setCounterValue(counter_node->getCounterValue()-1);
      else
        node->setCounterValue(counter_tile->getValue() - 1);
    }

    if(node->isUserMoved())
      continue;

    fast_move_string += static_cast<char>(node->getParentDirection());

    int i = 0;
    for(auto counter_tile_to_zero : counter_tiles_to_zero_)
    {
      Vector2d origin = node->getTile()->getPosition() +
                     Vector2d(node->getParentDirection());

      if(origin == counter_tile_to_zero->getPosition())
      {
        auto origin_tree = node->getTreeToNode();
        auto new_node = origin_tree->getDeepestLeave()->remove();

        new_node = new_node->addBranch(counter_tile_to_zero,
                                   node->getParentDirection());


        auto counter_node = new_node->getNodeInPath(*counter_tile_to_zero);
        if(counter_node)
          new_node->setCounterValue(counter_node->getCounterValue() - 1);
        else
        {
          counter_tile_to_zero->reset();
          new_node->setCounterValue(counter_tile_to_zero->getValue() - 1);
        }

        // bring this counter to zero
        int counter_value = counter_tiles_to_zero_start_values_[i];

        int run_times = new_node->getCounterValue();

        std::vector<std::shared_ptr<PathTree>> trees;

        // move in all 4 directions from this node
        //for(auto direction : directions)
        Direction direction = (Vector2d(node->getParentDirection()) * -1);
        {
          // the next lines are stolen from Player::move()
          bool valid_move = false;
          Tile::EnterResult enter_result;

          // if the tile that will be entered is a counter tile set its counter
          // value
          auto counter_tile = std::dynamic_pointer_cast<TileCounter>(
                  matrix_[origin + direction]);
          if(counter_tile)
          {
            auto counter_node = node->getNodeInPath(*counter_tile);
            if(counter_node)
              counter_tile->setValue(counter_node->getCounterValue());
            else
              counter_tile->reset();
          }

          while((enter_result = matrix_[origin + direction]->enter(origin)) ==
                Tile::MOVE_AGAIN && matrix_[origin]->leave(direction))
          {
            if(enter_result != Tile::INVALID_MOVE)
              valid_move = true;

            // if the tile that will be entered is a counter tile set its counter
            // value
            counter_tile = std::dynamic_pointer_cast<TileCounter>(
                    matrix_[origin + direction]);
            if(counter_tile)
            {
              auto counter_node = node->getNodeInPath(*counter_tile);
              if(counter_node)
                counter_tile->setValue(counter_node->getCounterValue());
              else
                counter_tile->reset();
            }
          }
          if(enter_result != Tile::INVALID_MOVE)
            valid_move = true;
          // until here is stolen from Player::move()

          // the player moved
          if(valid_move)
          {
            auto new_origin_tree = new_node->getTreeToNode();
            auto new_new_node = new_origin_tree->getDeepestLeave()
                    ->addBranch(matrix_[origin], direction);

            counter_tile = std::dynamic_pointer_cast<TileCounter>(
                            new_new_node->getTile());
            if(counter_tile)
            {
              counter_node = new_new_node->getNodeInPath(*counter_tile);
              if(counter_node)
                new_new_node->setCounterValue(
                        counter_node->getCounterValue() - 1);
              else
                new_new_node->setCounterValue(
                        counter_tile->getValue() - 1);
            }

            // the player moved away from the counter tile know search a
            // way back
            trees.push_back(new_origin_tree);

            if(new_node->getCounterValue() > 0) //test
            {
              trees.back()->setTarget(counter_tile_to_zero.get());
              findPath(*trees.back(), counter_tile_to_zero,
                       std::numeric_limits<int>::max());
            }
              else
            {
              // on the last run don't find the counter_tile_to_zero but the
              // one next to it
              trees.back()->setTarget(node->getTile().get());
              findPath(*trees.back(), node->getTile(),
                       std::numeric_limits<int>::max());
            }
          }
        }

        int shortest_tree_index = 0, index;
        for(index = 1; index < trees.size(); index++)
        {
          if(trees[index]->getPathLength() <
                trees[shortest_tree_index]->getPathLength())
            shortest_tree_index = index;
        }

        std::string reversed_fastmove_string;

        auto node = trees[shortest_tree_index]->getTargetNode();
        if(node)
        {
          do
          {
            reversed_fastmove_string +=
                    static_cast<char>(node->getParentDirection());
            node = node->getParent();
          }
          while(node && !(node->getTile()->getPosition() ==
                          counter_tile_to_zero->getPosition()));
        }

        std::reverse(reversed_fastmove_string.begin(),
                     reversed_fastmove_string.end());

        for(; run_times >= 0; run_times--)
          fast_move_string += reversed_fastmove_string;


        break;
      }
      i++;
    }
  }

  return fast_move_string;
}


void Map::resetReachTimes()
{
  for(auto column : columns_)
  {
    for(auto element : column)
    {
      element->setReachTime(std::numeric_limits<int>::max());  // TODO MAX REACH TIME CONSTANT
    }
  }
}

std::vector<std::shared_ptr<TileCounter>> Map::getCounterTiles()
{
  std::vector<std::shared_ptr<TileCounter>> counter_tiles;

  for(auto column : columns_)
  {
    for(auto element : column)
    {
      if(dynamic_cast<TileCounter*>(element.get()) != nullptr)
        counter_tiles.push_back(
                std::dynamic_pointer_cast<TileCounter>(element));
    }
  }

  return counter_tiles;
}












