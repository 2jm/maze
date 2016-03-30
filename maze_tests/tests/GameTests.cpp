//
// Created by jonas on 3/25/16.
//

#include <Game.h>
#include "gtest/gtest.h"

#define TEST_FILES_PATH "../maze_tests/tests/test_files/"


TEST(GameTest, test_no_file)
{
  Game game;
  EXPECT_EQ(game.loadFile(TEST_FILES_PATH"not_existing_file"), ResultCode::FILE_COULD_NOT_BE_OPENED);
}

TEST(GameTest, test_empty)
{
  Game game;
  EXPECT_EQ(game.loadFile(TEST_FILES_PATH"empty.txt"), ResultCode::INVALID_FILE);
}

TEST(GameTest, test_valid_1)
{
  Game game;
  EXPECT_EQ(game.loadFile(TEST_FILES_PATH"valid.txt"), ResultCode::SUCCESS);
}

TEST(GameTest, test_valid_2)
{
  Game game;
  EXPECT_EQ(game.loadFile(TEST_FILES_PATH"valid_with_moves.txt"), ResultCode::SUCCESS);
}

TEST(GameTest, test_no_available_steps)
{
  Game game;
  EXPECT_EQ(game.loadFile(TEST_FILES_PATH"no_available_steps.txt"), ResultCode::INVALID_FILE);
}

TEST(GameTest, test_invalid_available_steps_1)
{
  Game game;
  EXPECT_EQ(game.loadFile(TEST_FILES_PATH"invalid_available_steps_1.txt"), ResultCode::INVALID_FILE);
}

TEST(GameTest, test_invalid_available_steps_2)
{
  Game game;
  EXPECT_EQ(game.loadFile(TEST_FILES_PATH"invalid_available_steps_2.txt"), ResultCode::INVALID_FILE);
}

TEST(GameTest, test_no_map)
{
  Game game;
  EXPECT_EQ(game.loadFile(TEST_FILES_PATH"no_map.txt"), ResultCode::INVALID_FILE);
}

//TODO fails
TEST(GameTest, test_invalid_map)
{
  Game game;
  EXPECT_EQ(game.loadFile(TEST_FILES_PATH"invalid_map.txt"), ResultCode::INVALID_FILE);
}

//TODO fails
TEST(GameTest, test_invalid_moves)
{
  Game game;
  EXPECT_EQ(game.loadFile(TEST_FILES_PATH"invalid_moves.txt"), ResultCode::INVALID_MOVE);
}

//TODO fails
TEST(GameTest, test_impossible_moves)
{
  Game game;
  EXPECT_EQ(game.loadFile(TEST_FILES_PATH"impossible_moves.txt"), ResultCode::INVALID_MOVE);
}

TEST(GameTest, test_complete_teleporter)
{
  Game game;

  EXPECT_EQ(game.loadFile(TEST_FILES_PATH"complete_teleporter.txt"), ResultCode::SUCCESS);
}

//TODO fails
TEST(GameTest, test_incomplete_teleporter)
{
  Game game;
  EXPECT_EQ(game.loadFile(TEST_FILES_PATH"incomplete_teleporter.txt"), ResultCode::INVALID_FILE);
}

