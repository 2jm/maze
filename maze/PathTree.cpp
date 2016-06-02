//
// Created by jonas on 5/26/16.
//

#include <algorithm>
#include <iostream>
#include <iomanip>
#include <limits>
#include "PathTree.h"
#include "Direction.h"


PathTree::PathTree(std::shared_ptr<Tile> tile) :
        root_node_(std::make_shared<Node>(tile, *this))
{
  leaves_.push_back(root_node_.get());
}

PathTree::Node* PathTree::getRootNode()
{
  return root_node_.get();
}

void PathTree::print()
{
  int print_depth = 0;
  bool new_line = false;

  root_node_->recursivePrint(print_depth, new_line);
}

void PathTree::cut()
{
  int i; //TODO
  for(i=0; i<4; i++)
  {
    if(root_node_->getChild(i) != nullptr)
      root_node_->getChild(i)->remove();
  }

}


void PathTree::trim()
{
  int i;  // TODO
  for(i = 0; i < leaves_.size(); i++)
  {
    Node *node = leaves_[i];
    if(*(node->getTile()) != 'x' && node->getTile()->getStepChange() <= 0)
    {
      node->remove();
      i--;
    }
  }
}

void PathTree::addLeave(Node *node)
{
  if(node->getParent() != nullptr && node->getParent()->isLeave())
  {
    int i; // TODO
    for(i = 0; i < leaves_.size(); i++)
    {
      if(node->getParent() == leaves_[i])
      {
        leaves_.erase(leaves_.begin() + i);
        break;
      }
    }
  }

  leaves_.push_back(node);
}

void PathTree::removeLeave(Node *node)
{
  int i; // TODO
  for(i = 0; i < leaves_.size(); i++)
  {
    if(node == leaves_[i])
    {
      leaves_.erase(leaves_.begin() + i);
      break;
    }
  }
}

void PathTree::sortLeaves()
{
  std::sort(leaves_.begin(), leaves_.end());
}

void PathTree::printLeaves()
{
  int i;  // TODO
  for(i = 0; i < leaves_.size(); i++)
    std::cout << "leave: " << leaves_[i]->getTile()->getPosition().getX() <<
    " " << leaves_[i]->getTile()->getPosition().getY() << std::endl;
}

std::vector<PathTree::Node *> &PathTree::getLeaves()
{
  return leaves_;
}

PathTree::Node *PathTree::getFinishLeave()
{
  for(auto leave : getLeaves())
  {
    if(*leave->getTile() == 'x')
      return leave;
  }
  return nullptr;
}

int PathTree::getPathLength()
{
  PathTree::Node* leave = getFinishLeave();

  int path_length = std::numeric_limits<int>::max();

  if(leave != nullptr)
  {
    if(leave->getDepth() - leave->getBonusSteps() < path_length)
      path_length = leave->getDepth() - leave->getBonusSteps();
  }

  return path_length;
}

std::string PathTree::reconstructMoves()
{
  std::string fast_move_string;

  Node *end_node = getFinishLeave();

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
  }

  return fast_move_string;
}

bool PathTree::checkStepCount(int available_steps)
{
  Node *node = getRootNode(), *next_node;
  while(((next_node = node->getChild(Direction::UP))    != nullptr) ||
        ((next_node = node->getChild(Direction::RIGHT)) != nullptr) ||
        ((next_node = node->getChild(Direction::DOWN))  != nullptr) ||
        ((next_node = node->getChild(Direction::LEFT))  != nullptr))
  {
    if(available_steps <= 0)
      return false;

    node = next_node;
    available_steps--;
    available_steps += node->getBonusSteps() -
                          node->getParent()->getBonusSteps();
  }

  return true;
}

PathTree::Node* PathTree::getDeepestLeave()
{
  auto leaves = getLeaves();
  Node *deepestLeave = root_node_.get();

  for(auto leave : leaves)
  {
    if(leave->getDepth() > deepestLeave->getDepth())
      deepestLeave = leave;
  }
}









//------------------------------------------------------------------------------
//              NODE
//------------------------------------------------------------------------------

PathTree::Node::Node(std::shared_ptr<Tile> tile, PathTree::Node *parent,
                     Direction direction, int bonusPath, PathTree &tree, int
                     depth, bool user_moved) :
        tile_(tile),
        parent_(parent),
        parent_direction_(direction),
        bonus_path_(bonusPath),
        tree_(tree),
        depth_(depth),
        user_moved_(user_moved)
{
}

PathTree::Node::Node(std::shared_ptr<Tile> tile, PathTree &tree,
                     bool user_moved) :
        tile_(tile),
        parent_(nullptr),
        parent_direction_(Direction::OTHER),
        bonus_path_(0),
        tree_(tree),
        depth_(0),
        user_moved_(user_moved)
{

}

