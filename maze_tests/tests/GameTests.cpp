//
// Created by jonas on 3/25/16.
//

#include <Game.h>
#include <FileLoadException.h>
#include "gtest/gtest.h"

#define TEST_FILES_PATH "../maze_tests/tests/test_files/"


TEST(GameTest, test_no_file)
{
  Game game;

  try
  {
    game.loadFile(TEST_FILES_PATH"not_existing_file");
    FAIL();
  }
  catch(const FileLoadException &e)
  {
    EXPECT_EQ(e.getResultCode(), RESULT_CODE::FILE_COULD_NOT_BE_OPENED);
  }
  catch(...)
  {
    FAIL();
  }
}

TEST(GameTest, test_empty)
{
  Game game;

  try
  {
    game.loadFile(TEST_FILES_PATH"empty.txt");
    FAIL();
  }
  catch(const FileLoadException &e)
  {
    EXPECT_EQ(e.getResultCode(), RESULT_CODE::INVALID_FILE);
  }
  catch(...)
  {
    FAIL();
  }
}

TEST(GameTest, test_valid_1)
{
  Game game;

  EXPECT_NO_THROW(game.loadFile(TEST_FILES_PATH
                          "valid.txt"));
}

TEST(GameTest, test_valid_2)
{
  Game game;

  EXPECT_NO_THROW(game.loadFile(TEST_FILES_PATH
                          "valid_with_moves.txt"));
}

TEST(GameTest, test_no_available_steps)
{
  Game game;

  try
  {
    game.loadFile(TEST_FILES_PATH"no_available_steps.txt");
    FAIL();
  }
  catch(const FileLoadException &e)
  {
    EXPECT_EQ(e.getResultCode(), RESULT_CODE::INVALID_FILE);
  }
  catch(...)
  {
    FAIL();
  }
}

TEST(GameTest, test_invalid_available_steps_1)
{
  Game game;

  try
  {
    game.loadFile(TEST_FILES_PATH"invalid_available_steps_1.txt");
    FAIL();
  }
  catch(const FileLoadException &e)
  {
    EXPECT_EQ(e.getResultCode(), RESULT_CODE::INVALID_FILE);
  }
  catch(...)
  {
    FAIL();
  }
}

TEST(GameTest, test_invalid_available_steps_2)
{
  Game game;

  try
  {
    game.loadFile(TEST_FILES_PATH"invalid_available_steps_2.txt");
    FAIL();
  }
  catch(const FileLoadException &e)
  {
    EXPECT_EQ(e.getResultCode(), RESULT_CODE::INVALID_FILE);
  }
  catch(...)
  {
    FAIL();
  }
}

TEST(GameTest, test_no_map)
{
  Game game;

  try
  {
    game.loadFile(TEST_FILES_PATH"no_map.txt");
    FAIL();
  }
  catch(const FileLoadException &e)
  {
    EXPECT_EQ(e.getResultCode(), RESULT_CODE::INVALID_FILE);
  }
  catch(...)
  {
    FAIL();
  }
}

TEST(GameTest, test_invalid_map)
{
  Game game;

  try
  {
    game.loadFile(TEST_FILES_PATH"invalid_map.txt");
    FAIL();
  }
  catch(const FileLoadException &e)
  {
    EXPECT_EQ(e.getResultCode(), RESULT_CODE::INVALID_FILE);
  }
  catch(...)
  {
    FAIL();
  }
}

TEST(GameTest, test_invalid_moves)
{
  Game game;

  try
  {
    game.loadFile(TEST_FILES_PATH"invalid_moves.txt");
    FAIL();
  }
  catch(const FileLoadException &e)
  {
    EXPECT_EQ(e.getResultCode(), RESULT_CODE::INVALID_MOVE);
  }
  catch(...)
  {
    FAIL();
  }
}

TEST(GameTest, test_impossible_moves)
{
  Game game;

  try
  {
    game.loadFile(TEST_FILES_PATH"impossible_moves.txt");
    FAIL();
  }
  catch(const FileLoadException &e)
  {
    EXPECT_EQ(e.getResultCode(), RESULT_CODE::INVALID_MOVE);
  }
  catch(...)
  {
    FAIL();
  }
}

TEST(GameTest, test_complete_teleporter)
{
  Game game;

  EXPECT_NO_THROW(game.loadFile(TEST_FILES_PATH
                          "complete_teleporter.txt"));
}

TEST(GameTest, test_incomplete_teleporter)
{
  Game game;

  try
  {
    game.loadFile(TEST_FILES_PATH"incomplete_teleporter.txt");
    FAIL();
  }
  catch(const FileLoadException &e)
  {
    EXPECT_EQ(e.getResultCode(), RESULT_CODE::INVALID_FILE);
  }
  catch(...)
  {
    FAIL();
  }
}

