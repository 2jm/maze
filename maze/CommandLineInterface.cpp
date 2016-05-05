//------------------------------------------------------------------------------
// CommandLineInterface.cpp
//
// Group: Group 13624, study assistant Angela Promitzer
//
// Authors: Jonas Juffinger (1531253)
//          Matthias Klotz (1530653)
//          Johannes Kopf (1431505)
//------------------------------------------------------------------------------
//

#include <iostream>
#include <sstream>
#include <algorithm>
#include "CommandLineInterface.h"
#include "CommandLoad.h"
#include "CommandSave.h"
#include "CommandFastMove.h"
#include "CommandMove.h"
#include "CommandShow.h"
#include "CommandQuit.h"
#include "CommandReset.h"
#include "Game.h"

//------------------------------------------------------------------------------
CommandLineInterface::CommandLineInterface(Game &game) : game_(game)
{

}

//------------------------------------------------------------------------------
CommandLineInterface::~CommandLineInterface()
{
}

//------------------------------------------------------------------------------
const std::string CommandLineInterface::name_strings_[] = {
        "load",
        "save",
        "fastmove",
        "move",
        "show",
        "reset",
        "quit"
};

//------------------------------------------------------------------------------
bool CommandLineInterface::update()
{
  std::cout << "sep> ";

  std::string input_string;
  std::getline(std::cin, input_string);

  std::istringstream iss(input_string);

  std::string command;
  std::vector<std::string> params;

  iss >> command; //split the input into command and parameter

  std::string param;
  while(iss >> param)
    params.push_back(param); //write all single params into a string vector

  //transform the command into all LowerCase because its case insensitive
  std::transform(command.begin(), command.end(), command.begin(), ::tolower);

  return execute(command, params);
}

//------------------------------------------------------------------------------
bool CommandLineInterface::execute(std::string command,
                                   std::vector<std::string> params)
{
  //-----load------
  if(command == name_strings_[Name::LOAD])
  {
    CommandLoad command_load;
    Message::print(command_load.execute(game_, params));
    return true;
  }
    //-----save------
  else if(command == name_strings_[Name::SAVE])
  {
    CommandSave command_save;
    Message::print(command_save.execute(game_, params));
    return true;
  }
    //-----fastmove------
  else if(command == name_strings_[Name::FASTMOVE])
  {
    CommandFastMove command_fast_move;
    Message::print(command_fast_move.execute(game_, params));
    return true;
  }
    //-----move------
  else if(command == name_strings_[Name::MOVE])
  {
    CommandMove command_move;
    Message::Code return_code = command_move.execute(game_, params);
    Message::print(return_code);
    if(return_code == Message::NO_MORE_STEPS)
      game_.fullReset();
    return true;
  }
    //-----show------
  else if(command == name_strings_[Name::SHOW])
  {
    CommandShow command_show;
    Message::print(command_show.execute(game_, params));
    return true;
  }
    //-----reset------
  else if(command == name_strings_[Name::RESET])
  {
    CommandReset command_reset;
    Message::print(command_reset.execute(game_, params));
    return true;
  }
    //-----quit------
  else if(command == name_strings_[Name::QUIT])
  {
    CommandQuit command_quit;
    Message::Code return_code = command_quit.execute(game_, params);
    Message::print(return_code);
    return return_code != Message::BYE;
  }
    //-----empty command------
  else if(command.empty())
  {
    // do nothing
    return true;
  }

    //-----unknown command-----
  else
  {
    Message::print(Message::UNKNOWN_COMMAND);
    return true;
  }
}
