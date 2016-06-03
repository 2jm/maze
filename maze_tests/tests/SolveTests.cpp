#include "gtest/gtest.h"
#include "Game.h"

#define TEST_FILES_PATH "../tests/testFilesSolve/"

TEST(SolveTest, quicksand_1)
{
  Game game;
  Message::Code result = game.solve(true);
  ASSERT_EQ(result, Message::Code::NO_MAZE_LOADED);
  ASSERT_EQ(game.loadFile(TEST_FILES_PATH"quicksand1.txt"), Message::SUCCESS);
  result = game.solve(true);
  ASSERT_EQ(result, Message::Code::SUCCESS);

  ASSERT_EQ("urrrrrd" ,game.solve_path);
  ASSERT_EQ(7 , game.solve_steps);
}

TEST(SolveTest, fastmove_string)
{
  Game game;
  Message::Code result = game.solve(true);
  ASSERT_EQ(result, Message::Code::NO_MAZE_LOADED);
  ASSERT_EQ(game.loadFile(TEST_FILES_PATH"fastmoveString.txt"),
            Message::SUCCESS);
  result = game.solve(true);
  ASSERT_EQ(result, Message::Code::SUCCESS);

  ASSERT_EQ("rrr" , game.solve_path);
  ASSERT_EQ(3, game.solve_steps);
}
