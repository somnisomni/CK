#pragma once
#include "plane.h"
#include "gamemap.h"
#include "gameobjectlist.h"

class GameManager {
  private:
    static GameManager *_instance;
    GameObject *plane;
    GameMap *map;
    GameObjectList *bullets;
    GameManager() { }
    ~GameManager() { delete _instance; }
  public:
    static GameManager *getInstance() {
      if(_instance == nullptr) {
        _instance = new GameManager();
      }
      return _instance;
    }

    void initGame(GameObject *p, GameMap *m, GameObjectList *b);

    GameObject *getPlane() const { return plane; }
    GameMap *getGameMap() const { return map; }
    GameObjectList *getBullets() const { return bullets; }

    bool collision();
    void update();
    void draw();
};