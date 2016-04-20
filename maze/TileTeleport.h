//------------------------------------------------------------------------------
// <Filename>.cpp
//
// Group: Group 13624, study assistant Angela Promitzer
//
// Authors: Jonas Juffinger (1531253)
// Matthias Klotz (1530653)
// Johannes Kopf (1431505)
//------------------------------------------------------------------------------
//

#ifndef MAZE_ALL_TILETELEPORT_H
#define MAZE_ALL_TILETELEPORT_H


#include <memory>
#include "Tile.h"
#include "Game.h"

class TileTeleport : public Tile
{
  private:
    std::shared_ptr<TileTeleport> corresponding_teleport_;
    char character_;

  public:
    TileTeleport(Vector2d position, char character);

    bool enter(Vector2d &source_position);

    void setCorrespondingTeleport(std::shared_ptr<TileTeleport> teleport);
};


#endif //MAZE_ALL_TILETELEPORT_H
