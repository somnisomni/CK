#pragma once
#include "tile.h"

class GameMap {
  private:
    int width, height;
    GameObject **map;
  public:
    GameMap(int w = 60, int h = 30);
    ~GameMap();

    void initMap();

    int getWidth() const { return width; }
    int getHeight() const { return height; }
    GameObject getTile(int x, int y) const { return map[y][x]; }

    void setTile(int x, int y, GameObject obj) { map[y][x] = obj; }

    void draw();
};