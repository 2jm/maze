//
// Created by jonas on 18.03.16.
//

#include "CommandLoad.h"
#include <fstream>

int CommandLoad::execute(Game &board, std::vector<std::string> &params)
{
  // Read the content of level1.txt
  ifstream input("..\\Level\\level1.txt", ios::in | ios::binary);
  if(!input.is_open())
  {
    cout << "cannot open file" << endl;
    // TODO: return
  }
  // read c-string charwise till null byte
  char c;
  while((input >> c) && c != 0)
  {
    cout << c;
  }
  cout << endl;
  input.close();
}