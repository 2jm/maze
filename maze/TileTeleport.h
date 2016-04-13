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
    //Game *board_;
    TileTeleport *corr_teleport_;
  public:
    TileTeleport();//Game &board);
    bool enter(Vector2d source_position, Vector2d new_position) override;
    //setCorrespondingTeleport(TileTeleport teleport_);
};


#endif //MAZE_ALL_TILETELEPORT_H
