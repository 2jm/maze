//
// Created by jonas on 3/25/16.
//

#include "Game.h"
#include "gtest/gtest.h"

#define TEST_FILES_PATH "../maze_tests/tests/test_files/"

TEST(TileTest, test_bonus)
{
  Game game;
  EXPECT_EQ(game.loadFile(TEST_FILES_PATH"valid_bonus.txt"), ResultCode::SUCCESS);
  for(int rightMoves = 0; rightMoves < 17; rightMoves++) // TODO: check if the correct amount of rightmoves is made
  {
    game.movePlayer(Direction::RIGHT);
  }
  EXPECT_EQ(game.getStepsLeft(), 0);
  EXPECT_EQ(game.getState(), GameState::WON);
}

TEST(TileTest, test_finish)
{
  Game game;
  EXPECT_EQ(game.loadFile(TEST_FILES_PATH"valid.txt"), ResultCode::SUCCESS);
  game.movePlayer(Direction::RIGHT);
  game.movePlayer(Direction::RIGHT);
  EXPECT_EQ(game.getState(), GameState::WON);
}

TEST(TileTest, test_ice)
{
  Game game;
  EXPECT_EQ(game.loadFile(TEST_FILES_PATH"valid_ice.txt"), ResultCode::SUCCESS);
  game.movePlayer(Direction::RIGHT);
  EXPECT_EQ(game.getState(), GameState::PLAYING);
  game.movePlayer(Direction::DOWN);
  EXPECT_EQ(game.getState(), GameState::WON);
}

TEST(TileTest, test_ice_repeat_access)
{
  Game game;
  EXPECT_EQ(game.loadFile(TEST_FILES_PATH"valid_ice.txt"), ResultCode::SUCCESS);
  game.movePlayer(Direction::RIGHT);
  EXPECT_EQ(game.getState(), GameState::PLAYING);
  for(int repeat_access = 0; repeat_access < 50; repeat_access++)
  {
    game.movePlayer(Direction::LEFT);
    game.movePlayer(Direction::RIGHT);
  }
  game.movePlayer(Direction::DOWN);
  EXPECT_EQ(game.getState(), GameState::WON);
}

TEST(TileTest, test_one_way)
{
  Game game;
  EXPECT_EQ(game.loadFile(TEST_FILES_PATH"valid_one_way.txt"), ResultCode::SUCCESS);

  game.movePlayer(Direction::RIGHT);
  Vector2d tile_pos = game.getPlayer().getPosition();

  EXPECT_EQ(game.getState(), GameState::PLAYING);

  // > field
  game.movePlayer(Direction::UP);
  EXPECT_EQ(tile_pos.x(), game.getPlayer().getPosition().x());
  EXPECT_EQ(tile_pos.y(), game.getPlayer().getPosition().y());
  game.movePlayer(Direction::DOWN);
  EXPECT_EQ(tile_pos.x(), game.getPlayer().getPosition().x());
  EXPECT_EQ(tile_pos.y(), game.getPlayer().getPosition().y());
  game.movePlayer(Direction::LEFT);
  EXPECT_EQ(tile_pos.x(), game.getPlayer().getPosition().x());
  EXPECT_EQ(tile_pos.y(), game.getPlayer().getPosition().y());

  game.movePlayer(Direction::RIGHT);
  tile_pos = game.getPlayer().getPosition();

  // v field
  game.movePlayer(Direction::UP);
  EXPECT_EQ(tile_pos.x(), game.getPlayer().getPosition().x());
  EXPECT_EQ(tile_pos.y(), game.getPlayer().getPosition().y());
  game.movePlayer(Direction::RIGHT);
  EXPECT_EQ(tile_pos.x(), game.getPlayer().getPosition().x());
  EXPECT_EQ(tile_pos.y(), game.getPlayer().getPosition().y());
  game.movePlayer(Direction::LEFT);
  EXPECT_EQ(tile_pos.x(), game.getPlayer().getPosition().x());
  EXPECT_EQ(tile_pos.y(), game.getPlayer().getPosition().y());

  game.movePlayer(Direction::DOWN);
  game.movePlayer(Direction::DOWN);
  tile_pos = game.getPlayer().getPosition();

  // < field
  game.movePlayer(Direction::UP);
  EXPECT_EQ(tile_pos.x(), game.getPlayer().getPosition().x());
  EXPECT_EQ(tile_pos.y(), game.getPlayer().getPosition().y());
  game.movePlayer(Direction::RIGHT);
  EXPECT_EQ(tile_pos.x(), game.getPlayer().getPosition().x());
  EXPECT_EQ(tile_pos.y(), game.getPlayer().getPosition().y());
  game.movePlayer(Direction::DOWN);
  EXPECT_EQ(tile_pos.x(), game.getPlayer().getPosition().x());
  EXPECT_EQ(tile_pos.y(), game.getPlayer().getPosition().y());

  game.movePlayer(Direction::LEFT);
  tile_pos = game.getPlayer().getPosition();

  // ^ field
  game.movePlayer(Direction::RIGHT);
  EXPECT_EQ(tile_pos.x(), game.getPlayer().getPosition().x());
  EXPECT_EQ(tile_pos.y(), game.getPlayer().getPosition().y());
  game.movePlayer(Direction::DOWN);
  EXPECT_EQ(tile_pos.x(), game.getPlayer().getPosition().x());
  EXPECT_EQ(tile_pos.y(), game.getPlayer().getPosition().y());
  game.movePlayer(Direction::LEFT);
  EXPECT_EQ(tile_pos.x(), game.getPlayer().getPosition().x());
  EXPECT_EQ(tile_pos.y(), game.getPlayer().getPosition().y());

  game.movePlayer(Direction::UP);

  //EXPECT_EQ(game.getState(), GameState::WON);
}

