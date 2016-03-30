//
// Created by jonas on 3/25/16.
//

#include "Map.h"

bool Map::loadFromString(std::string map_string)
{
  is_loaded_ = true;
  return true;
}

std::string Map::saveToString()
{
  return "";
}

void Map::clear()
{
  // remove the map
  is_loaded_ = false;
}





