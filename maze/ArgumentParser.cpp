//------------------------------------------------------------------------------
// ArgumentParser.cpp
//
// Group: Group 13624, study assistant Angela Promitzer
//
// Authors: Jonas Juffinger (1531253)
//          Matthias Klotz (1530653)
//          Johannes Kopf (1431505)
//------------------------------------------------------------------------------
//

#include <string>
#include "ArgumentParser.h"
#include "Game.h"
#include "FileHandler.h"

ArgumentParser::ArgumentParser(Game &game) : game_(game)
{

}


ArgumentParser::ArgumentParser(const ArgumentParser &original) :
        game_(original.game_)
{

}


void ArgumentParser::parse(int argc, char **argv)
{
  if(argc >= 2)
  {
    int argument_index;
    for(argument_index = 1; argument_index < argc; argument_index++)
    {
      if(std::string(argv[argument_index]).compare("-m") == 0)
      {
        const char *file_name = getArgumentFileName(argc, argv, argument_index);
        Message::print(game_.loadFile(file_name));
      }
      else if(std::string(argv[argument_index]).compare("-s") == 0)
      {
        const char *file_name = getArgumentFileName(argc, argv, argument_index);
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
                                                int &argument_index)
{
  if(argc >= argument_index + 2)
  {
    argument_index++;

    if(!FileHandler::isValidFileName(argv[argument_index]))
      throw InvalidCommandLineArgumentException();

    return argv[argument_index];
  }
  else
  {
    throw InvalidCommandLineArgumentException();
  }
}
