#pragma once
#include "gameobject.h"

class Tile: public GameObject {
  public:
    Tile() { }
    Tile(int x, int y, const wchar_t *img): GameObject(x, y, img) { }
    ~Tile() { }
};