TEST(TileTest, test_path)
{
  Game game;
  EXPECT_EQ(game.loadFile(TEST_FILES_PATH"valid_big.txt"), ResultCode::SUCCESS);
  game.movePlayer(Direction::RIGHT);
  game.movePlayer(Direction::DOWN);
  game.movePlayer(Direction::DOWN);
  game.movePlayer(Direction::LEFT);
  game.movePlayer(Direction::DOWN);
  game.movePlayer(Direction::DOWN);
  game.movePlayer(Direction::RIGHT);
  game.movePlayer(Direction::RIGHT);
  game.movePlayer(Direction::UP);
  EXPECT_EQ(game.getState(), GameState::WON);
}

TEST(TileTest, test_quicksand)
{
  Game game;
  EXPECT_EQ(game.loadFile(TEST_FILES_PATH"valid_quicksand.txt"), ResultCode::SUCCESS);
  for(int rightMoves = 0; rightMoves < 17; rightMoves++) // TODO: check if the correct amount of rightmoves is made
  {
    game.movePlayer(Direction::RIGHT);
  }
  EXPECT_EQ(game.getState(), GameState::WON);
}

TEST(TileTest, test_start)
{
  // start should be a normal path after first visit
  Game game;
  EXPECT_EQ(game.loadFile(TEST_FILES_PATH"valid.txt"), ResultCode::SUCCESS);
  game.movePlayer(Direction::RIGHT);
  game.movePlayer(Direction::LEFT);
  EXPECT_EQ(game.getState(), GameState::PLAYING);
  game.movePlayer(Direction::RIGHT);
  game.movePlayer(Direction::RIGHT);
  EXPECT_EQ(game.getState(), GameState::WON);
}

TEST(TileTest, test_teleporter)
{
  Game game;
  EXPECT_EQ(game.loadFile(TEST_FILES_PATH"complete_teleporter.txt"), ResultCode::SUCCESS);
  game.movePlayer(Direction::DOWN);
  game.movePlayer(Direction::UP);
  EXPECT_EQ(game.getState(), GameState::WON);
}

TEST(TileTest, test_wall)
{
  Game game;
  EXPECT_EQ(game.loadFile(TEST_FILES_PATH"valid.txt"), ResultCode::SUCCESS);
  game.movePlayer(Direction::DOWN);
  EXPECT_EQ(game.getState(), GameState::PLAYING);
  game.movePlayer(Direction::UP);
  EXPECT_EQ(game.getState(), GameState::PLAYING);
  game.movePlayer(Direction::RIGHT);
  game.movePlayer(Direction::RIGHT);
  EXPECT_EQ(game.getState(), GameState::WON);
}