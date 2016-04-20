//
// Created by John on 26.03.2016.
//

#include "TileFinish.h"

TileFinish::TileFinish(Vector2d position, Game &board) : Tile(position, 'x'),
                                                         board_(board)
{

}

bool TileFinish::enter(Vector2d source_position, Vector2d &new_position)
{
  board_.wonGame();
  return false;
}
