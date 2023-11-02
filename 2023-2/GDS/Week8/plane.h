#pragma once
#include "gameobject.h"
#include "gamemap.h"
#include "bullet.h"
#include <conio.h>

class Plane: public GameObject {
  private:
    GameMap *currentMap;
  public:
    Plane(int x, int y, const wchar_t *img, GameMap *map): GameObject(x, y, img), currentMap(map) { }
    ~Plane() { }

    void update() override {
      int curX = getX();
      int curY = getY();
      int key;

      if(_kbhit()) {
        key = _getch();

        switch(key) {
          case LEFT:
            if(curX - 1 > 0) setXY(curX - 1, curY);
            break;
          case RIGHT:
            if(curX + 1 < currentMap->getWidth() - 1) setXY(curX + 1, curY);
            break;
          case SPACE:
            break;
        }
      }
    }
};