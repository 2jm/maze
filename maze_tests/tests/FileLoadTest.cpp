//
// Created by jonas on 03.05.16.
//

#include <Game.h>
#include "gtest/gtest.h"

#define TEST_FILES_PATH "../tests/testFiles/"



TEST(FileLoadTest, all_the_files)
{
  Game game;
  Map map;

  std::vector<std::string> strings = {
          ""  //This formating is because of clion
                  "#####\n"
                  "#o x#\n"
                  "#####\n",

          ""
                  "######\n"
                  "#oAxA#\n"
                  "######\n",

          ""
                  "######\n"
                  "#oAA##\n"
                  "###c##\n"
                  "##x###\n"
                  "######\n",

          ""
                  "########################################################\n"
                  "#oABCDEFGHIJKLMNOPQRSTUVWXYZxABCDEFGHIJKLMNOPQRSTUVWXYZ#\n"
                  "########################################################\n",

          ""
                  "########################\n"
                  "#abcdefghijoxabcdefghij#\n"
                  "########################\n",

          ""
                  "######################################################\n"
                  "#ABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZ#\n"
                  "#abcdefghijabcdefghij <<vv^>><v<v+<v+^^^<vv>v<<<>>+++#\n"
                  "#             o                       x              #\n"
                  "######################################################\n"
  };

  for(auto string : strings) {
    ASSERT_EQ(map.loadFromString(string, game), true);
  }
}


TEST(FileLoadTest, test_no_file)
{
  Game game;
  ASSERT_EQ(game.loadFile(TEST_FILES_PATH"notExistingFile"), Message::FILE_COULD_NOT_BE_OPENED);
}

TEST(FileLoadTest, test_empty)
{
  Game game;
  ASSERT_EQ(game.loadFile(TEST_FILES_PATH"empty.txt"), Message::INVALID_FILE);
}

TEST(FileLoadTest, test_filename)
{
  Game game;
  ASSERT_EQ(game.loadFile(TEST_FILES_PATH"filename.txt"), Message::SUCCESS);
}

TEST(FileLoadTest, test_filename_save)
{
  Game game;
  ASSERT_EQ(game.loadFile(TEST_FILES_PATH"filename.save.txt"),
            Message::SUCCESS);
}

TEST(FileLoadTest, test_filename_save_save)
{
  Game game;
  ASSERT_EQ(game.loadFile(TEST_FILES_PATH"filename.save.save.txt"),
            Message::SUCCESS);
}

TEST(FileLoadTest, test_filename_extension_long)
{
  Game game;
  ASSERT_EQ(game.loadFile(TEST_FILES_PATH"filename.savemeiamsolong"),
            Message::SUCCESS);
}

TEST(FileLoadTest, test_filename_without_extension)
{
  Game game;
  ASSERT_EQ(game.loadFile(TEST_FILES_PATH"filename"), Message::SUCCESS);
}

TEST(FileLoadTest, test_filename_big_and_underscore)
{
  Game game;
  ASSERT_EQ(game.loadFile(TEST_FILES_PATH"FiLeNaMe_.txt"), Message::WRONG_PARAMETER);
}

TEST(FileLoadTest, test_filename_big)
{
  Game game;
  ASSERT_EQ(game.loadFile(TEST_FILES_PATH"FiLeNaMeS.txt"), Message::SUCCESS);
}

//TEST(FileLoadTest, test_invalid_filename_big)
//{
//  Game game;
//  ASSERT_EQ(game.loadFile(TEST_FILES_PATH"FiLeNaMes.txt"), Message::FILE_COULD_NOT_BE_OPENED);
//}

TEST(FileLoadTest, test_valid_1)
{
  Game game;
  ASSERT_EQ(game.loadFile(TEST_FILES_PATH"valid.txt"), Message::SUCCESS);
}

TEST(FileLoadTest, test_valid_2)
{
  Game game;
  ASSERT_EQ(game.loadFile(TEST_FILES_PATH"validWithMoves.txt"), Message::SUCCESS);
}

TEST(FileLoadTest, test_no_available_steps)
{
  Game game;
  ASSERT_EQ(game.loadFile(TEST_FILES_PATH"noAvailableSteps.txt"), Message::INVALID_FILE);
}

TEST(FileLoadTest, test_invalid_available_steps_1)
{
  Game game;
  ASSERT_EQ(game.loadFile(TEST_FILES_PATH"invalidAvailableSteps1.txt"), Message::INVALID_FILE);
}

TEST(FileLoadTest, test_invalid_available_steps_2)
{
  Game game;
  ASSERT_EQ(game.loadFile(TEST_FILES_PATH"invalidAvailableSteps2.txt"), Message::INVALID_FILE);
}

TEST(FileLoadTest, test_no_map)
{
  Game game;
  ASSERT_EQ(game.loadFile(TEST_FILES_PATH"noMap.txt"), Message::INVALID_FILE);
}

TEST(FileLoadTest, test_invalid_map)
{
  Game game;
  ASSERT_EQ(game.loadFile(TEST_FILES_PATH"invalidMap.txt"), Message::INVALID_FILE);
}

TEST(FileLoadTest, test_invalid_map2)
{
  Game game;
  ASSERT_EQ(game.loadFile(TEST_FILES_PATH"invalidMap2.txt"),
            Message::INVALID_FILE);
}

TEST(FileLoadTest, test_invalid_map3)
{
  Game game;
  ASSERT_EQ(game.loadFile(TEST_FILES_PATH"invalidMap3.txt"),
            Message::INVALID_FILE);
}

TEST(FileLoadTest, test_invalid_moves)
{
  Game game;
  ASSERT_EQ(game.loadFile(TEST_FILES_PATH"invalidMoves.txt"), Message::INVALID_FILE);
}

TEST(FileLoadTest, test_invalid_two_starts)
{
  Game game;
  ASSERT_EQ(game.loadFile(TEST_FILES_PATH"invalidTwoStarts.txt"), Message::INVALID_FILE);
}

TEST(FileLoadTest, test_invalid_two_ends)
{
  Game game;
  ASSERT_EQ(game.loadFile(TEST_FILES_PATH"invalidTwoEnds.txt"), Message::INVALID_FILE);
}

TEST(FileLoadTest, test_invalid_no_end)
{
  Game game;
  ASSERT_EQ(game.loadFile(TEST_FILES_PATH"invalidNoEnd.txt"),
            Message::INVALID_FILE);
}

TEST(FileLoadTest, test_invalid_no_start)
{
  Game game;
  ASSERT_EQ(game.loadFile(TEST_FILES_PATH"invalidNoStart.txt"),
            Message::INVALID_FILE);
}

TEST(FileLoadTest, test_impossible_moves)
{
  Game game;
  ASSERT_EQ(game.loadFile(TEST_FILES_PATH"impossibleMoves.txt"), Message::INVALID_PATH);
}

TEST(FileLoadTest, test_complete_teleporter)
{
  Game game;
  ASSERT_EQ(game.loadFile(TEST_FILES_PATH"completeTeleporter.txt"), Message::SUCCESS);
}

TEST(FileLoadTest, test_incomplete_teleporter)
{
  Game game;
  ASSERT_EQ(game.loadFile(TEST_FILES_PATH"incompleteTeleporter.txt"), Message::INVALID_FILE);
}