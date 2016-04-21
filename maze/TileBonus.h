//------------------------------------------------------------------------------
// TileBonus.h
//
// Group: Group 13624, study assistant Angela Promitzer
//
// Authors: Jonas Juffinger (1531253)
// Matthias Klotz (1530653)
// Johannes Kopf (1431505)
//------------------------------------------------------------------------------
//

#ifndef MAZE_ALL_TILEBONUS_H
#define MAZE_ALL_TILEBONUS_H


#include "Tile.h"
#include "Game.h"

class TileBonus : public Tile
{
  private:
    Game &board_;
    bool used_;

  public:
    TileBonus(Vector2d position, char character, Game &board);

    EnterResult enter(Vector2d &source_position);

    operator char() const;

    void reset();
};


#endif //MAZE_ALL_TILEBONUS_H
