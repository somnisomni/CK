#pragma once
#include "gamemap.h"

class GameManager {
  private:
    static GameManager *_instance;
    GameObject *snake;
    GameObject *dot;
    GameMap *map;
    bool running;

    GameManager(): snake(nullptr), dot(nullptr), map(nullptr), running(true) { }
    ~GameManager() { delete _instance; }
  public:
    static GameManager* getInstance();

    void initGame(GameObject *snake, GameMap *m);

    GameObject *getSnake() const { return snake; }
    GameObject *getDot() const { return dot; }
    GameMap *getGameMap() const { return map; }

    bool collision();
    void update();
    void draw();
    void reset();

    void setRunning(bool r) { running = r; }
};
