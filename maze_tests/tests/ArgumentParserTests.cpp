//
// Created by jonas on 3/25/16.
//

#include <Game.h>
#include <ArgumentParser.h>
#include "gtest/gtest.h"

TEST(ArgumentParserTest, test_valid_1)
{
  Game game;
  ArgumentParser a(game);
  Message::Code result;
  int argc = 1;
  const char *argv[] = {
          "path/to/executable"
  };

  ASSERT_NO_THROW(a.parse(argc, const_cast<char **>(argv)));
}


TEST(ArgumentParserTest, test_valid_2)
{
  Game game;
  ArgumentParser a(game);
  int argc = 5;
  const char *argv[] = {
          "path/to/executable",
          "-s",
          "filename",
          "-m",
          "filename"
  };

  ASSERT_NO_THROW(a.parse(argc, const_cast<char **>(argv)));
}


TEST(ArgumentParserTest, unknow_argument_1)
{
  Game game;
  ArgumentParser a(game);
  int argc = 2;
  const char *argv[] = {
          "path/to/executable",
          "-x"
  };

  EXPECT_THROW(a.parse(argc, const_cast<char **>(argv)),
               InvalidCommandLineArgumentException);
}


TEST(ArgumentParserTest, unknow_argument_2)
{
  Game game;
  ArgumentParser a(game);
  int argc = 3;
  const char *argv[] = {
          "path/to/executable",
          "-x",
          "filename"
  };

  EXPECT_THROW(a.parse(argc, const_cast<char **>(argv)),
               InvalidCommandLineArgumentException);
}


TEST(ArgumentParserTest, unknow_argument_3)
{
  Game game;
  ArgumentParser a(game);
  int argc = 4;
  const char *argv[] = {
          "path/to/executable",
          "-x",
          "-m",
          "filename"
  };

  EXPECT_THROW(a.parse(argc, const_cast<char **>(argv)),
               InvalidCommandLineArgumentException);
}


TEST(ArgumentParserTest, not_enough_arguments_1)
{
  Game game;
  ArgumentParser a(game);
  int argc = 2;
  const char *argv[] = {
          "path/to/executable",
          "-m",
  };

  ASSERT_THROW(a.parse(argc, const_cast<char **>(argv)), InvalidCommandLineArgumentException);
}


TEST(ArgumentParserTest, not_enough_arguments_2)
{
  Game game;
  ArgumentParser a(game);
  int argc = 4;
  const char *argv[] = {
          "path/to/executable",
          "-m",
          "filename",
          "-s"
  };

  ASSERT_THROW(a.parse(argc, const_cast<char **>(argv)), InvalidCommandLineArgumentException);
}


TEST(ArgumentParserTest, not_enough_arguments_3)
{
  Game game;
  ArgumentParser a(game);
  int argc = 4;
  const char *argv[] = {
          "path/to/executable",
          "-m",
          "-s",
          "filename"
  };

  ASSERT_THROW(a.parse(argc, const_cast<char **>(argv)), InvalidCommandLineArgumentException);
}


TEST(ArgumentParserTest, not_enough_arguments_4)
{
  Game game;
  ArgumentParser a(game);
  int argc = 5;
  const char *argv[] = {
          "path/to/executable",
          "-m",
          "-s",
          "-s",
          "filename"
  };

  ASSERT_NO_THROW(a.parse(argc, const_cast<char **>(argv)));
}


TEST(ArgumentParserTest, invalid_argument_1)
{
  Game game;
  ArgumentParser a(game);
  int argc = 3;
  const char *argv[] = {
          "path/to/executable",
          "filename",
          "-m"
  };

  ASSERT_THROW(a.parse(argc, const_cast<char **>(argv)), InvalidCommandLineArgumentException);
}


TEST(ArgumentParserTest, invalid_argument_2)
{
  Game game;
  ArgumentParser a(game);
  int argc = 4;
  const char *argv[] = {
          "path/to/executable",
          "filename",
          "-m",
          "filename"
  };

  EXPECT_THROW(a.parse(argc, const_cast<char **>(argv)),
               InvalidCommandLineArgumentException);
}