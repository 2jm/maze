//------------------------------------------------------------------------------
// CommandLineInterface.cpp
//
// Group: Group 13624, study assistant Angela Promitzer
//
// Authors: Jonas Juffinger (1531253)
// Matthias Klotz (1530653)
// Johannes Kopf (1431505)
//------------------------------------------------------------------------------
//

#include <iostream>
#include <sstream>
#include <string.h>
#include <algorithm>
#include "CommandLineInterface.h"
#include "CommandLoad.h"
#include "CommandSave.h"
#include "CommandFastMove.h"
#include "CommandMove.h"
#include "CommandShow.h"
#include "CommandQuit.h"
#include "CommandReset.h"

CommandLineInterface::CommandLineInterface(Game &game) : game_(game)
{

}

const std::string CommandLineInterface::name_strings_[] = {
        "load",
        "save",
        "fastmove",
        "move",
        "show",
        "reset",
        "quit"
};

bool CommandLineInterface::update()
{
  std::cout << "sep> ";

  std::string input_string_;
  std::getline(std::cin, input_string_);

  std::istringstream iss(input_string_);

  std::string command;
  std::vector<std::string> params;

  //Split the input into command and parameter
  iss >> command;

  std::string param;
  while(iss >> param)
    params.push_back(param);

  //Transform the command into all LowerCase because its case insensitive
  std::transform(command.begin(), command.end(), command.begin(), ::tolower);

  return execute(command, params);
}

bool CommandLineInterface::execute(std::string command, std::vector<std::string> params)
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
    Message::print(command_move.execute(game_, params));
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
    Message::print(command_quit.execute(game_, params));
    return false;
  }

  //-----unknown command-----
  else
  {
    Message::print(Message::UNKNOWN_COMMAND);
    return true;
  }
}


/*
bool CommandLineInterface::checkLine()
{
  int loop_counter;
  //check if its a correct command
  if(cmd != name_strings_[Name::LOAD] &&
      cmd != name_strings_[Name::SAVE] &&
      cmd != name_strings_[Name::FASTMOVE] &&
      cmd != name_strings_[Name::MOVE] &&
      cmd != name_strings_[Name::SHOW] &&
      cmd != name_strings_[Name::QUIT] &&
      !cmd.empty()) //cmd.empty() because no input is not invalid
  {
    Message::print(Message::UNKNOWN_COMMAND);
    return false;
  }

  if(!overflow.empty()) //check if there are to much params
  {
    Message::print(Message::WRONG_PARAMETER_COUNT);
    return false;
  }

  //-----check load parameter------
  if(!cmd.compare("load"))
  {
    if(param.empty())
    {
      Message::print(Message::WRONG_PARAMETER_COUNT);
      return false;
    }

    for (loop_counter = 0; loop_counter < param.length() ; ++loop_counter)
    {
      if (param[loop_counter] < 'A' && param[loop_counter] > 'Z' &&
          param[loop_counter] < 'a' && param[loop_counter] > 'z' &&
          param[loop_counter] < '0' && param[loop_counter] > '9' &&
          param[loop_counter] != '.' && param[loop_counter] != '/')
      {
        Message::print(Message::WRONG_PARAMETER);
        return false;
      }

    }
  }

  //-----check save parameter------
  if(!cmd.compare("save"))
  {
    if(param.empty())
    {
      Message::print(Message::WRONG_PARAMETER_COUNT);
      return false;
    }

    for (loop_counter = 0; loop_counter < param.length() ; ++loop_counter)
    {
      if(param[loop_counter] < 'A' && param[loop_counter] > 'Z' &&
         param[loop_counter] < 'a' && param[loop_counter] > 'z' &&
         param[loop_counter] < '0' && param[loop_counter] > '9' &&
         param[loop_counter] != '.' && param[loop_counter] != '/')
      {
        Message::print(Message::WRONG_PARAMETER);
        return false;
      }

    }//check if param is correct (A-Z, a-z, 0-9, ., /)
  }

  //-----check fastmove parameter------
  if(!cmd.compare("fastmove"))
  {
    if(param.empty())
    {
      Message::print(Message::WRONG_PARAMETER_COUNT);
      return false;
    }

    for (loop_counter = 0; loop_counter < param.length() ; ++loop_counter)
    {
      if(param[loop_counter] != 'u' && param[loop_counter] != 'd' &&
              param[loop_counter] != 'l' && param[loop_counter] != 'r')
      {
        Message::print(Message::WRONG_PARAMETER);
        return false;
      }

    }
  }

  //-----check move parameter------
  if(!cmd.compare("move"))
  {
    if(param.empty())
    {
      Message::print(Message::WRONG_PARAMETER_COUNT);
      return false;
    }

    if(param != "up" && param != "down" &&
       param != "left" && param != "right")
    {
      Message::print(Message::WRONG_PARAMETER);
      return false;
    }
  }

  //-----check show parameter------
  if(!cmd.compare("show"))
  {
    if(!param.empty() && param != "more")
    {
      Message::print(Message::WRONG_PARAMETER);
      return false;
    }
  }

  //-----check quit parameter------
  if(!cmd.compare("quit"))
  {
    if(!param.empty())
    {
      Message::print(Message::WRONG_PARAMETER_COUNT);
      return false;
    }
  }


  return true;
}*/
