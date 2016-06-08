//
// Created by jonas on 5/22/16.
//

#ifndef MAZE_ALL_TREE_H
#define MAZE_ALL_TREE_H

#include <vector>
#include <memory>
#include "Tile.h"
#include "TileCounter.h"

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
        bool user_moved_;

        int directionToArrayIndex(Direction direction);
        bool isTileInPath(const Tile &tile);

      public:
        Node(std::shared_ptr<Tile> tile, Node *parent, Direction direction,
             int bonusPath, PathTree &tree, int depth,
             bool user_moved = false);
        Node(std::shared_ptr<Tile> tile, PathTree &tree,
             bool user_moved = false);

        Node* addBranch(std::shared_ptr<Tile> tile, Direction direction,
                        bool user_moved = false);

        std::shared_ptr<Tile> getTile();
        Node *getChild(Direction direction);
        Node *getChild(int index);
        Node *getParent();
        Direction getParentDirection();
        int getBonusSteps();
        bool isLeave();
        Node *remove();
        int getDepth();
        bool isUserMoved();
        void setUserMoved(bool user_moved);

        void recursivePrint(int &print_depth, bool &new_line);

        std::shared_ptr<PathTree> getTreeToNode();

        bool operator<(Node *node2);
    };

  private:
    std::shared_ptr<Node> root_node_;
    std::vector<Node*> leaves_;
    Node* finish_node_;

  public:
    PathTree(std::shared_ptr<Tile> tile);

    Node* getRootNode();

    void print();

    void cut();
    void trim();

    void addLeave(Node* node);
    void removeLeave(Node *node);
    void sortLeaves();
    void printLeaves();
    std::vector<Node*> &getLeaves();
    void addFinishNode(Node* node);
    Node* getFinishNode();
    Node* getDeepestLeave();

    int getPathLength();

    std::string reconstructMoves(
            std::vector<std::shared_ptr<TileCounter>> &counter_tiles,
            std::vector<int> &counter_tiles_start_values);

    bool checkStepCount(int available_steps);
};

#endif //MAZE_ALL_TREE_H
