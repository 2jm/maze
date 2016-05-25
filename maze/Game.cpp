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

  int time = 0;   // in the first step the time is equal to the steps

  // the history stores all nodes from each time
  std::vector<std::vector<std::shared_ptr<PathTree::Node>>> history;

  // some other variables
  bool endReached = false;
  bool movesPossible = true;
  std::vector<Direction> directions;
  directions.push_back(Direction::UP);
  directions.push_back(Direction::RIGHT);
  directions.push_back(Direction::DOWN);
  directions.push_back(Direction::LEFT);

  // get the start tile and set its reachTime to 0
  std::shared_ptr<Tile> startTile = map_->getStartTile();
  startTile->setReachTime(time);

  // the end node if it is found
  PathTree::Node *end_node = nullptr;

  // create the path tree with the startTile as root node
  PathTree tree(startTile);

  // add the root node to the history
  history.push_back(
          std::vector<std::shared_ptr<PathTree::Node>>(1, tree.getRootNode()));


  // start the solving
  time++;

  // run until no moves are possible anymore
  while(movesPossible)
  {
    movesPossible = false;

    // add a new vector of nodes to the history, it will be filled in this step
    history.push_back(std::vector<std::shared_ptr<PathTree::Node>>());

    // a vector containg all nodes that should be add, it will also contain
    // multiple nodes pointing to the same tile. From this nodes only one
    // will be taken and pushed to the history.
    std::vector<std::shared_ptr<PathTree::Node>> nodes_to_add;

    // loop through all nodes that were added in the last step
    for(auto node : history[history.size() - 2])
    {
      // move in all 4 directions from this node
      for(auto direction : directions)
      {
        // the next lines are stolen from Player::move()
        bool valid_move = false;
        Tile::EnterResult enter_result;

        Vector2d origin = node->getTile()->getPosition();

        while((enter_result = (*map_)[origin + direction]->enter(origin)) ==
              Tile::MOVE_AGAIN && (*map_)[origin]->leave(direction))
        {
          if(enter_result != Tile::INVALID_MOVE)
            valid_move = true;
        }
        if(enter_result != Tile::INVALID_MOVE)
          valid_move = true;
        // until here is stolen from Player::move()

        // the player moved
        if(valid_move)
        {
          // check if he reached the end (this will not stop the solving)
          if((*map_)[origin] == (*map_).getEndTile())
            endReached = true;

          // if this tile was not reached in a previous step, enter it
          if((*map_)[origin]->getReachTime() >= time)
          {
            (*map_)[origin]->setReachTime(time);
            movesPossible = true;

            // create a new node on the tree
            std::shared_ptr<PathTree::Node> new_node =
                    node->addBranch((*map_)[origin], direction);

            nodes_to_add.push_back(new_node);

            // thinking about this and what the variable endReached is for...
            // but here is the end_node set
            if(map_->getEndTile()->getPosition()
               == (*map_)[origin]->getPosition())
              end_node = new_node.get();
          }

          // if the end is not reached moves are possible!
          if(!endReached)
            movesPossible = true;
        }
      }
    }


    // compare all nodes_to_add and check if some point to the same tile, if
    // they do take the one with more bonus steps of both have 0 bonus steps,
    // take the first one.
    // this can be done faster
    int i, j;  //TODO
    bool go_to_next;

    for(i = 0; i < nodes_to_add.size(); i++)
    {
      go_to_next = false;

      for(j = i + 1; j < nodes_to_add.size() && !go_to_next; j++)
      {
        if(nodes_to_add[i]->getTile()->getPosition() ==
           nodes_to_add[j]->getTile()->getPosition())
        {
          // if the bonus steps of j are higher remove i
          if(nodes_to_add[j]->getBonusSteps() >
             nodes_to_add[i]->getBonusSteps())
          {
            // remove it from the tree
            nodes_to_add[i]->remove();
            // remove it from the nodes_to_add vector
            nodes_to_add.erase(nodes_to_add.begin() + i);
            i--;
            go_to_next = true;
          }
          else
          {
            nodes_to_add[j]->remove();
            nodes_to_add.erase(nodes_to_add.begin() + j);
            j--;
          }
        }
      }
    }

    // add the remaining nodes to the history
    for(auto &new_node : nodes_to_add)
      history.back().push_back(new_node);

    nodes_to_add.clear();

    // print what we have got so far
    std::cout << "Time:  " << time << std::endl;
    std::cout << "Count: " << history.back().size() << std::endl;
    for(int row_number = 0; row_number < map_->getSize().getY(); row_number++)
    {
      for(int column_number = 0; column_number < map_->getSize().getX();
          column_number++)
        std::cout <<
        (((*map_)[column_number][row_number]->getReachTime() < 10) ? " " : "")
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

    // start from the end node and go to the root node, the directions are
    // pushed in the moves vector
    while(end_node->getParent() != nullptr)
    {
      moves.push_back(end_node->getParentDirection());
      end_node = end_node->getParent();
    }

    int move_counter;

    // print the moves from back to front, because this is the right direction
    for(move_counter = static_cast<int>(moves.size() - 1); move_counter >= 0;
        move_counter--)
      std::cout << static_cast<char>(moves[move_counter]);

    std::cout << std::endl;
  }

  // print the tree
  tree.print();

  return Message::SUCCESS;
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


