#include "gtest/gtest.h"
#include "Game.h"

#define TEST_FILES_PATH "../tests/testFilesSolveBasic/"

//TEST(SolveTestBasic, big)
//{
//  Game game;
//  Message::Code result = game.solve(true);
//  ASSERT_EQ(result, Message::Code::NO_MAZE_LOADED);
//  std::string file_path = TEST_FILES_PATH"big.maze";
//  ASSERT_EQ(game.loadFile(file_path), Message::SUCCESS);
//  result = game.solve(true);
//  ASSERT_EQ(result, Message::Code::SUCCESS);
//
//  ASSERT_EQ("r" ,game.solve_path);
//  ASSERT_EQ(1, game.solve_steps);
//  ASSERT_EQ(remove((file_path + "Solved").c_str()), 0);
//}

TEST(SolveTestBasic, ice_1)
{
  Game game;
  Message::Code result = game.solve(true);
  ASSERT_EQ(result, Message::Code::NO_MAZE_LOADED);
  std::string file_path = TEST_FILES_PATH"ice1.maze";
  ASSERT_EQ(game.loadFile(file_path), Message::SUCCESS);
  result = game.solve(true);
  ASSERT_EQ(result, Message::Code::SUCCESS);

  ASSERT_EQ("rdlll" ,game.solve_path);
  ASSERT_EQ(5, game.solve_steps);
  ASSERT_EQ(remove((file_path + "Solved").c_str()), 0);
}

TEST(SolveTestBasic, ice_2)
{
  Game game;
  Message::Code result = game.solve(true);
  ASSERT_EQ(result, Message::Code::NO_MAZE_LOADED);
  std::string file_path = TEST_FILES_PATH"ice2.maze";
  ASSERT_EQ(game.loadFile(file_path), Message::SUCCESS);
  result = game.solve(true);
  ASSERT_EQ(result, Message::Code::SUCCESS);

  ASSERT_EQ("rdlll" ,game.solve_path);
  ASSERT_EQ(5, game.solve_steps);
  ASSERT_EQ(remove((file_path + "Solved").c_str()), 0);
}

TEST(SolveTestBasic, ice_3)
{
  Game game;
  Message::Code result = game.solve(true);
  ASSERT_EQ(result, Message::Code::NO_MAZE_LOADED);
  std::string file_path = TEST_FILES_PATH"ice3.maze";
  ASSERT_EQ(game.loadFile(file_path), Message::SUCCESS);
  result = game.solve(true);
  ASSERT_EQ(result, Message::Code::SUCCESS);

  ASSERT_EQ("r" ,game.solve_path);
  ASSERT_EQ(1, game.solve_steps);
  ASSERT_EQ(remove((file_path + "Solved").c_str()), 0);
}

TEST(SolveTestBasic, ice_bonus)
{
  Game game;
  Message::Code result = game.solve(true);
  ASSERT_EQ(result, Message::Code::NO_MAZE_LOADED);
  std::string file_path = TEST_FILES_PATH"iceBonus.maze";
  ASSERT_EQ(game.loadFile(file_path), Message::SUCCESS);
  result = game.solve(true);
  ASSERT_EQ(result, Message::Code::SUCCESS);

  ASSERT_EQ("rr" ,game.solve_path);
  ASSERT_EQ(1, game.solve_steps);
  ASSERT_EQ(remove((file_path + "Solved").c_str()), 0);
}

TEST(SolveTestBasic, ice_quicksand1)
{
  Game game;
  Message::Code result = game.solve(true);
  ASSERT_EQ(result, Message::Code::NO_MAZE_LOADED);
  std::string file_path = TEST_FILES_PATH"iceQuicksand1.maze";
  ASSERT_EQ(game.loadFile(file_path), Message::SUCCESS);
  result = game.solve(true);
  ASSERT_EQ(result, Message::Code::SUCCESS);

  ASSERT_EQ("rr" ,game.solve_path);
  ASSERT_EQ(7, game.solve_steps);
  ASSERT_EQ(remove((file_path + "Solved").c_str()), 0);
}

TEST(SolveTestBasic, ice_teleport)
{
  Game game;
  Message::Code result = game.solve(true);
  ASSERT_EQ(result, Message::Code::NO_MAZE_LOADED);
  std::string file_path = TEST_FILES_PATH"iceTeleport.maze";
  ASSERT_EQ(game.loadFile(file_path), Message::SUCCESS);
  result = game.solve(true);
  ASSERT_EQ(result, Message::Code::SUCCESS);

  ASSERT_EQ("rrur" ,game.solve_path);
  ASSERT_EQ(4, game.solve_steps);
  ASSERT_EQ(remove((file_path + "Solved").c_str()), 0);
}

