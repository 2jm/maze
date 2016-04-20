//------------------------------------------------------------------------------
// Player.h
//
// Group: Group 13624, study assistant Angela Promitzer
//
// Authors: Jonas Juffinger (1531253)
// Matthias Klotz (1530653)
// Johannes Kopf (1431505)
//------------------------------------------------------------------------------
//

#ifndef MAZE_PLAYER_H
#define MAZE_PLAYER_H

#include "Vector2d.h"
#include "Direction.h"

class Map;

class Player
{
  private:
    Vector2d position_;
    Map &map_;

  public:
    Player(Map &map);

    bool move(Direction direction);

    Vector2d getPosition() const;

    void setPosition(Vector2d);
};


#endif //MAZE_PLAYER_H
