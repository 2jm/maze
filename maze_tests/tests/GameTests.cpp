//
// Created by jonas on 3/25/16.
//

#include <Game.h>
#include "gtest/gtest.h"

#define TEST_FILES_PATH "../maze_tests/tests/test_files/"


TEST(GameTest, test_no_file)
{
  Game game;
  ASSERT_EQ(game.loadFile(TEST_FILES_PATH"not_existing_file"), Message::FILE_COULD_NOT_BE_OPENED);
}

TEST(GameTest, test_empty)
{
  Game game;
  ASSERT_EQ(game.loadFile(TEST_FILES_PATH"empty.txt"), Message::INVALID_FILE);
}

TEST(GameTest, test_valid_1)
{
  Game game;
  ASSERT_EQ(game.loadFile(TEST_FILES_PATH"valid.txt"), Message::SUCCESS);
}

TEST(GameTest, test_valid_2)
{
  Game game;
  ASSERT_EQ(game.loadFile(TEST_FILES_PATH"valid_with_moves.txt"), Message::SUCCESS);
}

TEST(GameTest, test_no_available_steps)
{
  Game game;
  ASSERT_EQ(game.loadFile(TEST_FILES_PATH"no_available_steps.txt"), Message::INVALID_FILE);
}

TEST(GameTest, test_invalid_available_steps_1)
{
  Game game;
  ASSERT_EQ(game.loadFile(TEST_FILES_PATH"invalid_available_steps_1.txt"), Message::INVALID_FILE);
}

TEST(GameTest, test_invalid_available_steps_2)
{
  Game game;
  ASSERT_EQ(game.loadFile(TEST_FILES_PATH"invalid_available_steps_2.txt"), Message::INVALID_FILE);
}

TEST(GameTest, test_no_map)
{
  Game game;
  ASSERT_EQ(game.loadFile(TEST_FILES_PATH"no_map.txt"), Message::INVALID_FILE);
}

TEST(GameTest, test_invalid_map)
{
  Game game;
  ASSERT_EQ(game.loadFile(TEST_FILES_PATH"invalid_map.txt"), Message::INVALID_FILE);
}

TEST(GameTest, test_invalid_moves)
{
  Game game;
  ASSERT_EQ(game.loadFile(TEST_FILES_PATH"invalid_moves.txt"), Message::INVALID_PATH);
}

TEST(GameTest, test_invalid_two_starts)
{
  Game game;
  ASSERT_EQ(game.loadFile(TEST_FILES_PATH"invalid_two_starts.txt"), Message::INVALID_FILE);
}

TEST(GameTest, test_invalid_two_ends)
{
  Game game;
  ASSERT_EQ(game.loadFile(TEST_FILES_PATH"invalid_two_ends.txt"), Message::INVALID_FILE);
}

TEST(GameTest, test_impossible_moves)
{
  Game game;
  ASSERT_EQ(game.loadFile(TEST_FILES_PATH"impossible_moves.txt"), Message::INVALID_PATH);
}

TEST(GameTest, test_complete_teleporter)
{
  Game game;
  ASSERT_EQ(game.loadFile(TEST_FILES_PATH"complete_teleporter.txt"), Message::SUCCESS);
}

TEST(GameTest, test_incomplete_teleporter)
{
  Game game;
  ASSERT_EQ(game.loadFile(TEST_FILES_PATH"incomplete_teleporter.txt"), Message::INVALID_FILE);
}

TEST(GameTest, test_game_won)
{
  Game game;
  ASSERT_EQ(game.loadFile(TEST_FILES_PATH"valid.txt"), Message::SUCCESS);
  game.movePlayer(Direction::RIGHT);
  ASSERT_EQ(game.getState(), Game::PLAYING);
  game.movePlayer(Direction::RIGHT);
  ASSERT_EQ(game.getState(), Game::WON);
}

TEST(GameTest, test_move_after_game_won)
{
  Game game;
  ASSERT_EQ(game.loadFile(TEST_FILES_PATH"valid.txt"), Message::SUCCESS);
  game.movePlayer(Direction::RIGHT);
  ASSERT_EQ(game.getState(), Game::PLAYING);
  game.movePlayer(Direction::RIGHT);
  ASSERT_EQ(game.getState(), Game::WON);
  game.movePlayer(Direction::LEFT);
  // TODO: expect throw here?
}


TEST(GameTest, test_game_lost)
{
  Game game;
  ASSERT_EQ(game.loadFile(TEST_FILES_PATH"valid_inusfficient_steps.txt"), Message::SUCCESS);
  game.movePlayer(Direction::RIGHT);
  ASSERT_EQ(game.getState(), Game::NO_MORE_STEPS);
  game.movePlayer(Direction::RIGHT);
  ASSERT_EQ(game.getState(), Game::NO_MAZE_LOADED);
}


TEST(GameTest, test_game_reload_valid_file)
{
  Game game;
  ASSERT_EQ(game.loadFile(TEST_FILES_PATH"valid_with_moves.txt"), Message::SUCCESS);
  ASSERT_EQ(game.getState(), Game::PLAYING);
  ASSERT_EQ(2, game.getPlayer().getPosition().x());
  ASSERT_EQ(1, game.getPlayer().getPosition().y());

  ASSERT_EQ(game.loadFile(TEST_FILES_PATH"valid.txt"), Message::SUCCESS);
  ASSERT_EQ(game.getState(), Game::PLAYING);
  ASSERT_EQ(1, game.getPlayer().getPosition().x());
  ASSERT_EQ(1, game.getPlayer().getPosition().y());
}


TEST(GameTest, test_game_reload_invalid_file)
{
  Game game;
  ASSERT_EQ(game.loadFile(TEST_FILES_PATH"valid_with_moves.txt"), Message::SUCCESS);
  ASSERT_EQ(game.getState(), Game::PLAYING);
  ASSERT_EQ(2, game.getPlayer().getPosition().x());
  ASSERT_EQ(1, game.getPlayer().getPosition().y());

  ASSERT_EQ(game.loadFile(TEST_FILES_PATH"invalid_map.txt"), Message::INVALID_FILE);
  ASSERT_EQ(game.getState(), Game::PLAYING);
  ASSERT_EQ(2, game.getPlayer().getPosition().x());
  ASSERT_EQ(1, game.getPlayer().getPosition().y());
}