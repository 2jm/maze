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
#include <algorithm>
#include <iomanip>
#include "Game.h"
#include "CommandFastMove.h"
#include "Convert.h"
#include "FileHandler.h"
#include "PathTree.h"

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

//------------------------------------------------------------------------------
Message::Code Game::solve(const bool silent)
{
  if(game_state_ == State::NO_MAZE_LOADED)
    return Message::NO_MAZE_LOADED;

  int time = 0;
  std::vector<std::vector<std::shared_ptr<PathTree::Node>>> history;

  bool endReached = false;
  bool movesPossible = true;
  std::vector<Direction> directions;
  directions.push_back(Direction::RIGHT);
  directions.push_back(Direction::DOWN);
  directions.push_back(Direction::LEFT);
  directions.push_back(Direction::UP);


  std::shared_ptr<Tile> startTile = map_->getStartTile();
  startTile->setReachTime(time);

  PathTree tree(startTile);
  Matrix<PathTree::Node*> node_map(map_->getSize());

  node_map[startTile->getPosition()] = tree.getRootNode().get();

  history.push_back(
          std::vector<std::shared_ptr<PathTree::Node>>(1, tree.getRootNode()));

  time++;

  PathTree::Node *end_node = nullptr;


  while(movesPossible)
  {
    movesPossible = false;
    history.push_back(std::vector<std::shared_ptr<PathTree::Node>>());

    std::vector<PathTree::Node*> nodes_to_add;

    for(auto node : history[history.size()-2])
    {
      Vector2d origin;

      // move in all 4 directions
      for(auto direction : directions)
      {
        bool valid_move = false;
        Tile::EnterResult enter_result;

        origin = node->getTile()->getPosition();
        int moved_steps = node->getTile()->getReachTime();

        std::cout << origin.getX() << " " << origin.getY() << " " <<
                static_cast<char>(direction) << ": ";

        while((enter_result = (*map_)[origin + direction]->enter(origin)) ==
              Tile::MOVE_AGAIN && (*map_)[origin]->leave(direction))
        {
          if(enter_result != Tile::INVALID_MOVE)
            valid_move = true;
        }
        if(enter_result != Tile::INVALID_MOVE)
          valid_move = true;

        // the player moved
        if(valid_move)
        {
          std::cout << "valid ";

          if((*map_)[origin] == (*map_).getEndTile())
            endReached = true;

          moved_steps++;

          // check if the bonus tile was already visited
          if((*map_)[origin]->getStepChange() > 0)  // it is a bonus tile
          {
            bool used = false;

            // go through the tree
            PathTree::Node *search_node = node.get();

            while(search_node->getParent() != nullptr)
            {
              if(search_node->getTile()->getPosition()
                  == (*map_)[origin]->getPosition())
                used = true;

              std::cout << search_node->getTile()->getPosition().getX() <<
                      " " << search_node->getTile()->getPosition().getY() <<
                      ", ";


              search_node = search_node->getParent();
            }

            if(!used)
              moved_steps -= (*map_)[origin]->getStepChange();

            std::cout << "used: " << used << " ";
          }
          else
            moved_steps -= (*map_)[origin]->getStepChange();

          // man muss irgendwie alle bonusfelder die beide pfade schon
          // gesammelt haben aufsummieren und abziehen und wenn dann die steps
          // immer noch größer sind, dann überschreiben, also den alten pfad
          // komplett löschen.
          // bringt glaub ich nix
          // aber man kann noch miteinbeziehen wer die bonusfelder früher
          // gesammelt hat, früher = besser



          if((*map_)[origin]->getReachTime() > moved_steps)
          {
            std::cout << "moved steps: " << moved_steps;
            //(*map_)[origin]->setReachTime(moved_steps);
            movesPossible = true;

            std::shared_ptr<PathTree::Node> new_node =
                    node->addBranch((*map_)[origin], direction, moved_steps);

            nodes_to_add.push_back(new_node.get());

            // remove the node that was here before

            //node_map[origin] = new_node.get();

            //if(map_->getEndTile()->getPosition() ==
            //        (*map_)[origin]->getPosition())
            //  end_node = new_node.get();
          }

          if(!endReached)
            movesPossible = true;

        }

        std::cout << std::endl;
      }
    }

    // check all nodes that where added
    // if two nodes where added on the same field take the one with less steps,
    // if the steps are equal take the one that took the bonus field earlier.

    // this can be done faster
    int i, j;  //TODO
    bool go_to_next;

    for(i = 0; i < nodes_to_add.size(); i++)
    {
      go_to_next = false;

      for(j = i+1; j < nodes_to_add.size() && !go_to_next; j++)
      {
        if(nodes_to_add[i]->getTile()->getPosition() ==
                nodes_to_add[j]->getTile()->getPosition())
        {
          if(nodes_to_add[i]->getMovedSteps() >
             nodes_to_add[j]->getMovedSteps())
          {
            nodes_to_add.erase(nodes_to_add.begin() + i);
            go_to_next = true;
          }
          else if(nodes_to_add[i]->getMovedSteps() <
             nodes_to_add[j]->getMovedSteps())
          {
            nodes_to_add.erase(nodes_to_add.begin() + j);
          }
          else
          {
            // if no bonus tile was used or the same it doesn't matter which
            // one i take

            // i muas sie irgendwie parallel laffn lossn, aber des wead gestört

            // es is so: wenn sich zwei pfade treffen, de gleich viele aber
            // unterschiedliche bonusfelder verwendet haben, müssen die
            // beiden parallel weiterlaufen, vielleicht löschen sie sich
            // wieder auf.
            // dazu die moved steps in den nodes speichern und, wenn
            // parallelisiert wird die node_map duplizieren und auf der
            // jeweiligen weiterlaufen, k.a. wie das funktionieren soll, weil
            // man trotzdem immer mit den anderen parallelen maps vergleichen
            // muss damit man langsamere pfade entfernen kann.

            // ganz neue idee:
            // vorher mal einen weg suchen und dann in der nähe des weges
            // schauen ob bonusfelder da sind die sich rentieren mitzunehmen,
            // wenn ja die noch ansteuern, den neuen weg wieder checken usw...
            // im prinzip kann man das so lange machen bis man keine
            // bonusfelder in der nähe mehr findet, oder 15s um sind.
          }

          i--;
          j--;
        }
      }
    }


    std::cout << "Time:  " << time << std::endl;
    std::cout << "Count: " << history.back().size() << std::endl;
    for(int row_number = 0; row_number < map_->getSize().getY(); row_number++)
    {
      for(int column_number = 0; column_number < map_->getSize().getX();
          column_number++)
        std::cout << std::setw(3)
          << (*map_)[column_number][row_number]->getReachTime() << " ";

      std::cout << std::endl;
    }


    time++;

    if(time == 100000)
      break;
  }

  std::cout << std::endl << std::endl << " RECONSTRUCT FROM TREE " <<
          std::endl <<
          std::endl;

  map_->reset();

  // Reconstruct moves
  if(end_node != nullptr)
  {
    std::vector<Direction> moves;

    while(end_node->getParent() != nullptr)
    {
      moves.push_back(end_node->getParentDirection());
      end_node = end_node->getParent();
    }

    int move_counter;

    for(move_counter = static_cast<int>(moves.size() - 1); move_counter >= 0;
        move_counter--)
      std::cout << static_cast<char>(moves[move_counter]);

    std::cout << std::endl;
  }

  return Message::SUCCESS;
}


