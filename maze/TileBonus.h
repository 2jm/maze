//
// Created by John on 26.03.2016.
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
    TileBonus(Vector2d position, char character, Game &board) :
            Tile(position, character),
            board_(board)
    {}

    bool enter(Vector2d source_position, Vector2d &new_position);

    operator char() const
    {
      return (used_) ? ' ' : character_;
    }

    void setUsed(bool used);

};


#endif //MAZE_ALL_TILEBONUS_H
