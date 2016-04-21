//------------------------------------------------------------------------------
// TileWall.h
//
// Group: Group 13624, study assistant Angela Promitzer
//
// Authors: Jonas Juffinger (1531253)
//          Matthias Klotz (1530653)
//          Johannes Kopf (1431505)
//------------------------------------------------------------------------------
//

#ifndef MAZE_ALL_TILEWALL_H
#define MAZE_ALL_TILEWALL_H


#include "Tile.h"

class TileWall : public Tile
{
  public:
    TileWall(Vector2d position);

    EnterResult enter(Vector2d &source_position);
};


#endif //MAZE_ALL_TILEWALL_H
