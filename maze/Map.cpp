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

Map::Map() : matrix_(*this),
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

  start_once_ = -1;
  end_once_ = -1;

  TileTeleport **tiles_teleport = new TileTeleport*[26];
  std::fill(tiles_teleport, tiles_teleport + 26, nullptr);  //TODO remove '26'

  std::fill(teleporter_pair_, teleporter_pair_ + 26, -1);  //TODO remove '26'

  clear();

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
        teleporter_pair_[pair_nr]++;

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

  if(check())
  {
    is_loaded_ = true;
    return true;
  }

  return false;
}

bool Map::check()
{
  int line_length;
  int column_height;

  line_length = size_.x();
  column_height = size_.y();

  for (int j = 0; j < column_height; j++)
  {
    if(matrix_[0][j] == nullptr || matrix_[line_length - 1][j] == nullptr ||
            *(matrix_[0][j]) != '#' || *(matrix_[line_length - 1][j]) != '#')
      return false;
  }

  for (int j = 0; j < line_length; j++)
  {
    if(matrix_[j][0] == nullptr || matrix_[j][column_height - 1] == nullptr ||
            *(matrix_[j][0]) != '#' || *(matrix_[j][column_height - 1]) != '#')
      return false;
  }


  //check if exact one start-tile
  if(start_once_ != 0)
    return false;
  //check if exact one end-tile
  if(end_once_ != 0)
    return false;
  //check if if teleporter_pairs are correct
  for(int i = 0; i < 26; i++)
  {
    if(teleporter_pair_[i] != -1 && teleporter_pair_[i] != 1)
      return false;
  }

  return true;
}

void Map::clear()
{
  for (auto &row : rows_)
  {
    for (auto &element : row)
      delete element;
  }

  resize(0, 0);

  is_loaded_ = false;
}

void Map::reset()
{
  for (auto &row : rows_)
  {
    for (auto &element : row)
    {
      if(typeid(element).name() == "TileBonus")
        dynamic_cast<TileBonus*>(element)->setUsed(false);
    }
  }
}

std::string Map::toStringWithPlayer(Vector2d player_position)
{
  std::string map_string;
  unsigned int row_number, column_number;

  for(row_number = 0; row_number < size_.y(); row_number++)
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


