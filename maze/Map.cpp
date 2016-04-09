//
// Created by jonas on 3/25/16.
//

#include "Map.h"

using std::string;

bool Map::loadFromString(string map_string)
{
  //jede Zeile des Spielfelds muss mit # aufhören.
  is_loaded_ = true;
  return true;
}

string Map::saveToString()
{
  string res;
  return "";
}

void Map::clear()
{
  // remove the map
  is_loaded_ = false;
}

void Map::check()
{

}




