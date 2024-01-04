#include <iostream>
#include "util.h"
#include "gamemap.h"
#include "bfs.h"
using namespace std;

int main() {
  GameMap *gameMap = new GameMap;

  BFS bfs(1, 1, 7, 7, gameMap);

  ScreenInit();

  while(true) {
    bfs.findPath();

    ScreenClear();

    gameMap->print();

    ScreenFlipping();
  }

  ScreenRelease();

  delete gameMap;
  return 0;
}
