//------------------------------------------------------------------------------
// Game.cpp
//
// Group: Group 13624, study assistant Angela Promitzer
//
// Authors: Jonas Juffinger (1531253)
//          Matthias Klotz (1530653)
//          Johannes Kopf (1431505)
//------------------------------------------------------------------------------
//

#include <fstream>
#include <iostream>
#include "Game.h"
#include "CommandFastMove.h"
#include "Convert.h"
#include "FileHandler.h"

//------------------------------------------------------------------------------
Game::Game() : map_(&play_map_),
               play_player_(play_map_),
               load_test_player_(load_test_map_),
               player_(&play_player_),
               game_state_(State::NO_MAZE_LOADED),
               fast_moving_(false)
{

}

//------------------------------------------------------------------------------
Game::~Game()
{

}

//------------------------------------------------------------------------------
Message::Code Game::loadFile(const std::string file_name)
{
  std::string saved_moves;
  Message::Code return_code;
  int steps_left;
  std::string map_string;
  std::ifstream input_file;

  if((return_code = FileHandler::getInputFile(file_name, input_file))
     != Message::SUCCESS)
    return return_code;

  std::getline(input_file, saved_moves);

  if((steps_left = loadAvailableSteps(input_file)) == -1)
    return Message::INVALID_FILE;

  if((map_string = loadMapString(input_file)) == "")
    return Message::INVALID_FILE;

  switchState(State::TESTING_MAP);
  *remaining_steps_ = steps_left;

  if(!map_->loadFromString(map_string, *this))
  {
    switchState(State::PREVIOUS);
    return Message::INVALID_FILE;
  }

  if((return_code = doInitialFastMove(saved_moves)) != Message::SUCCESS)
  {
    switchState(State::PREVIOUS);
    return return_code;
  }

  switchState(State::LOADING);

  *remaining_steps_ = steps_left;
  available_steps_ = steps_left;

  // we already know that the file is valid
  map_->loadFromString(map_string, *this);
  doInitialFastMove(saved_moves);

  if(game_state_ != State::WON)
    switchState(State::PLAYING);

  autoSave();
  show();

  if(game_state_ == State::WON)
    Message::print(Message::WON);

  return Message::SUCCESS;
}

//------------------------------------------------------------------------------
Message::Code Game::saveFile(const std::string file_name)
{
  Message::Code return_code;
  std::ofstream output_file;

  if((return_code = FileHandler::getOutputFile(file_name, output_file))
     != Message::SUCCESS)
    return return_code;

  if(game_state_ == State::NO_MAZE_LOADED)
    return Message::NO_MAZE_LOADED;

  for(auto move : move_history_)
    output_file << static_cast<char>(move);
  output_file << '\n';
  output_file << available_steps_ << '\n';
  output_file << play_map_.toString(true);

  return Message::SUCCESS;
}

//------------------------------------------------------------------------------
Message::Code Game::movePlayer(const Direction direction)
{
  if(game_state_ == State::WON)
    return Message::INVALID_MOVE;

  if(game_state_ == State::NO_MORE_STEPS)
    return Message::NO_MORE_STEPS;

  if(game_state_ == State::NO_MAZE_LOADED)
    return Message::NO_MAZE_LOADED;

  if(fast_moving_)
  {
    if(*remaining_steps_ == 0)
      return Message::INVALID_MOVE;

    if(player_->move(direction))
    {
      decrementRemainingSteps(1);
      fast_move_move_history_.push_back(direction);

      return Message::SUCCESS;
    }
  }
  else if(!fast_moving_ && player_->move(direction))
  {
    // decrement 1 step for a single move
    decrementRemainingSteps(1);

    if(game_state_ != State::WON && *remaining_steps_ <= 0)
      lostGame();

    move_history_.push_back(direction);
    autoSave();
    show();

    if(game_state_ == State::WON)
      Message::print(Message::WON);

    return Message::SUCCESS;
  }

  return Message::INVALID_MOVE;
}

