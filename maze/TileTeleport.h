//
// Created by John on 26.03.2016.
//

#ifndef MAZE_ALL_TILETELEPORT_H
#define MAZE_ALL_TILETELEPORT_H


#include "Tile.h"
#include "Game.h"

class TileTeleport : public Tile
{
  private:
    TileTeleport *corresponding_teleport_;
    char character_;

  public:
    TileTeleport(Vector2d position, char character) : Tile(position, character)
    {}

    bool enter(Vector2d source_position, Vector2d &new_position);

    void setCorrespondingTeleport(TileTeleport *teleport);
};


#endif //MAZE_ALL_TILETELEPORT_H
