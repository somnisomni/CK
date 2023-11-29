#pragma once
#include "gameobject.h"

class Bullet: public GameObject {
  public:
    Bullet(int x, int y, const wchar_t *img): GameObject(x, y, img) { };
    ~Bullet() { }

    void update() override {
      int curX = getX();
      int curY = getY();

      if(curY > 0) setXY(curX, curY - 1);
    }
};