PathTree::Node* PathTree::Node::addBranch(
        std::shared_ptr<Tile> tile, Direction direction, bool user_moved)
{
  int bonus_path = bonus_path_;

  // if it is a bonus tile check if it was already used
  if(tile->getStepChange() > 0)
  {
    if(!isTileInPath(*tile))
      bonus_path += tile->getStepChange();
  }
  else
    bonus_path += tile->getStepChange();

  int array_index = directionToArrayIndex(direction);

  std::shared_ptr<Node> new_node =
          std::make_shared<Node>(tile, this, direction, bonus_path, tree_,
                                 depth_ + 1, user_moved);

  tree_.addLeave(new_node.get());
  childs_[array_index] = new_node;

  return childs_[array_index].get();
}

int PathTree::Node::directionToArrayIndex(Direction direction)
{
  if(direction == Direction::UP)
    return 0;
  else if(direction == Direction::RIGHT)
    return 1;
  else if(direction == Direction::DOWN)
    return 2;
  else if(direction == Direction::LEFT)
    return 3;
  else
    return 4;  // TODO
}


std::shared_ptr<Tile> PathTree::Node::getTile()
{
  return tile_;
}

PathTree::Node* PathTree::Node::getChild(Direction direction)
{
  return childs_[directionToArrayIndex(direction)].get();
}

PathTree::Node *PathTree::Node::getChild(int index)
{
  if(index > 3)
    return nullptr;
  return childs_[index].get();
}


PathTree::Node *PathTree::Node::getParent()
{
  return parent_;
}

Direction PathTree::Node::getParentDirection()
{
  return parent_direction_;
}

int PathTree::Node::getBonusSteps()
{
  return bonus_path_;
}

PathTree::Node *PathTree::Node::remove()
{
  if(parent_ == nullptr)
    return nullptr;

  int i; //TODO
  for(i = 0; i < 4; i++)  // TODO 4 -> richtungsanzahl oder so
  {
    if(childs_[i] != nullptr)
      childs_[i]->remove();
  }
  tree_.removeLeave(this);

  Node *parent_save = parent_; // This is needed because after the reset the
  // parent_ variable will not be available anymore

  // Do nothing after this
  parent_->childs_[directionToArrayIndex(parent_direction_)].reset();

  if(parent_save->isLeave())
    parent_save->tree_.addLeave(parent_save);

  return parent_save;
}

void PathTree::Node::recursivePrint(int &print_depth, bool &new_line)
{
  bool is_leave = true;
  int i; //TODO

  if(new_line)
  {
    new_line = false;

    for(i = 0; i < print_depth * 15; i++)
    {
      std::cout << " ";
    }
    std::cout << "+";
  }
  else
  {
    std::cout << " -";
  }

  char bracketL = '(', bracketR = ')';
  if(bonus_path_)
  {
    bracketL = '[';
    bracketR = ']';
  }

  std::cout << static_cast<char>(parent_direction_) << " " << bracketL
  << std::setw(2) << tile_->getPosition().getX() << "/"
  << std::setw(2) << tile_->getPosition().getY() << bracketR
  << std::setw(2) << bonus_path_ << " " <<
  tile_->toChar(true);

  print_depth++;

  for(i = 0; i < 4; i++)
  {
    if(childs_[i] != nullptr)
    {
      is_leave = false;
      childs_[i]->recursivePrint(print_depth, new_line);
    }
  }

  print_depth--;

  if(is_leave)
  {
    std::cout << std::endl;
    new_line = true;
  }
}

bool PathTree::Node::isLeave()
{
  int i; //TODO
  for(i = 0; i < 4; i++)  // TODO 4 -> richtungsanzahl oder so
  {
    if(childs_[i] != nullptr)
      return false;
  }

  return true;
}

int PathTree::Node::getDepth()
{
  return depth_;
}

bool PathTree::Node::operator<(Node *node2)
{
  return (depth_ < node2->getDepth());
}

std::shared_ptr<PathTree> PathTree::Node::getTreeToNode()
{
  std::shared_ptr<PathTree> new_tree =
          std::make_shared<PathTree>(tree_.getRootNode()->getTile());

  std::vector<Direction> path;

  Node* node = this;
  while(node->parent_ != nullptr)
  {
    path.push_back(node->parent_direction_);
    node = node->parent_;
  }

  Node *new_node = new_tree->getRootNode();
  new_node->setUserMoved(node->isUserMoved());

  for(auto direction = path.rbegin(); direction != path.rend(); ++direction)
  {
    node = node->getChild(*direction);
    new_node = new_node->addBranch(node->getTile(), *direction,
                                   node->isUserMoved());
  }

  return new_tree;
}

bool PathTree::Node::isUserMoved()
{
  return user_moved_;
}

void PathTree::Node::setUserMoved(bool user_moved)
{
  user_moved_ = user_moved;
}

bool PathTree::Node::isTileInPath(const Tile &tile)
{
  Node *node = this;
  while((node = node->getParent()) != nullptr)
  {
    if(node->getTile()->getPosition() == tile.getPosition())
      return true;
  }
  return false;
}





































