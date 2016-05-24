//
// Created by jonas on 5/22/16.
//

#ifndef MAZE_ALL_TREE_H
#define MAZE_ALL_TREE_H

#include <vector>
#include <bits/shared_ptr.h>
#include <iostream>
#include <iomanip>
#include "Tile.h"
#include "Direction.h"

class PathTree
{
  public:
    class Node
    {
      private:
        std::shared_ptr<Tile> tile_;
        std::shared_ptr<Node> childs_[4];
        Node *parent_;
        Direction parent_direction_;
        int bonusPath_;

        int directionToArrayIndex(Direction direction);

      public:
        Node(std::shared_ptr<Tile> tile, Node *parent, Direction direction,
             int bonusPath);
        Node(std::shared_ptr<Tile> tile);

        // TODO destructor that destroys all children or is this done by the
        // shared_ptr?

        std::shared_ptr<Node> addBranch(std::shared_ptr<Tile> tile, Direction
        direction);

        std::shared_ptr<Tile> getTile();
        std::shared_ptr<Node> getChild(Direction direction);
        Node *getParent();
        Direction getParentDirection();
        int getBonusSteps();
        void remove();

        void recursivePrint(int &print_depth, bool &new_line);
    };

  private:
    std::shared_ptr<Node> root_node_;

  public:
    PathTree(std::shared_ptr<Tile> tile);

    std::shared_ptr<Node> getRootNode();

    void print();
};



PathTree::PathTree(std::shared_ptr<Tile> tile) :
        root_node_(std::make_shared<Node>(tile))
{

}

std::shared_ptr<PathTree::Node> PathTree::getRootNode()
{
  return root_node_;
}

void PathTree::print()
{
  int print_depth = 0;
  bool new_line = false;

  root_node_->recursivePrint(print_depth, new_line);
}







//------------------------------------------------------------------------------
//              NODE
//------------------------------------------------------------------------------

PathTree::Node::Node(std::shared_ptr<Tile> tile, PathTree::Node *parent,
                     Direction direction, int bonusPath) :
        tile_(tile),
        parent_(parent),
        parent_direction_(direction),
        bonusPath_(bonusPath)
{
}

std::shared_ptr<PathTree::Node> PathTree::Node::addBranch(
        std::shared_ptr<Tile> tile, Direction direction)
{
  int bonusPath = bonusPath_ + tile->getStepChange();

  int array_index = directionToArrayIndex(direction);

  childs_[array_index] = std::make_shared<Node>(tile, this, direction,
                                                bonusPath);

  return childs_[array_index];
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

PathTree::Node::Node(std::shared_ptr<Tile> tile) :
        tile_(tile),
        parent_(nullptr),
        parent_direction_(Direction::OTHER),
        bonusPath_(0)
{

}

std::shared_ptr<Tile> PathTree::Node::getTile()
{
  return tile_;
}

std::shared_ptr<PathTree::Node> PathTree::Node::getChild(Direction direction)
{
  return childs_[directionToArrayIndex(direction)];
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
  return bonusPath_;
}

void PathTree::Node::remove()
{
  if(parent_ == nullptr)
    return;

  parent_->childs_[directionToArrayIndex(parent_direction_)].reset();
}

void PathTree::Node::recursivePrint(int &print_depth, bool &new_line)
{
  bool is_leave = true;
  int i; //TODO

  if(new_line)
  {
    new_line = false;

    for(i=0; i < print_depth * 15; i++)
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
  if(bonusPath_)
  {
    bracketL = '[';
    bracketR = ']';
  }

  std::cout << static_cast<char>(parent_direction_) << " " << bracketL
          << std::setw(2) << tile_->getPosition().getX() << "/"
          << std::setw(2) << tile_->getPosition().getY() << bracketR
          << std::setw(2) << bonusPath_ << " " <<
          tile_->toChar(true);

  print_depth++;

  for(i=0; i<4; i++)
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


#endif //MAZE_ALL_TREE_H