//------------------------------------------------------------------------------
bool Game::startFastMove()
{
  if(game_state_ == State::NO_MAZE_LOADED)
    return false;

  fast_moving_ = true;
  fast_move_move_history_.clear();

  return true;
}

//------------------------------------------------------------------------------
void Game::completeFastMove()
{
  fast_moving_ = false;

  if(game_state_ != State::TESTING_MAP)
  {
    for(auto move : fast_move_move_history_)
      move_history_.push_back(move);
  }

  if(game_state_ != State::LOADING && game_state_ != State::TESTING_MAP)
  {
    autoSave();
    show();
  }

  if(player_->getPosition() == map_->getEndTile()->getPosition())
  {
    if(game_state_ != State::LOADING && game_state_ != State::TESTING_MAP)
      Message::print(Message::WON);

    wonGame();
  }
  else if(*remaining_steps_ <= 0)
    lostGame();
}

//------------------------------------------------------------------------------
void Game::cancelFastMove()
{
  if(game_state_ == State::WON)
    return;

  reset();

  //redo all moves
  for(auto direction : move_history_)
    movePlayer(direction);

  fast_moving_ = false;
}

//------------------------------------------------------------------------------
void Game::reset()
{
  *remaining_steps_ = available_steps_;
  map_->reset();
  player_->setPosition(map_->getStartTile()->getPosition());
}

//------------------------------------------------------------------------------
Message::Code Game::fullReset()
{
  if(game_state_ == State::NO_MAZE_LOADED)
    return Message::NO_MAZE_LOADED;

  reset();
  move_history_.clear();
  autoSave();
  switchState(State::PLAYING);

  return Message::SUCCESS;
}

//------------------------------------------------------------------------------
void Game::setAutoSave(const std::string file_name)
{
  auto_save_filename_ = file_name;

  if(game_state_ == State::PLAYING)
    autoSave();
}

//------------------------------------------------------------------------------
Message::Code Game::show(const bool show_more, const bool show_no_path)
{
  if(game_state_ == State::NO_MAZE_LOADED)
    return Message::NO_MAZE_LOADED;

  if(show_more || show_no_path)
  {
    Message::print(Message::REMAINING_STEPS);
    std::cout << *remaining_steps_ << '\n';

    if(!show_no_path)
    {
      Message::print(Message::MOVED_STEPS);
      for(auto move : move_history_)
        std::cout << static_cast<char>(move);
      std::cout << '\n';
    }
  }

  std::cout << map_->toStringWithPlayer(player_->getPosition());

  return Message::SUCCESS;
}


const int inf = 1 << 30;
using std::vector;

