//
// Created by John on 26.03.2016.
//

#ifndef MAZE_ALL_TILEFINISH_H
#define MAZE_ALL_TILEFINISH_H


#include "Tile.h"
#include "Game.h"

class TileFinish : public Tile
{
  private:
    Game &board_;

  public:
    TileFinish(Vector2d position, Game &board) :
            Tile(position, 'x'),
            board_(board)
    {}

    bool enter(Vector2d source_position, Vector2d &new_position);
};


#endif //MAZE_ALL_TILEFINISH_H
