//
// Created by jonas on 3/25/16.
//

#include <string>
#include "ArgumentParser.h"
#include "Game.h"

ArgumentParser::ArgumentParser(Game &game) : game_(game)
{

}


void ArgumentParser::parse(int argc, char **argv)
{
  if(argc >= 2)
  {
    int argument;
    for (argument = 1; argument < argc; argument++)
    {
      if(std::string(argv[argument]).compare("-m") == 0)
      {
        const char *file_name = getArgumentFileName(argc, argv, argument);
        game_.loadFile(file_name);
      }
      else if(std::string(argv[argument]).compare("-s") == 0)
      {
        const char *file_name = getArgumentFileName(argc, argv, argument);
        game_.setAutoSave(file_name);
      }
      else
      {
        throw InvalidCommandLineArgumentException();
      }
    }
  }
}

const char *ArgumentParser::getArgumentFileName(int argc, char **argv,
                                                int &argument)
{
  if(argc >= argument + 2)
  {
    argument++;
    return argv[argument];
  }
  else
  {
    throw InvalidCommandLineArgumentException();
  }
}





