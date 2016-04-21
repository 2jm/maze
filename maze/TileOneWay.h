//------------------------------------------------------------------------------
// TileOneWay.h
//
// Group: Group 13624, study assistant Angela Promitzer
//
// Authors: Jonas Juffinger (1531253)
//          Matthias Klotz (1530653)
//          Johannes Kopf (1431505)
//------------------------------------------------------------------------------
//

#ifndef MAZE_ALL_TILEONEWAY_H
#define MAZE_ALL_TILEONEWAY_H


#include "Tile.h"

class TileOneWay : public Tile
{
  public:
    TileOneWay(Vector2d position, char character);

    EnterResult enter(Vector2d &source_position);

    bool leave(const Direction move_direction) const override;
};


#endif //MAZE_ALL_TILEONEWAY_H
