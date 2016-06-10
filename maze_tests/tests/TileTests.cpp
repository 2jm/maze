//
// Created by jonas on 3/25/16.
//

#include "Game.h"
#include "gtest/gtest.h"

#define TEST_FILES_PATH "../tests/testFiles/"
/*

/*
TEST(TileTest, test_ice_then_teleporter)
{
  Game game;
  EXPECT_EQ(game.loadFile(TEST_FILES_PATH"iceThenTeleporter.txt"), Message::SUCCESS);
  EXPECT_EQ(game.getState(), Game::State::PLAYING);
  EXPECT_EQ(game.getStepsLeft(), 2);
  game.movePlayer(Direction::RIGHT);
  EXPECT_EQ(game.getState(), Game::State::PLAYING);
  EXPECT_EQ(game.getStepsLeft(), 1);
  game.movePlayer(Direction::LEFT);
  EXPECT_EQ(game.getStepsLeft(), 0);
  EXPECT_EQ(game.getState(), Game::State::WON);
}

TEST(TileTest, test_bonus)
{
  Game game;
  EXPECT_EQ(game.loadFile(TEST_FILES_PATH"validBonus.txt"), Message::SUCCESS);
  EXPECT_EQ(game.getState(), Game::State::PLAYING);
  for(int rightMoves = 0; rightMoves < 17; rightMoves++)
  {
    EXPECT_EQ(game.getState(), Game::State::PLAYING);
    game.movePlayer(Direction::RIGHT);
  }
  EXPECT_EQ(game.getStepsLeft(), 0);
  EXPECT_EQ(game.getState(), Game::State::WON);
}

TEST(TileTest, test_bonus_too_few_steps)
{
  Game game;
  EXPECT_EQ(game.loadFile(TEST_FILES_PATH"invalidBonus.txt"), Message::SUCCESS);
  EXPECT_EQ(game.getState(), Game::State::PLAYING);
  for(int rightMoves = 0; rightMoves < 17; rightMoves++)
  {
    EXPECT_EQ(game.getState(), Game::State::PLAYING);
    game.movePlayer(Direction::RIGHT);
  }
  EXPECT_EQ(game.getRemainingSteps(), 0);
  EXPECT_EQ(game.getState(), Game::State::NO_MORE_STEPS);
  game.movePlayer(Direction::RIGHT);
  EXPECT_EQ(game.getState(), Game::State::PLAYING);
}

TEST(TileTest, test_finish)
{
  Game game;
  EXPECT_EQ(game.loadFile(TEST_FILES_PATH"valid.txt"), Message::SUCCESS);
  EXPECT_EQ(game.getState(), Game::State::PLAYING);
  game.movePlayer(Direction::RIGHT);
  EXPECT_EQ(game.getState(), Game::State::PLAYING);
  game.movePlayer(Direction::RIGHT);
  EXPECT_EQ(game.getState(), Game::State::WON);
}

TEST(TileTest, test_ice)
{
  Game game;
  EXPECT_EQ(game.loadFile(TEST_FILES_PATH"validIce.txt"), Message::SUCCESS);
  EXPECT_EQ(game.getState(), Game::State::PLAYING);
  game.movePlayer(Direction::RIGHT);
  EXPECT_EQ(game.getState(), Game::State::PLAYING);
  game.movePlayer(Direction::DOWN);
  EXPECT_EQ(game.getState(), Game::State::WON);
}

TEST(TileTest, test_ice_repeat_access)
{
  Game game;
  EXPECT_EQ(game.loadFile(TEST_FILES_PATH"validIce.txt"), Message::SUCCESS);
  EXPECT_EQ(game.getState(), Game::State::PLAYING);
  game.movePlayer(Direction::RIGHT);
  EXPECT_EQ(game.getState(), Game::State::PLAYING);
  for(int repeat_access = 0; repeat_access < 50; repeat_access++)
  {
    game.movePlayer(Direction::LEFT);
    game.movePlayer(Direction::RIGHT);
  }
  game.movePlayer(Direction::DOWN);
  EXPECT_EQ(game.getState(), Game::State::WON);
}

TEST(TileTest, test_one_way)
{
  Game game;
  EXPECT_EQ(game.loadFile(TEST_FILES_PATH"validOneWay.txt"), Message::SUCCESS);
  EXPECT_EQ(game.getState(), Game::State::PLAYING);
  game.movePlayer(Direction::RIGHT);
  Vector2d tile_pos = game.getPlayer().getPosition();

  EXPECT_EQ(game.getState(), Game::State::PLAYING);

  // > field
  game.movePlayer(Direction::UP);
  EXPECT_EQ(tile_pos.getX(), game.getPlayer().getPosition().x());
  EXPECT_EQ(tile_pos.getY(), game.getPlayer().getPosition().y());
  game.movePlayer(Direction::DOWN);
  EXPECT_EQ(tile_pos.getX(), game.getPlayer().getPosition().x());
  EXPECT_EQ(tile_pos.getY(), game.getPlayer().getPosition().y());
  game.movePlayer(Direction::LEFT);
  EXPECT_EQ(tile_pos.getX(), game.getPlayer().getPosition().x());
  EXPECT_EQ(tile_pos.getY(), game.getPlayer().getPosition().y());

  game.movePlayer(Direction::RIGHT);
  tile_pos = game.getPlayer().getPosition();

  // v field
  game.movePlayer(Direction::UP);
  EXPECT_EQ(tile_pos.getX(), game.getPlayer().getPosition().x());
  EXPECT_EQ(tile_pos.getY(), game.getPlayer().getPosition().y());
  game.movePlayer(Direction::RIGHT);
  EXPECT_EQ(tile_pos.getX(), game.getPlayer().getPosition().x());
  EXPECT_EQ(tile_pos.getY(), game.getPlayer().getPosition().y());
  game.movePlayer(Direction::LEFT);
  EXPECT_EQ(tile_pos.getX(), game.getPlayer().getPosition().x());
  EXPECT_EQ(tile_pos.getY(), game.getPlayer().getPosition().y());

  game.movePlayer(Direction::DOWN);
  game.movePlayer(Direction::DOWN);
  tile_pos = game.getPlayer().getPosition();

  // < field
  game.movePlayer(Direction::UP);
  EXPECT_EQ(tile_pos.getX(), game.getPlayer().getPosition().x());
  EXPECT_EQ(tile_pos.getY(), game.getPlayer().getPosition().y());
  game.movePlayer(Direction::RIGHT);
  EXPECT_EQ(tile_pos.getX(), game.getPlayer().getPosition().x());
  EXPECT_EQ(tile_pos.getY(), game.getPlayer().getPosition().y());
  game.movePlayer(Direction::DOWN);
  EXPECT_EQ(tile_pos.getX(), game.getPlayer().getPosition().x());
  EXPECT_EQ(tile_pos.getY(), game.getPlayer().getPosition().y());

  game.movePlayer(Direction::LEFT);
  tile_pos = game.getPlayer().getPosition();

  // ^ field
  game.movePlayer(Direction::RIGHT);
  EXPECT_EQ(tile_pos.getX(), game.getPlayer().getPosition().x());
  EXPECT_EQ(tile_pos.getY(), game.getPlayer().getPosition().y());
  game.movePlayer(Direction::DOWN);
  EXPECT_EQ(tile_pos.getX(), game.getPlayer().getPosition().x());
  EXPECT_EQ(tile_pos.getY(), game.getPlayer().getPosition().y());
  game.movePlayer(Direction::LEFT);
  EXPECT_EQ(tile_pos.getX(), game.getPlayer().getPosition().x());
  EXPECT_EQ(tile_pos.getY(), game.getPlayer().getPosition().y());

  game.movePlayer(Direction::UP);

  //EXPECT_EQ(game.getState(), Game::State::WON);
}

TEST(TileTest, test_path)
{
  Game game;
  EXPECT_EQ(game.loadFile(TEST_FILES_PATH"validBig.txt"), Message::SUCCESS);
  EXPECT_EQ(game.getState(), Game::State::PLAYING);
  game.movePlayer(Direction::RIGHT);
  EXPECT_EQ(game.getState(), Game::State::PLAYING);
  game.movePlayer(Direction::DOWN);
  EXPECT_EQ(game.getState(), Game::State::PLAYING);
  game.movePlayer(Direction::DOWN);
  EXPECT_EQ(game.getState(), Game::State::PLAYING);
  game.movePlayer(Direction::LEFT);
  EXPECT_EQ(game.getState(), Game::State::PLAYING);
  game.movePlayer(Direction::DOWN);
  EXPECT_EQ(game.getState(), Game::State::PLAYING);
  game.movePlayer(Direction::DOWN);
  EXPECT_EQ(game.getState(), Game::State::PLAYING);
  game.movePlayer(Direction::RIGHT);
  EXPECT_EQ(game.getState(), Game::State::PLAYING);
  game.movePlayer(Direction::RIGHT);
  game.movePlayer(Direction::UP);
  EXPECT_EQ(game.getState(), Game::State::WON);
}

TEST(TileTest, test_quicksand)
{
  Game game;
  EXPECT_EQ(game.loadFile(TEST_FILES_PATH"validQuicksand.txt"), Message::SUCCESS);
  for(int rightMoves = 0; rightMoves < 17; rightMoves++)
  {
    EXPECT_EQ(game.getState(), Game::State::PLAYING);
    game.movePlayer(Direction::RIGHT);
  }
  EXPECT_EQ(game.getState(), Game::State::WON);
}

TEST(TileTest, test_start)
{
  // start should be a normal path after first visit
  Game game;
  EXPECT_EQ(game.loadFile(TEST_FILES_PATH"validStart.txt"), Message::SUCCESS);
  EXPECT_EQ(game.getState(), Game::State::PLAYING);
  game.movePlayer(Direction::RIGHT);
  EXPECT_EQ(game.getState(), Game::State::PLAYING);
  game.movePlayer(Direction::LEFT);
  EXPECT_EQ(game.getState(), Game::State::PLAYING);
  game.movePlayer(Direction::RIGHT);
  EXPECT_EQ(game.getState(), Game::State::PLAYING);
  game.movePlayer(Direction::RIGHT);
  EXPECT_EQ(game.getState(), Game::State::WON);
}

TEST(TileTest, test_teleporter)
{
  Game game;
  EXPECT_EQ(game.loadFile(TEST_FILES_PATH"completeTeleporter.txt"), Message::SUCCESS);
  EXPECT_EQ(game.getState(), Game::State::PLAYING);
  game.movePlayer(Direction::DOWN);
  EXPECT_EQ(game.getState(), Game::State::PLAYING);
  game.movePlayer(Direction::UP);
  EXPECT_EQ(game.getState(), Game::State::WON);
}

TEST(TileTest, test_wall)
{
  Game game;
  EXPECT_EQ(game.loadFile(TEST_FILES_PATH"valid.txt"), Message::SUCCESS);
  EXPECT_EQ(game.getState(), Game::State::PLAYING);
  game.movePlayer(Direction::DOWN);
  EXPECT_EQ(game.getState(), Game::State::PLAYING);
  game.movePlayer(Direction::UP);
  EXPECT_EQ(game.getState(), Game::State::PLAYING);
  game.movePlayer(Direction::RIGHT);
  game.movePlayer(Direction::RIGHT);
  EXPECT_EQ(game.getState(), Game::State::WON);
}*/
