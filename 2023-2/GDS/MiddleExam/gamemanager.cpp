#include "gamemanager.h"
#include "snake.h"
#include "dot.h"

GameManager* GameManager::_instance = nullptr;

GameManager* GameManager::getInstance() {
  if(_instance == nullptr) {
    _instance = new GameManager();
  }
  return _instance;
}

void GameManager::initGame(GameObject *snake, GameMap *m) {
  this->snake = snake;
  map = m;
  dot = new Dot();
}

bool GameManager::collision() {
  Snake *s = (Snake*)snake;

  if(s->collision(dot)) {
    s->addSingleCell();
    ((Dot *) dot)->setRandomPos();
  }

  return (s->isCollidedWithCell())
    || (s->getX() <= 0 || s->getX() >= map->getWidth() - 1)
    || (s->getY() <= 0 || s->getY() >= map->getHeight() - 1);
}

void GameManager::update() {
  if(running) {
    snake->update();
    setRunning(!collision());
  } else if(!running && _getch() == ENTER) {
    reset();
    setRunning(true);
  }
}

void GameManager::draw() {
  map->draw();
  snake->draw();
  dot->draw();

  if(!running) {
    Snake *s = (Snake *) snake;

    const wchar_t *text1 = L"GAME OVER";
    wchar_t text3[30];
    swprintf_s(text3, L"SCORE: %d", s->getCells()->getSize() - s->getInitialCellSize());
    const wchar_t *text2 = L"PRESS < ENTER > TO RESTART";

    ScreenPrint(map->getWidth() / 2 - ((int) wcslen(text1) / 4), map->getHeight() / 2 - 1, text1);
    ScreenPrint(map->getWidth() / 2 - ((int) wcslen(text3) / 4), map->getHeight() / 2, text3);
    ScreenPrint(map->getWidth() / 2 - ((int) wcslen(text2) / 4), map->getHeight() / 2 + 1, text2);
  }
}

void GameManager::reset() {
  delete dot;
  dot = new Dot();
  ((Snake *) snake)->reset();
}