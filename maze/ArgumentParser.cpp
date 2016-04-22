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
  // It is important that the auto save is set before the load is executed.
  // To achieve this the file names for load and save are saved and then
  // executed in the correct order
  std::string auto_save_file_name, load_file_name;

  if(argc >= 2)
  {
    int argument_index;
    for(argument_index = 1; argument_index < argc; argument_index++)
    {
      if(std::string(argv[argument_index]).compare("-m") == 0)
      {
        if(load_file_name != "")
          throw InvalidCommandLineArgumentException();

        load_file_name = getArgumentFileName(argc, argv, argument_index);
      }
      else if(std::string(argv[argument_index]).compare("-s") == 0)
      {
        if(auto_save_file_name != "")
          throw InvalidCommandLineArgumentException();

        auto_save_file_name = getArgumentFileName(argc, argv, argument_index);
      }
      else
      {
        throw InvalidCommandLineArgumentException();
      }
    }
  }

  if(auto_save_file_name != "")
    game_.setAutoSave(auto_save_file_name);

  if(load_file_name != "")
    Message::print(game_.loadFile(load_file_name));
}

const char *ArgumentParser::getArgumentFileName(int argc, char **argv,
                                                int &argument_index)
{
  if(argc >= argument_index + 2)
  {
    argument_index++;
    return argv[argument_index];
  }
  else
  {
    throw InvalidCommandLineArgumentException();
  }
}
