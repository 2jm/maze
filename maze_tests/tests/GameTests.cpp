//
// Created by jonas on 3/25/16.
//

#include <Game.h>
#include "gtest/gtest.h"

#define TEST_FILES_PATH "../tests/testFiles/"


/*

TEST(GameTest, test_game_won)
{
  Game game;
  ASSERT_EQ(game.loadFile(TEST_FILES_PATH"valid.txt"), Message::SUCCESS);
  game.movePlayer(Direction::RIGHT);
  ASSERT_EQ(game.getState(), Game::State::PLAYING);
  game.movePlayer(Direction::RIGHT);
  ASSERT_EQ(game.getState(), Game::State::WON);
}

TEST(GameTest, test_move_after_game_won)
{
  Game game;
  ASSERT_EQ(game.loadFile(TEST_FILES_PATH"valid.txt"), Message::SUCCESS);
  game.movePlayer(Direction::RIGHT);
  ASSERT_EQ(game.getState(), Game::State::PLAYING);
  game.movePlayer(Direction::RIGHT);
  ASSERT_EQ(game.getState(), Game::State::WON);
  game.movePlayer(Direction::LEFT);
  // TODO: expect throw here?
}


TEST(GameTest, test_game_lost)
{
  Game game;
  ASSERT_EQ(game.loadFile(TEST_FILES_PATH"validInusfficientSteps.txt"), Message::SUCCESS);
  game.movePlayer(Direction::RIGHT);
  ASSERT_EQ(game.getState(), Game::State::NO_MORE_STEPS);
  game.movePlayer(Direction::RIGHT);
  ASSERT_EQ(game.getState(), Game::State::PLAYING);
}


TEST(GameTest, test_game_reload_valid_file)
{
  Game game;
  ASSERT_EQ(game.loadFile(TEST_FILES_PATH"validWithMoves.txt"), Message::SUCCESS);
  ASSERT_EQ(game.getState(), Game::State::PLAYING);
  ASSERT_EQ(2, game.getPlayer().getPosition().x());
  ASSERT_EQ(1, game.getPlayer().getPosition().y());

  ASSERT_EQ(game.loadFile(TEST_FILES_PATH"valid.txt"), Message::SUCCESS);
  ASSERT_EQ(game.getState(), Game::State::PLAYING);
  ASSERT_EQ(1, game.getPlayer().getPosition().x());
  ASSERT_EQ(1, game.getPlayer().getPosition().y());
}


TEST(GameTest, test_game_reload_invalid_file)
{
  Game game;
  ASSERT_EQ(game.loadFile(TEST_FILES_PATH"validWithMoves.txt"), Message::SUCCESS);
  ASSERT_EQ(game.getState(), Game::State::PLAYING);
  ASSERT_EQ(2, game.getPlayer().getPosition().x());
  ASSERT_EQ(1, game.getPlayer().getPosition().y());

  ASSERT_EQ(game.loadFile(TEST_FILES_PATH"invalidMap.txt"), Message::INVALID_FILE);
  ASSERT_EQ(game.getState(), Game::State::PLAYING);
  ASSERT_EQ(2, game.getPlayer().getPosition().x());
  ASSERT_EQ(1, game.getPlayer().getPosition().y());
}


TEST(GameTest, test_valid_two_teleporters_valid_move)
{
  Game game;
  ASSERT_EQ(game.loadFile(TEST_FILES_PATH"validTwoTeleportersValidMove.txt"), Message::SUCCESS);
  ASSERT_EQ(Message::SUCCESS, game.movePlayer(Direction::RIGHT));
  ASSERT_EQ(Message::SUCCESS, game.movePlayer(Direction::LEFT));
  ASSERT_EQ(Message::INVALID_MOVE, game.movePlayer(Direction::UP));
  ASSERT_EQ(Message::SUCCESS, game.movePlayer(Direction::RIGHT));
  ASSERT_EQ( Game::State::WON, game.getState());
}
*/
