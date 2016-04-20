//------------------------------------------------------------------------------
// TileIce.h
//
// Group: Group 13624, study assistant Angela Promitzer
//
// Authors: Jonas Juffinger (1531253)
// Matthias Klotz (1530653)
// Johannes Kopf (1431505)
//------------------------------------------------------------------------------
//

#ifndef MAZE_ALL_TILEICE_H
#define MAZE_ALL_TILEICE_H


#include "Tile.h"

class TileIce : public Tile
{
  public:
    TileIce(Vector2d position);

    bool enter(Vector2d &source_position);
};


#endif //MAZE_ALL_TILEICE_H
