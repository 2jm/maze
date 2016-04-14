//
// Created by jonas on 3/25/16.
//

#include "Map.h"
#include "TileWall.h"
#include "TileStart.h"
#include "TilePath.h"
#include "TileFinish.h"
#include "TileTeleport.h"
#include "TileBonus.h"
#include "TileIce.h"
#include "TileOneWay.h"
#include "TileQuicksand.h"


using std::string;

Map::Map() : //matrix(*this),
        is_loaded_(false)
{
  //
}

bool Map::loadFromString(string map_string, Game &game)
{
  int x = 0;
  int y = 0;
  int string_position = 0;
  int pair_nr;

  TileTeleport **tiles_teleport = new TileTeleport*[26];
  std::fill(tiles_teleport, tiles_teleport + 26, nullptr);  //TODO remove '26'


  while(map_string[string_position])
  {
    x = 0;
    while(map_string[string_position] != '\n')
    {
      Vector2d tile_position(x, y);

      if(map_string[string_position] == '#')
      {
        put(new TileWall(tile_position), tile_position);
      }
      else if(map_string[string_position] >= 'A' && map_string[string_position] <= 'Z')
      {
        TileTeleport *tile_teleport = new TileTeleport(tile_position, map_string[string_position]);
        pair_nr = map_string[string_position] - 'A';  //character - ascii(A)

        if(tiles_teleport[pair_nr] == nullptr)
          tiles_teleport[pair_nr] = tile_teleport;
        else
        {
          tiles_teleport[pair_nr]->setCorrespondingTeleport(tile_teleport);
          tile_teleport->setCorrespondingTeleport(tiles_teleport[pair_nr]);
        }

        put(tile_teleport, tile_position);
      }
      else if(map_string[string_position] == 'o')
      {
        start_once_++;

        start_tile_ = new TileStart(tile_position);

        put(start_tile_, tile_position);
      }
      else if(map_string[string_position] == 'x')
      {
        end_once_++;

        end_tile_ = new TileFinish(tile_position, game);

        put(end_tile_, tile_position);
      }
      else if(map_string[string_position] >= 'a' && map_string[string_position] <= 'e')
      {
        put(new TileBonus(tile_position, map_string[string_position], game), tile_position);
      }
      else if(map_string[string_position] >= 'f' && map_string[string_position] <= 'j')
      {
        put(new TileQuicksand(tile_position, map_string[string_position], game), tile_position);
      }
      else if(map_string[string_position] == ' ')
      {
        put(new TilePath(tile_position), tile_position);
      }
      else if(map_string[string_position] == '+')
      {
        put(new TileIce(tile_position), tile_position);
      }
      else if(map_string[string_position] == '<' || map_string[string_position] == '>' ||
              map_string[string_position] == 'v' || map_string[string_position] == '^')
      {
        put(new TileOneWay(tile_position, map_string[string_position]), tile_position);
      }
      else
      {
        return false;
      }


      //Tile *tile = new Tile(tile_position, map_string[string_position]);

      //put(a , tile_position);
      x++;
      string_position++;
    }
    y++;
    string_position++;
  }

  is_loaded_ = true;
  return true;
}

void Map::clear()
{
  // remove the map
  is_loaded_ = false;
}

void Map::check(std::string map_string)
{
  Vector2d vector;
  int line_length;
  int column_height;

/******checking the border****
  vector = getSize();
  line_length = vector.x();
  column_height = vector.y();

  for (int j = 0; j < line_length; j++)
  {

  }
  */

  //check if exact one start-tile
  if(start_once_ != 0)
    Message::print(ResultCode::INVALID_FILE);
  //check if exact one end-tile
  if(end_once_ != 0)
    Message::print(ResultCode::INVALID_FILE);
  //check if if teleporter_pairs are correct
  for(int i = 0; i < 26; i++)
  {
    if(teleporter_pair_[i] != -1 && teleporter_pair_[i] != 1)
    {
      Message::print(ResultCode::INVALID_FILE);
      break;
    }

  }
}


std::string Map::toStringWithPlayer(Vector2d player_position)
{
  std::string map_string;
  unsigned int row_number, column_number;

  for(row_number = 0; row_number < getSize().y(); row_number++)
  {
    for(column_number = 0; column_number < getSize().x(); column_number++)
    {
      if(player_position == Vector2d(column_number, row_number))
        map_string += '*';
      else
        map_string += getCharacterOfElement((*this)[column_number][row_number]);
    }
    map_string += '\n';
  }

  return map_string;
}


Tile *Map::getTeleporterPair(char name) // returns the corresponding second match of the teleporter tile with the given name
{
/*  int pair_count = name - 65; // 'A' = 65, 'B' = 66, ..
  if(teleporter_pair_[pair_count] == 1) // exsits twice
  {
    std::map<int, int>::iterator pair_iterator = teleporter_pair_map_.find(pair_count);
    if(pair_iterator != teleporter_pair_map_.end()) // found value by key
    {
      int matching_teleporter = pair_iterator->second;
      int row = matching_teleporter / this->getSize().x();
      int col = matching_teleporter % this->getSize().x();
      return this->at(row, col);
    }
  }
  else if(teleporter_pair_[pair_count] == 0) // exists once
  {

  }
  else if(teleporter_pair_[pair_count] == -1) // doesn't exist
  {

  }*/
}




