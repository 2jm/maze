//
// Created by jonas on 5/22/16.
//

#ifndef MAZE_ALL_TREE_H
#define MAZE_ALL_TREE_H

#include <vector>
#include <memory>
#include "Tile.h"

class PathTree
{
  public:
    class Node
    {
      private:
        PathTree &tree_;
        std::shared_ptr<Tile> tile_;
        std::shared_ptr<Node> childs_[4];
        Node *parent_;
        Direction parent_direction_;
        int bonus_path_;
        int depth_;

        int directionToArrayIndex(Direction direction);

      public:
        Node(std::shared_ptr<Tile> tile, Node *parent, Direction direction,
             int bonusPath, PathTree &tree, int depth);
        Node(std::shared_ptr<Tile> tile, PathTree &tree);

        // TODO destructor that destroys all children or is this done by the
        // shared_ptr?

        std::shared_ptr<Node> addBranch(std::shared_ptr<Tile> tile, Direction
        direction);

        std::shared_ptr<Tile> getTile();
        std::shared_ptr<Node> getChild(Direction direction);
        Node *getParent();
        Direction getParentDirection();
        int getBonusSteps();
        bool isLeave();
        Node *remove();
        int getDepth();

        void recursivePrint(int &print_depth, bool &new_line);

        bool operator<(Node *node2);
    };

  private:
    std::shared_ptr<Node> root_node_;
    std::vector<Node*> leaves_;


  public:
    PathTree(std::shared_ptr<Tile> tile);
    PathTree(Node *node);

    std::shared_ptr<Node> getRootNode();

    void print();

    void trim();

    void addLeave(Node* node);
    void removeLeave(Node *node);

    void sortLeaves();

    void printLeaves();

    std::vector<Node*> &getLeaves();
};

#endif //MAZE_ALL_TREE_H
