#include <iostream>
#include <thread>
#include "util.h"
#include "gameobject.h"
#include "gamemap.h"
#include "plane.h"
#include "bullet.h"
using namespace std;

int main() {
  GameMap *map = new GameMap();
  Plane *plane = new Plane(map->getWidth() / 2, map->getHeight() - 3, L"▲", map);

  Bullet *temp = new Bullet(plane->getX(), plane->getY(), L".");

  ScreenInit();

  bool cont = true;
  while(cont) {
    this_thread::sleep_for(0.3ms);

    ScreenClear(map->getWidth(), map->getHeight());

    map->draw();
    plane->draw();
    temp->draw();

    ScreenFlipping();

    plane->update();
    temp->update();
  }

  ScreenRelease();

  delete plane;
  delete map;
  return 0;
}