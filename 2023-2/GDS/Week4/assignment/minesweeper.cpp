#include <iostream>
#include <cstdlib>
#include <ctime>
#include "./minesweeper.h"
using namespace std;

int main() {
  srand((unsigned) time(NULL));

  MinesweeperMap *map = new MinesweeperMap(10, 10, 20);

  map->print();

  delete map;
  return 0;
}
