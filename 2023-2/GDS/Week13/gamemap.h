#pragma once
#include "util.h"
#include "base.h"

class GameMap {
  private:
  TileType **map;
  int width;
  int height;
  public:
  GameMap(int width = 10, int height = 10): width(width), height(height) {
    map = new TileType*[height];
    for(int i = 0; i < height; i++) {
      map[i] = new TileType[width];
    }
    makeMap();
  }
  ~GameMap() {
    for(int i = 0; i < height; i++) {
      delete[] map[i];
    }
    delete[] map;
  }

  int getWidth() const { return width; }
  int getHeight() const { return height; }
  int getTile(int x, int y) const { return map[y][x]; }
  void setTile(int x, int y, TileType tile) { map[y][x] = tile; }

  void makeMap();
  void print();
};

void GameMap::makeMap() {
  srand((unsigned)time(NULL));

  for(int i = 0; i < height; i++) {
    for(int j = 0; j < width; j++) {
      if(i == 0 || i == height - 1 || j == 0 || j == width - 1) {
        map[i][j] = WALL;
      } else {
        map[i][j] = rand() % 2 ? OBJECT : BLANK;
      }
    }
  }

  map[1][1] = map[2][1] = map[3][1] = map[4][1] = map[5][1] = map[6][1] = map[7][1] = BLANK;
  map[7][2] = map[7][3] = map[7][4] = map[7][5] = map[7][6] = map[7][7] = BLANK;
}

void GameMap::print() {
  for(int y = 0; y < height; y++) {
    for(int x = 0; x < width; x++) {
      if(map[y][x] == PATH) SetColor(10);
      else SetColor(15);

      ScreenPrint(x, y, TILE_ICON[map[y][x]]);
    }
  }
}