//------------------------------------------------------------------------------
Message::Code Game::solve(const bool silent)
{
  if(game_state_ == State::NO_MAZE_LOADED)
    return Message::NO_MAZE_LOADED;

  // TODO: print out correct error messages
  /*
  Fehlermeldungen
[ERR] No path found.\n
Wenn vom aktuellen Standpunkt aus kein Weg ins Ziel gefunden werden kann (Bsp: nicht genügend Schritte oder es existiert kein Pfad). In diesem Fall wird auch kein fastmove oder save Befehl ausgeführt.
[ERR] You already solved the maze.\n
Wenn sich der Spieler bereits im Ziel befindet.
   */

  // TODO: calc. path and set used steps accordingly
  int used_steps = 0;

  Vector2d size_vector = map_->getSize();

  int N = (size_vector.getX() - 2) * (size_vector.getY() - 2); // N = amount of
  // knoten (tiles to search through), -2 because wall is stripped away
  vector<vector<int>> adj(N); // adjacency matrix
  // https://de.wikipedia.org/wiki/Adjazenzmatrix

  // init adjacency matrix
  for(int i = 0; i < N; ++i)
  {
    adj[i] = vector<int>(N);
    for(int j = 0; j < N; ++j)
    {
      adj[i][j] = inf;
    }
  }

  // only loop through content of map (wall around the map is stripped away)
  for(int col = 1; col < size_vector.getY() - 1; ++col)
  {
    for(int row = 1; row < size_vector.getX() - 1; ++row)
    {
      int knotenIndex = ((col - 1) * (size_vector.getX() - 2)) + (row - 1);

      char neighborUp = '#';
      char neighborLeft = '#';
      char neighborDown = '#';
      char neighborRight = '#';

      char crtChar = map_->at(row, col).get()->toChar(false);

      // get all 4 neighbor knoten
      if(crtChar == '<')
      {
        if(row - 1 != 0)
        {
          int row_index = knotenIndex - 1;
          neighborLeft = map_->at(row - 1, col).get()->toChar(false);
          adj[knotenIndex][row_index] = getPathCost(neighborLeft);
        }
      }
      else if(crtChar == '>')
      {
        if(row + 1 != size_vector.getX() - 1)
        {
          int row_index = knotenIndex + 1;
          neighborRight = map_->at(row + 1, col).get()->toChar(false);
          adj[knotenIndex][row_index] = getPathCost(neighborRight);
        }
      }
      else if(crtChar == '^')
      {
        if(col - 1 != 0)
        {
          int row_index = knotenIndex - (size_vector.getX() - 2);
          neighborUp = map_->at(row, col - 1).get()->toChar(false);
          adj[knotenIndex][row_index] = getPathCost(neighborUp);
        }
      }
      else if(crtChar == 'v')
      {
        if(col + 1 != size_vector.getY() - 1)
        {
          int row_index = knotenIndex + (size_vector.getX() - 2);
          neighborDown = map_->at(row, col + 1).get()->toChar(false);
          adj[knotenIndex][row_index] = getPathCost(neighborDown);
        }
      }
      else
      {
        if(row - 1 != 0)
        {
          int row_index = knotenIndex - 1;
          neighborLeft = map_->at(row - 1, col).get()->toChar(false);
          adj[knotenIndex][row_index] = getPathCost(neighborLeft);
        }
        if(row + 1 != size_vector.getX() - 1)
        {
          int row_index = knotenIndex + 1;
          neighborRight = map_->at(row + 1, col).get()->toChar(false);
          adj[knotenIndex][row_index] = getPathCost(neighborRight);
        }
        if(col - 1 != 0)
        {
          int row_index = knotenIndex - (size_vector.getX() - 2);
          neighborUp = map_->at(row, col - 1).get()->toChar(false);
          adj[knotenIndex][row_index] = getPathCost(neighborUp);
        }
        if(col + 1 != size_vector.getY() - 1)
        {
          int row_index = knotenIndex + (size_vector.getX() - 2);
          neighborDown = map_->at(row, col + 1).get()->toChar(false);
          adj[knotenIndex][row_index] = getPathCost(neighborDown);
        }
      }
    }
  }

  Vector2d start_pos = map_->getStartTile().get()->getPosition();
  Vector2d end_pos = map_->getEndTile().get()->getPosition();

  int start = ((start_pos.getY() - 1) * (size_vector.getX() - 2)) +
              (start_pos.getX() - 1);
  int end = ((end_pos.getY() - 1) * (size_vector.getX() - 2)) +
            (end_pos.getX() - 1);

  std::string path = "";
  used_steps = dijk(start, end, adj, path, size_vector);

  std::cout << "The maze was solved in " << used_steps << " steps.\n";

  if(!silent)
  {
    std::cout << "Found path: " << path << '\n';
  }

  return Message::SUCCESS;
}

int Game::getPathCost(char tile_char) const
{
  int path_cost = 0; // 0 means not visitable
  int way_path_cost = 100;
  if(tile_char == ' ' || tile_char == 'x' || tile_char == 'o')
    path_cost = way_path_cost;
  else if(tile_char >= 'a' && tile_char <= 'e')
    path_cost = way_path_cost - (tile_char - 'a') * 10; // a = 90, e = 50
  else if(tile_char >= 'f' && tile_char <= 'j')
    path_cost = way_path_cost + (tile_char - 'f' + 1) * way_path_cost;
  else if(tile_char == '<' ||
          tile_char == '>' ||
          tile_char == 'v' ||
          tile_char == '^')
    path_cost = 100;
      // f = 200, j = 600
  //else if(tile_char == '#') // unnecessary, as inital state of path_cost
  // is 0
  // path_cost = 0; // 0 means not visitable
  return path_cost;
}


