//
// Created by John on 26.03.2016.
//

#include "TileFinish.h"

TileFinish::TileFinish(Game &board) : board_(&board)
{
}

bool TileFinish::enter(Vector2d source_position, Vector2d new_position)
{
  // won the game
  board_->wonGame();
  return false;
}
