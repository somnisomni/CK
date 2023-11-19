#include <iostream>
#include <thread>
#include <cstdlib>
#include <ctime>
#include "util.h"
#include "gameobject.h"
#include "gamemap.h"
#include "snake.h"
#include "gamemanager.h"
#include "inputmanager.h"
using namespace std;

void inputThread() {
  while(true) {
    this_thread::sleep_for(1000ms / 120);
    InputManager::getInstance()->update();
  }
}

int main() {
  srand((unsigned)time(NULL));

  GameMap *map = new GameMap();
  Snake *snake = new Snake(map->getWidth() / 2, map->getHeight() / 2);

  GameManager::getInstance()->initGame(snake, map);

  ScreenInit();

  thread ithread(inputThread);
  ithread.detach();

  bool cont = true;
  while(cont) {
    this_thread::sleep_for(1000ms / 20);

    ScreenClear(map->getWidth(), map->getHeight());

    GameManager::getInstance()->draw();
    
    ScreenFlipping();

    GameManager::getInstance()->update();
  }

  ScreenRelease();

  ithread.~thread();
  delete snake;
  delete map;
  return 0;
}
