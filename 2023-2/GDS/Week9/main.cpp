#include <iostream>
#include <thread>
#include "util.h"
#include "gameobject.h"
#include "gamemap.h"
#include "plane.h"
#include "bullet.h"
#include "gamemanager.h"
using namespace std;

int main() {
  GameMap *map = new GameMap();
  Plane *plane = new Plane(map->getWidth() / 2, map->getHeight() - 3, L"▲", map);
  GameObjectList *bulletList = new GameObjectList();

  GameManager::getInstance()->initGame(plane, map, bulletList);

  ScreenInit();

  wchar_t str[100] = L" ";
  bool cont = true;
  while(cont) {
    this_thread::sleep_for(0.3ms);

    ScreenClear(map->getWidth(), map->getHeight());
    swprintf_s(str, L"b: %d", bulletList->getSize());
    GameManager::getInstance()->draw();
    ScreenFlipping();

    GameManager::getInstance()->update();
  }

  ScreenRelease();

  delete plane;
  delete map;
  delete bulletList;
  return 0;
}