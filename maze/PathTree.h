//
// Created by jonas on 5/22/16.
//

#ifndef MAZE_ALL_TREE_H
#define MAZE_ALL_TREE_H

#include <vector>
#include <bits/shared_ptr.h>
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
        int moved_steps_;

        int directionToArrayIndex(Direction direction);

      public:
        Node(std::shared_ptr<Tile> tile, Node *parent, Direction direction,
             int moved_steps);
        Node(std::shared_ptr<Tile> tile);

        std::shared_ptr<Node> addBranch(std::shared_ptr<Tile> tile, Direction
        direction, int moved_steps);

        std::shared_ptr<Tile> getTile();
        std::shared_ptr<Node> getChild(Direction direction);
        Node *getParent();
        Direction getParentDirection();
        int getMovedSteps();
    };

  private:
    std::shared_ptr<Node> root_node_;

  public:
    PathTree(std::shared_ptr<Tile> tile);

    std::shared_ptr<Node> getRootNode();

};

PathTree::PathTree(std::shared_ptr<Tile> tile) :
        root_node_(std::make_shared<Node>(tile))
{

}

std::shared_ptr<PathTree::Node> PathTree::getRootNode()
{
  return root_node_;
}





PathTree::Node::Node(std::shared_ptr<Tile> tile, PathTree::Node *parent,
                     Direction direction, int moved_steps) :
        tile_(tile),
        parent_(parent),
        parent_direction_(direction),
        moved_steps_(moved_steps)
{

}

std::shared_ptr<PathTree::Node> PathTree::Node::addBranch(
        std::shared_ptr<Tile> tile, Direction direction, int moved_steps)
{
  int array_index = directionToArrayIndex(direction);

  childs_[array_index] =
          std::make_shared<Node>(tile, this, direction, moved_steps);

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
        parent_direction_(Direction::OTHER)
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

int PathTree::Node::getMovedSteps()
{
  return moved_steps_;
}

#endif //MAZE_ALL_TREE_H
