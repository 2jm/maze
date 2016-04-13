//
// Created by jonas on 3/25/16.
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

CommandLineInterface::CommandLineInterface(Game &game) : game_(game)
{

}

bool CommandLineInterface::update()
{

  std::cout << "sep> ";
  std::getline(std::cin, input_string_);

  std::istringstream iss(input_string_);
  cmd.clear();
  param.clear();
  overflow.clear();

  //Split the input into command, parameter, and the rest
  iss >> cmd;
  iss >> param;
  iss >> overflow;

  //Transform the command into all LowerCase because its case insensitive
  std::transform(cmd.begin(), cmd.end(), cmd.begin(), ::tolower);


  if(checkLine())
  {
    return execute();
  }


  return true;
}


bool CommandLineInterface::checkLine()
{
  int loop_counter;
  //check if its a correct command
  if(cmd.compare("load") &&
      cmd.compare("save") &&
      cmd.compare("fastmove") &&
      cmd.compare("move") &&
      cmd.compare("show") &&
      cmd.compare("quit") &&
      !cmd.empty()) //cmd.empty() because no input is not invalid
  {
    Message::print(ResultCode::UNKNOWN_COMMAND);
    return false;
  }

  if(!overflow.empty()) //check if there are to much params
  {
    Message::print(ResultCode::WRONG_PARAMETER_COUNT);
    return false;
  }

  //-----check load parameter------
  if(!cmd.compare("load"))
  {
    if(param.empty())
    {
      Message::print(ResultCode::WRONG_PARAMETER_COUNT);
      return false;
    }

    for (loop_counter = 0; loop_counter < param.length() ; ++loop_counter)
    {
      if (param[loop_counter] < 'A' && param[loop_counter] > 'Z' &&
          param[loop_counter] < 'a' && param[loop_counter] > 'z' &&
          param[loop_counter] < '0' && param[loop_counter] > '9' &&
          param[loop_counter] != '.' && param[loop_counter] != '/')
      {
        Message::print(ResultCode::WRONG_PARAMETER);
        return false;
      }

    }
  }

  //-----check save parameter------
  if(!cmd.compare("save"))
  {
    if(param.empty())
    {
      Message::print(ResultCode::WRONG_PARAMETER_COUNT);
      return false;
    }

    for (loop_counter = 0; loop_counter < param.length() ; ++loop_counter)
    {
      if(param[loop_counter] < 'A' && param[loop_counter] > 'Z' &&
         param[loop_counter] < 'a' && param[loop_counter] > 'z' &&
         param[loop_counter] < '0' && param[loop_counter] > '9' &&
         param[loop_counter] != '.' && param[loop_counter] != '/')
      {
        Message::print(ResultCode::WRONG_PARAMETER);
        return false;
      }

    }//check if param is correct (A-Z, a-z, 0-9, ., /)
  }

  //-----check fastmove parameter------
  if(!cmd.compare("fastmove"))
  {
    if(param.empty())
    {
      Message::print(ResultCode::WRONG_PARAMETER_COUNT);
      return false;
    }

    for (loop_counter = 0; loop_counter < param.length() ; ++loop_counter)
    {
      if(param[loop_counter] != 'u' && param[loop_counter] != 'd' &&
              param[loop_counter] != 'l' && param[loop_counter] != 'r')
      {
        Message::print(ResultCode::WRONG_PARAMETER);
        return false;
      }

    }
  }

  //-----check move parameter------
  if(!cmd.compare("move"))
  {
    if(param.empty())
    {
      Message::print(ResultCode::WRONG_PARAMETER_COUNT);
      return false;
    }

    if(param != "up" && param != "down" &&
       param != "left" && param != "right")
    {
      Message::print(ResultCode::WRONG_PARAMETER);
      return false;
    }
  }

  //-----check show parameter------
  if(!cmd.compare("show"))
  {
    if(!param.empty() && param != "more")
    {
      Message::print(ResultCode::WRONG_PARAMETER);
      return false;
    }
  }

  //-----check quit parameter------
  if(!cmd.compare("quit"))
  {
    if(!param.empty())
    {
      Message::print(ResultCode::WRONG_PARAMETER_COUNT);
      return false;
    }
  }


  return true;
}

bool CommandLineInterface::execute()
{
  //-----load------
  if(!cmd.compare("load"))
  {
    CommandLoad command_load;
    command_load.execute(game_, params);
    return true;
  }

  //-----save------
  if(!cmd.compare("save"))
  {
    CommandSave command_save;
    command_save.execute(game_, params);
    return true;
  }

  //-----fastmove------
  if(!cmd.compare("fastmove"))
  {
    CommandFastMove command_fast_move;
    command_fast_move.execute(game_, params);
    return true;
  }

  //-----move------
  if(!cmd.compare("move"))
  {
    CommandMove command_move;
    command_move.execute(game_, params);
    return true;
  }

  //-----show------
  if(!cmd.compare("show"))
  {
    CommandShow command_show;
    command_show.execute(game_, params);
    return true;
  }

  //-----quit------
  if(!cmd.compare("quit"))
  {
    CommandQuit command_quit;
    command_quit.execute(game_, params);
    return false;
  }
}