TEST(SolveTestBasic, oneway)
{
  Game game;
  Message::Code result = game.solve(true);
  ASSERT_EQ(result, Message::Code::NO_MAZE_LOADED);
  std::string file_path = TEST_FILES_PATH"oneway.maze";
  ASSERT_EQ(game.loadFile(file_path), Message::SUCCESS);
  result = game.solve(true);
  ASSERT_EQ(result, Message::Code::SUCCESS);

  ASSERT_EQ("rrrrrurrrrrrrrrrrrrrrrrrrrr" ,game.solve_path);
  ASSERT_EQ(27, game.solve_steps);
  ASSERT_EQ(remove((file_path + "Solved").c_str()), 0);
}

TEST(SolveTestBasic, quicksand_3)
{
  Game game;
  Message::Code result = game.solve(true);
  ASSERT_EQ(result, Message::Code::NO_MAZE_LOADED);
  std::string file_path = TEST_FILES_PATH"quicksand3.maze";
  ASSERT_EQ(game.loadFile(file_path), Message::SUCCESS);
  result = game.solve(true);
  ASSERT_EQ(result, Message::Code::SUCCESS);

  ASSERT_EQ("urrrrd" ,game.solve_path);
  ASSERT_EQ(6, game.solve_steps);
  ASSERT_EQ(remove((file_path + "Solved").c_str()), 0);
}

TEST(SolveTestBasic, quicksandbonus1)
{
  Game game;
  Message::Code result = game.solve(true);
  ASSERT_EQ(result, Message::Code::NO_MAZE_LOADED);
  std::string file_path = TEST_FILES_PATH"quicksandBonus1.maze";
  ASSERT_EQ(game.loadFile(file_path), Message::SUCCESS);
  result = game.solve(true);
  ASSERT_EQ(result, Message::Code::SUCCESS);

  ASSERT_EQ("rrrr" ,game.solve_path);
  ASSERT_EQ(4, game.solve_steps);
  ASSERT_EQ(remove((file_path + "Solved").c_str()), 0);
}

TEST(SolveTestBasic, quicksandbonus2)
{
  Game game;
  Message::Code result = game.solve(true);
  ASSERT_EQ(result, Message::Code::NO_MAZE_LOADED);
  std::string file_path = TEST_FILES_PATH"quicksandBonus2.maze";
  ASSERT_EQ(game.loadFile(file_path), Message::SUCCESS);
  result = game.solve(true);
  ASSERT_EQ(result, Message::Code::SUCCESS);

  ASSERT_EQ("rrrrrurrrrrrd" ,game.solve_path);
  ASSERT_EQ(-2, game.solve_steps);
  ASSERT_EQ(remove((file_path + "Solved").c_str()), 0);
}

TEST(SolveTestBasic, quicksandbonus3)
{
  Game game;
  Message::Code result = game.solve(true);
  ASSERT_EQ(result, Message::Code::NO_MAZE_LOADED);
  std::string file_path = TEST_FILES_PATH"quicksandBonus3.maze";
  ASSERT_EQ(game.loadFile(file_path), Message::SUCCESS);
  result = game.solve(true);
  ASSERT_EQ(result, Message::Code::SUCCESS);

  ASSERT_EQ("" ,game.solve_path);
  ASSERT_EQ(0, game.solve_steps);
  ASSERT_EQ(remove((file_path + "Solved").c_str()), 0);
}

TEST(SolveTestBasic, quicksand_bonus)
{
  Game game;
  Message::Code result = game.solve(true);
  ASSERT_EQ(result, Message::Code::NO_MAZE_LOADED);
  std::string file_path = TEST_FILES_PATH"quicksandBonus4.maze";
  ASSERT_EQ(game.loadFile(file_path), Message::SUCCESS);
  result = game.solve(true);
  ASSERT_EQ(result, Message::Code::SUCCESS);

  ASSERT_EQ("" ,game.solve_path);
  ASSERT_EQ(0, game.solve_steps);
  ASSERT_EQ(remove((file_path + "Solved").c_str()), 0);
}

TEST(SolveTestBasic, quicksand_bonus2)
{
  Game game;
  Message::Code result = game.solve(true);
  ASSERT_EQ(result, Message::Code::NO_MAZE_LOADED);
  std::string file_path = TEST_FILES_PATH"quicksandBonus5.maze";
  ASSERT_EQ(game.loadFile(file_path), Message::SUCCESS);
  result = game.solve(true);
  ASSERT_EQ(result, Message::Code::SUCCESS);

  ASSERT_EQ("" ,game.solve_path);
  ASSERT_EQ(0, game.solve_steps);
  ASSERT_EQ(remove((file_path + "Solved").c_str()), 0);
}