#include <algorithm>

// given adjacency matrix adj, finds shortest path from A to B
int Game::dijk(int A, int B, vector<vector<int>> adj, std::string &path,
               Vector2d size_vector)
{
  std::cout << "Dest: " << B << "\n";
  int n = adj.size(); // knoten
  vector<int> dist(n); // stores the distance between the knoten
  vector<bool> vis(n); // visited knoten

  for(int i = 0; i < n; ++i)
  { // init every dist with infinity
    dist[i] = inf;
  }
  dist[A] = 0;  // set source distance to 0

  for(int i = 0; i < n; ++i)
  { // loop through every knoten
    int cur = -1;
    for(int j = 0; j < n; ++j)
    { // loop again through every knoten
      if(vis[j])
        continue; // already visited, prevent going back
      if(cur == -1 || dist[j] < dist[cur])
      { // determine next knoten mit minimaler Distanz zum aktuellen Knoten (shortest path first)
        cur = j;
      }
    }

    vis[cur] = true; // visited next knoten
   //if(vis[B]) // break when end knoten has been visited
    //  break;

    for(int j = 0; j < n; ++j) // loop through the paths of each knoten
    {
      // TODO: change to inf? or remove?
      if(adj[cur][j] == 0) // not allowed path
        continue;
      int path = adj[cur][j];
      if(path != inf)
        path += dist[cur];
      if(path < dist[j])
      {
        dist[j] = path;
      }
    }
    //std::cout << cur << ":" << dist[cur] << '\n';
  }

  int crtVal = 0;
  crtVal = B; // beginning of way back
  if(dist[crtVal] == inf)
  {
    std::cout << "Level is not solvable" << '\n';
    return -1;
  }


  int row = crtVal % (size_vector.getX() - 2);
  int col = crtVal / (size_vector.getX() - 2);

  char neighbors_chars[]{'d', 'r', 'u', 'l'};

  // TODO: usage of prev, to no look at previously visited location again?
  int prev = crtVal;
  while(crtVal != A)
  {
    std::vector<int> neighbors{inf, inf, inf, inf};
    std::vector<int> row_indexes{-1, -1, -1, -1};
    // get all 4 neighbor knoten
    if(col - 1 != -1)
    {
      int row_index = crtVal - (size_vector.getX() - 2);
      row_indexes[0] = row_index;
      neighbors[0] = dist[row_index];
    }
    if(row - 1 != -1)
    {
      int row_index = crtVal - 1;
      row_indexes[1] = row_index;
      neighbors[1] = dist[row_index];
    }
    if(col != size_vector.getY() - 3)
    {
      int row_index = crtVal + (size_vector.getX() - 2);
      row_indexes[2] = row_index;
      neighbors[2] = dist[row_index];
    }
    if(row != size_vector.getX() - 3)
    {
      int row_index = crtVal + 1;
      row_indexes[3] = row_index;
      neighbors[3] = dist[row_index];
    }

    std::vector<int>::iterator result;

    // TODO: add check, if result_neighbor is inf value, then
    //        level is not solveable

    result = std::min_element(neighbors.begin(), neighbors.end());
    int result_neighbor = std::distance(neighbors.begin(), result);
    //std::cout << "min element at: " << result_neighbor << '\n';

//    if(result_neighbor == inf)
//    {
//      std::cout << "Level is not solvable" << '\n';
//      path.clear();
//      return -1;
//    }

    path.insert(0, 1, neighbors_chars[result_neighbor]);

    crtVal = row_indexes[result_neighbor];
    row = crtVal % (size_vector.getX() - 2);
    col = crtVal / (size_vector.getX() - 2);
  }

  return path.length(); //dist[B];
}

//------------------------------------------------------------------------------
void Game::wonGame()
{
  if(!fast_moving_ && game_state_ != State::TESTING_MAP)
    switchState(State::WON);
}

