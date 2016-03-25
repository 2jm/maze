//
// Created by jonas on 3/25/16.
//


#include <ArgumentParser.h>
#include "gtest/gtest.h"

TEST(ArgumentParserTest, test_correct1)
{
  ArgumentParser a;
  int argc = 1;
  const char *argv[] = {
          "path/to/executable"
  };

  try
  {
    a.parse(argc, argv);
  }
  catch(InvalidCommandLineArgumentException e)
  {
    FAIL();
  }
  catch(...)
  {
    FAIL();
  }
}


TEST(ArgumentParserTest, test_correct2)
{
  ArgumentParser a;
  int argc = 5;
  const char *argv[] = {
          "path/to/executable",
          "-s",
          "filename",
          "-m",
          "filename"
  };

  try
  {
    a.parse(argc, argv);
  }
  catch(InvalidCommandLineArgumentException e)
  {
    FAIL();
  }
  catch(...)
  {
    FAIL();
  }
}


TEST(ArgumentParserTest, unknow_argument1)
{
  ArgumentParser a;
  int argc = 5;
  const char *argv[] = {
          "path/to/executable",
          "-x"
  };

  try
  {
    a.parse(argc, argv);
    FAIL();
  }
  catch(InvalidCommandLineArgumentException e)
  {
  }
  catch(...)
  {
    FAIL();
  }
}


TEST(ArgumentParserTest, unknow_argument2)
{
  ArgumentParser a;
  int argc = 5;
  const char *argv[] = {
          "path/to/executable",
          "-x",
          "filename"
  };

  try
  {
    a.parse(argc, argv);
    FAIL();
  }
  catch(InvalidCommandLineArgumentException e)
  {
  }
  catch(...)
  {
    FAIL();
  }
}


TEST(ArgumentParserTest, unknow_argument3)
{
  ArgumentParser a;
  int argc = 5;
  const char *argv[] = {
          "path/to/executable",
          "-x",
          "-m"
                  "filename"
  };

  try
  {
    a.parse(argc, argv);
    FAIL();
  }
  catch(InvalidCommandLineArgumentException e)
  {
  }
  catch(...)
  {
    FAIL();
  }
}


TEST(ArgumentParserTest, not_enough_arguments1)
{
  ArgumentParser a;
  int argc = 5;
  const char *argv[] = {
          "path/to/executable",
          "-m",
  };

  try
  {
    a.parse(argc, argv);
    FAIL();
  }
  catch(InvalidCommandLineArgumentException e)
  {
  }
  catch(...)
  {
    FAIL();
  }
}


TEST(ArgumentParserTest, not_enough_arguments2)
{
  ArgumentParser a;
  int argc = 5;
  const char *argv[] = {
          "path/to/executable",
          "-m",
          "filename",
          "-s"
  };

  try
  {
    a.parse(argc, argv);
    FAIL();
  }
  catch(InvalidCommandLineArgumentException e)
  {
  }
  catch(...)
  {
    FAIL();
  }
}


TEST(ArgumentParserTest, not_enough_arguments3)
{
  ArgumentParser a;
  int argc = 5;
  const char *argv[] = {
          "path/to/executable",
          "-m",
          "-s",
          "filename"
  };

  try
  {
    a.parse(argc, argv);
    FAIL();
  }
  catch(InvalidCommandLineArgumentException e)
  {
  }
  catch(...)
  {
    FAIL();
  }
}


TEST(ArgumentParserTest, invalid_argument)
{
  ArgumentParser a;
  int argc = 5;
  const char *argv[] = {
          "path/to/executable",
          "filename",
          "-m"
  };

  try
  {
    a.parse(argc, argv);
    FAIL();
  }
  catch(InvalidCommandLineArgumentException e)
  {
  }
  catch(...)
  {
    FAIL();
  }
}


TEST(ArgumentParserTest, invalid_argument2)
{
  ArgumentParser a;
  int argc = 5;
  const char *argv[] = {
          "path/to/executable",
          "filename",
          "-m",
          "filename"
  };

  try
  {
    a.parse(argc, argv);
    FAIL();
  }
  catch(InvalidCommandLineArgumentException e)
  {
  }
  catch(...)
  {
    FAIL();
  }
}