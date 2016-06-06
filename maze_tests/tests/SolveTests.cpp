#include "gtest/gtest.h"
#include "Game.h"

#define TEST_FILES_PATH "../tests/testFilesSolve/"

TEST(SolveTest, fastmove_string)
{
  Game game;
  Message::Code result = game.solve(true);
  ASSERT_EQ(result, Message::Code::NO_MAZE_LOADED);
  std::string file_path = TEST_FILES_PATH"fastmoveString.txt";
  ASSERT_EQ(game.loadFile(file_path),
            Message::SUCCESS);
  result = game.solve(true);
  ASSERT_EQ(result, Message::Code::SUCCESS);

  ASSERT_EQ("rrr" , game.solve_path);
  ASSERT_EQ(3, game.solve_steps);

  ASSERT_EQ(remove((file_path + "Solved").c_str()), 0);
}

TEST(SolveTest, quicksand_1)
{
  Game game;
  Message::Code result = game.solve(true);
  ASSERT_EQ(result, Message::Code::NO_MAZE_LOADED);
  std::string file_path = TEST_FILES_PATH"quicksand1.txt";
  ASSERT_EQ(game.loadFile(file_path), Message::SUCCESS);
  result = game.solve(true);
  ASSERT_EQ(result, Message::Code::SUCCESS);

  ASSERT_EQ("urrrrrd" ,game.solve_path);
  ASSERT_EQ(7, game.solve_steps);
  ASSERT_EQ(remove((file_path + "Solved").c_str()), 0);
}

TEST(SolveTest, quicksand_2)
{
  Game game;
  Message::Code result = game.solve(true);
  ASSERT_EQ(result, Message::Code::NO_MAZE_LOADED);
  std::string file_path = TEST_FILES_PATH"quicksand2.txt";
  ASSERT_EQ(game.loadFile(file_path), Message::SUCCESS);
  result = game.solve(true);
  ASSERT_EQ(result, Message::Code::SUCCESS);

  ASSERT_EQ("rrrrr" ,game.solve_path);
  ASSERT_EQ(1, game.solve_steps);
  ASSERT_EQ(remove((file_path + "Solved").c_str()), 0);
}

TEST(SolveTest, quicksand_3)
{
  Game game;
  Message::Code result = game.solve(true);
  ASSERT_EQ(result, Message::Code::NO_MAZE_LOADED);
  std::string file_path = TEST_FILES_PATH"quicksand3.txt";
  ASSERT_EQ(game.loadFile(file_path), Message::SUCCESS);
  result = game.solve(true);
  ASSERT_EQ(result, Message::Code::SUCCESS);

  ASSERT_EQ("urrrrrrd" ,game.solve_path);
  ASSERT_EQ(8, game.solve_steps);
  ASSERT_EQ(remove((file_path + "Solved").c_str()), 0);
}

TEST(SolveTest, heavy_1)
{
  Game game;
  Message::Code result = game.solve(true);
  ASSERT_EQ(result, Message::Code::NO_MAZE_LOADED);
  std::string file_path = TEST_FILES_PATH"heavy1.txt";
  ASSERT_EQ(game.loadFile(file_path), Message::SUCCESS);
  result = game.solve(true);
  ASSERT_EQ(result, Message::Code::SUCCESS);

  ASSERT_EQ("urrrddl" ,game.solve_path);
  ASSERT_EQ(-3, game.solve_steps);
  ASSERT_EQ(remove((file_path + "Solved").c_str()), 0);
}

TEST(SolveTest, heavy_2)
{
  Game game;
  Message::Code result = game.solve(true);
  ASSERT_EQ(result, Message::Code::NO_MAZE_LOADED);
  std::string file_path = TEST_FILES_PATH"heavy2.txt";
  ASSERT_EQ(game.loadFile(file_path), Message::SUCCESS);
  result = game.solve(true);
  ASSERT_EQ(result, Message::Code::SUCCESS);

  ASSERT_EQ("rd" ,game.solve_path);
  ASSERT_EQ(2, game.solve_steps);
  ASSERT_EQ(remove((file_path + "Solved").c_str()), 0);
}

TEST(SolveTest, heavy_3)
{
  Game game;
  Message::Code result = game.solve(true);
  ASSERT_EQ(result, Message::Code::NO_MAZE_LOADED);
  std::string file_path = TEST_FILES_PATH"heavy3.txt";
  ASSERT_EQ(game.loadFile(file_path), Message::SUCCESS);
  result = game.solve(true);
  ASSERT_EQ(result, Message::Code::SUCCESS);

  ASSERT_EQ("rrddl" ,game.solve_path);
  ASSERT_EQ(5, game.solve_steps);
  ASSERT_EQ(remove((file_path + "Solved").c_str()), 0);
}

TEST(SolveTest, bonus_1)
{
  Game game;
  Message::Code result = game.solve(true);
  ASSERT_EQ(result, Message::Code::NO_MAZE_LOADED);
  std::string file_path = TEST_FILES_PATH"bonus1.txt";
  ASSERT_EQ(game.loadFile(file_path), Message::SUCCESS);
  result = game.solve(true);
  ASSERT_EQ(result, Message::Code::SUCCESS);

  ASSERT_EQ("rrrurrd" ,game.solve_path);
  ASSERT_EQ(2, game.solve_steps);
  ASSERT_EQ(remove((file_path + "Solved").c_str()), 0);
}

TEST(SolveTest, step_exact)
{
  Game game;
  Message::Code result = game.solve(true);
  ASSERT_EQ(result, Message::Code::NO_MAZE_LOADED);
  std::string file_path = TEST_FILES_PATH"stepExact.txt";
  ASSERT_EQ(game.loadFile(file_path), Message::SUCCESS);
  result = game.solve(true);
  ASSERT_EQ(result, Message::Code::SUCCESS);

  ASSERT_EQ("rrrrrr" ,game.solve_path);
  ASSERT_EQ(6, game.solve_steps);
  ASSERT_EQ(remove((file_path + "Solved").c_str()), 0);
}

TEST(SolveTest, step_few)
{
  Game game;
  Message::Code result = game.solve(true);
  ASSERT_EQ(result, Message::Code::NO_MAZE_LOADED);
  std::string file_path = TEST_FILES_PATH"stepFew.txt";
  ASSERT_EQ(game.loadFile(file_path), Message::SUCCESS);
  result = game.solve(true);
  ASSERT_EQ(result, Message::Code::NO_PATH_FOUND);
}

TEST(SolveTest, step_more)
{
  Game game;
  Message::Code result = game.solve(true);
  ASSERT_EQ(result, Message::Code::NO_MAZE_LOADED);
  std::string file_path = TEST_FILES_PATH"stepMore.txt";
  ASSERT_EQ(game.loadFile(file_path), Message::SUCCESS);
  result = game.solve(true);
  ASSERT_EQ(result, Message::Code::SUCCESS);

  ASSERT_EQ("rrrrrr" ,game.solve_path);
  ASSERT_EQ(6, game.solve_steps);
  ASSERT_EQ(remove((file_path + "Solved").c_str()), 0);
}