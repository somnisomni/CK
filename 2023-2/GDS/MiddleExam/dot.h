#pragma once
#include <cstdlib>
#include "gameobject.h"
#include "gamemanager.h"

class Dot: public GameObject {
  public:
    Dot(): GameObject(0, 0, L"¢¿", "DOT") {
      setRandomPos();
    }

    void setRandomPos() {
      setXY(
        (rand() % (GameManager::getInstance()->getGameMap()->getWidth() - 2)) + 1,
        (rand() % (GameManager::getInstance()->getGameMap()->getHeight() - 2)) + 1
      );
    }
};