/*int i = 0;

while(time > 0 && i < 100)
{
  Vector2d origin;
  std::shared_ptr<Tile> smallestReachTimeTile = nullptr;  //TODO
  Direction move;

  tile->invert();

  for(auto direction : directions)
  {
    bool valid_move = false;
    Tile::EnterResult enter_result;

    origin = tile->getPosition();

    while((enter_result = (*map_)[origin + direction]->enter(origin)) ==
          Tile::MOVE_AGAIN && (*map_)[origin]->leave(direction))
    {
      if(enter_result != Tile::INVALID_MOVE)
        valid_move = true;
    }
    if(enter_result != Tile::INVALID_MOVE)
      valid_move = true;

    // the player moved
    if(valid_move)
    {
      if(smallestReachTimeTile == nullptr)
      {
        smallestReachTimeTile = (*map_)[origin];
        move = direction;
      }
      else if((*map_)[origin]->getReachTime() <
              smallestReachTimeTile->getReachTime())
      {
        smallestReachTimeTile = (*map_)[origin];
        move = direction;
      }
    }
  }

  i++;

  tile->invert();

  moves.push_back(move);
  tile = smallestReachTimeTile;
  time = tile->getReachTime();

  std::cout << static_cast<char>(move) << " " << time << std::endl;
}*/

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


