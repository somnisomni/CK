#include "gamemanager.h"

void GameManager::initGame(GameObject *p, GameMap *m, GameObjectList *b) {
  plane = p;
  map = m;
  bullets = b;
}

bool GameManager::collision() {
  for(int i = 0; i < bullets->getSize(); i++) {
    GameObject *curBullet = bullets->getObject(i);
  }

  return true;
}

void GameManager::update() {
  plane->update();
  bullets->update();
  collision();
}

void GameManager::draw() {
  map->draw();
  plane->draw();
  bullets->draw();
}