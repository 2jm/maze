//
// Created by jonas on 3/25/16.
//

#include <Game.h>
#include "gtest/gtest.h"

#define TEST_FILES_PATH "../maze_tests/tests/test_files/"


TEST(GameTest, test_no_file)
{
  Game game;
  EXPECT_EQ(game.loadFile(TEST_FILES_PATH"not_existing_file"), RESULT_CODE::FILE_COULD_NOT_BE_OPENED);
}

TEST(GameTest, test_empty)
{
  Game game;
  EXPECT_EQ(game.loadFile(TEST_FILES_PATH"empty.txt"), RESULT_CODE::INVALID_FILE);
}

TEST(GameTest, test_valid_1)
{
  Game game;
  EXPECT_EQ(game.loadFile(TEST_FILES_PATH"valid.txt"), RESULT_CODE::SUCCESS);
}

TEST(GameTest, test_valid_2)
{
  Game game;
  EXPECT_EQ(game.loadFile(TEST_FILES_PATH"valid_with_moves.txt"), RESULT_CODE::SUCCESS);
}

TEST(GameTest, test_no_available_steps)
{
  Game game;
  EXPECT_EQ(game.loadFile(TEST_FILES_PATH"no_available_steps.txt"), RESULT_CODE::INVALID_FILE);
}

TEST(GameTest, test_invalid_available_steps_1)
{
  Game game;
  EXPECT_EQ(game.loadFile(TEST_FILES_PATH"invalid_available_steps_1.txt"), RESULT_CODE::INVALID_FILE);
}

TEST(GameTest, test_invalid_available_steps_2)
{
  Game game;
  EXPECT_EQ(game.loadFile(TEST_FILES_PATH"invalid_available_steps_2.txt"), RESULT_CODE::INVALID_FILE);
}

TEST(GameTest, test_no_map)
{
  Game game;
  EXPECT_EQ(game.loadFile(TEST_FILES_PATH"no_map.txt"), RESULT_CODE::INVALID_FILE);
}

//TODO fails
TEST(GameTest, test_invalid_map)
{
  Game game;
  EXPECT_EQ(game.loadFile(TEST_FILES_PATH"invalid_map.txt"), RESULT_CODE::INVALID_FILE);
}

//TODO fails
TEST(GameTest, test_invalid_moves)
{
  Game game;
  EXPECT_EQ(game.loadFile(TEST_FILES_PATH"invalid_moves.txt"), RESULT_CODE::INVALID_MOVE);
}

//TODO fails
TEST(GameTest, test_impossible_moves)
{
  Game game;
  EXPECT_EQ(game.loadFile(TEST_FILES_PATH"impossible_moves.txt"), RESULT_CODE::INVALID_MOVE);
}

TEST(GameTest, test_complete_teleporter)
{
  Game game;

  EXPECT_EQ(game.loadFile(TEST_FILES_PATH"complete_teleporter.txt"), RESULT_CODE::SUCCESS);
}

//TODO fails
TEST(GameTest, test_incomplete_teleporter)
{
  Game game;
  EXPECT_EQ(game.loadFile(TEST_FILES_PATH"incomplete_teleporter.txt"), RESULT_CODE::INVALID_FILE);
}

