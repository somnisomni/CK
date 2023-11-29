#include "gamemap.h"

GameMap::GameMap(int w, int h): width(w), height(h) {
  map = new GameObject*[h];
  for(int i = 0; i < h; i++) map[i] = new GameObject[w];

  initMap();
}

GameMap::~GameMap() {
  for(int y = 0; y < height; y++) delete[] map[y];
  delete[] map;
}

void GameMap::initMap() {
  for(int y = 0; y < height; y++) {
    for(int x = 0; x < width; x++) {
      if(x == 0 || x == width - 1 || y == 0 || y == height - 1) {
        map[y][x] = Tile(x, y, L"¢Ã");
      } else {
        map[y][x] = Tile(x, y, L" ");
      }
    }
  }
}

void GameMap::draw() {
  for(int y = 0; y < height; y++) {
    for(int x = 0; x < width; x++) {
      map[y][x].draw();
    }
  }
}
