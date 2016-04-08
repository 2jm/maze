//
// Created by jonas on 3/25/16.
//

#include <iostream>
#include <sstream>
#include <string.h>
#include <algorithm>
#include "CommandLineInterface.h"

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
  int iterator;
  //check if its a correct command
  if(cmd.compare("load") &&
      cmd.compare("save") &&
      cmd.compare("fastmove") &&
      cmd.compare("move") &&
      cmd.compare("show") &&
      cmd.compare("quit") &&
      !cmd.empty()) //cmd.empty() because no input is not invalid
  {
    std::cout << "[ERR] Unknown command." << std::endl;
    return false;
  }

  if(!overflow.empty()) //check if there are to much params
  {
    std::cout << "[ERR] Wrong parameter count." << std::endl;
    return false;
  }

  //-----check load parameter------
  if(!cmd.compare("load"))
  {
    for (iterator = 0; iterator < param.length() ; ++iterator)
    {
      if (param[iterator] < 'A' && param[iterator] > 'Z' &&
          param[iterator] < 'a' && param[iterator] > 'z' &&
          param[iterator] < '0' && param[iterator] > '9' &&
          param[iterator] != '.' && param[iterator] != '/')
      {
        std::cout << "[ERR] Wrong parameter." << std::endl;
        return false;
      }

    }
  }

  //-----check save parameter------
  if(!cmd.compare("save"))
  {
    for (iterator = 0; iterator < param.length() ; ++iterator)
    {
      if(param[iterator] < 'A' && param[iterator] > 'Z' &&
         param[iterator] < 'a' && param[iterator] > 'z' &&
         param[iterator] < '0' && param[iterator] > '9' &&
         param[iterator] != '.' && param[iterator] != '/')
      {
        std::cout << "[ERR] Wrong parameter." << std::endl;
        return false;
      }

    }//check if param is correct (A-Z, a-z, 0-9, ., /)
  }

  //-----check fastmove parameter------
  if(!cmd.compare("fastmove"))
  {
    for (iterator = 0; iterator < param.length() ; ++iterator)
    {
      if(param[iterator] != 'u' && param[iterator] != 'd' &&
              param[iterator] != 'l' && param[iterator] != 'r')
      {
        std::cout << "[ERR] Wrong parameter." << std::endl;
        return false;
      }

    }
  }

  //-----check move parameter------
  if(!cmd.compare("move"))
  {
    if(param != "up" && param != "down" &&
       param != "left" && param != "right")
    {
      std::cout << "[ERR] Wrong parameter." << std::endl;
      return false;
    }
  }

  //-----check show parameter------
  if(!cmd.compare("show"))
  {
    if(!param.empty() && param != "more")
    {
      std::cout << "[ERR] Wrong parameter." << std::endl;
      return false;
    }
  }

  //-----check quit parameter------
  if(!cmd.compare("quit"))
  {
    if(!param.empty())
    {
      std::cout << "[ERR] Wrong parameter count." << std::endl;
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
    //load from file
    return true;
  }

  //-----save------
  if(!cmd.compare("save"))
  {
    //save in file
    return true;
  }

  //-----fastmove------
  if(!cmd.compare("fastmove"))
  {
    //execute fastmove
    return true;
  }

  //-----move------
  if(!cmd.compare("move"))
  {
    //execute move
    return true;
  }

  //-----show------
  if(!cmd.compare("show"))
  {
    //execute show
    return true;
  }

  //-----quit------
  if(!cmd.compare("quit"))
  {
    std::cout << "Bye!" << std::endl;
    return false;
  }
}