//------------------------------------------------------------------------------
void Game::lostGame()
{
  switchState(State::NO_MORE_STEPS);

}

//------------------------------------------------------------------------------
int Game::getRemainingSteps() const
{
  return *remaining_steps_;
}

//------------------------------------------------------------------------------
void Game::setRemainingSteps(int remaining_steps)
{
  if(remaining_steps < 0)
    remaining_steps = 0;
  *remaining_steps_ = remaining_steps;
}

//------------------------------------------------------------------------------
void Game::decrementRemainingSteps(int amount)
{
  *remaining_steps_ -= amount;
  if(*remaining_steps_ < 0)
    *remaining_steps_ = 0;
}

//------------------------------------------------------------------------------
int Game::loadAvailableSteps(std::ifstream &input_file)
{
  std::string available_steps_string;

  std::getline(input_file, available_steps_string);
  if(available_steps_string == "")
    return INVALID_AVAILABLE_STEPS;

  try //convert available_steps
  {
    int available_steps;
    available_steps = Convert::toUnsignedInt(available_steps_string);

    if(available_steps == 0)
      return INVALID_AVAILABLE_STEPS;

    return available_steps;
  }
  catch(const std::exception &e)
  {
    return INVALID_AVAILABLE_STEPS;
  }
}

//------------------------------------------------------------------------------
std::string Game::loadMapString(std::ifstream &input_file)
{
  std::string map_string;
  // read the map
  // calculate the size of the map in bytes
  std::streampos map_start = input_file.tellg();
  input_file.seekg(0, std::ios::end);
  unsigned long map_size =
          static_cast<unsigned long>(input_file.tellg() - map_start);

  if(map_size == 0)
    return "";

  // resize the map_string to this size
  map_string.resize(map_size);
  // read the map into the string, starting from where the map starts
  input_file.seekg(map_start);
  input_file.read(&map_string[0], map_size);
  // close the file
  input_file.close();

  if(map_string.back() != '\n')
    return "";

  return map_string;
}

//------------------------------------------------------------------------------
Message::Code Game::doInitialFastMove(std::string &saved_moves)
{
  player_->setPosition(map_->getStartTile()->getPosition());

  if(saved_moves != "")
  {
    CommandFastMove fast_move;
    std::vector<std::string> fast_move_params;
    fast_move_params.push_back(saved_moves);

    Message::Code return_code;

    if((return_code = fast_move.execute(*this, fast_move_params))
       != Message::SUCCESS)
    {
      if(game_state_ == State::TESTING_MAP)
      {
        if(return_code == Message::WRONG_PARAMETER)
          return_code = Message::INVALID_FILE;

        if(return_code == Message::INVALID_MOVE)
          return_code = Message::INVALID_PATH;
      }
      return return_code;
    }
  }
  return Message::SUCCESS;
}

//------------------------------------------------------------------------------
void Game::autoSave()
{
  if(auto_save_filename_ != "")
    Message::print(saveFile(auto_save_filename_));
}

//------------------------------------------------------------------------------
void Game::switchState(State new_state)
{
  if(new_state != State::PREVIOUS)
    previous_game_state_ = game_state_;

  switch(new_state)
  {
    case State::NO_MAZE_LOADED:
      game_state_ = State::NO_MAZE_LOADED;
      break;

    case State::TESTING_MAP:
      map_ = &load_test_map_;
      player_ = &load_test_player_;
      remaining_steps_ = &load_test_remaining_steps_;
      game_state_ = State::TESTING_MAP;
      break;

    case State::LOADING:
      remaining_steps_ = &play_remaining_steps_;
      map_ = &play_map_;
      player_ = &play_player_;
      game_state_ = State::LOADING;
      move_history_.clear();
      break;

    case State::PLAYING:
      game_state_ = State::PLAYING;
      break;

    case State::WON:
      game_state_ = State::WON;
      break;

    case State::NO_MORE_STEPS:
      game_state_ = State::NO_MORE_STEPS;
      break;

    case State::PREVIOUS:
      switchState(previous_game_state_);
      break;
  }
}


