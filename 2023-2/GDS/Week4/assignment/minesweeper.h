#pragma once
#include <iostream>
#include <cstdlib>
using namespace std;

enum TileType {
  EMPTY,
  MINE
};

class Tile {
  private:
    unsigned int x;
    unsigned int y;
    unsigned int num = 0;
    bool revealed = false;
    bool flagged = false;
    TileType type = EMPTY;
  protected:
    Tile(const unsigned int x, const unsigned int y, const TileType type): x(x), y(y), type(type) { };
  public:
    Tile(const unsigned int x, const unsigned int y): x(x), y(y) { };
    const unsigned int getX() const { return x; }
    const unsigned int getY() const { return y; }
    const unsigned int getNum() const { return num; }
    const bool isRevealed() const { return revealed; }
    const bool isFlagged() const { return flagged; }
    const TileType getType() const { return type; }
    void reveal() { revealed = true; }
    void flag() { flagged = true; }
    void increaseNum() { num++; }
    void decreaseNum() { num--; }
};

class Mine: public Tile {
  public:
    Mine(const unsigned int x, const unsigned int y): Tile(x, y, MINE) { };
};

class MapGenerator {
  public:
    static void initMap(Tile*** &mapTiles, const unsigned int w, const unsigned int h) {
      mapTiles = new Tile**[h];

      for(unsigned int y = 0; y < h; y++) {
        mapTiles[y] = new Tile*[w];

        for(unsigned int x = 0; x < w; x++) {
          mapTiles[y][x] = new Tile(x, y);
        }
      }
    }

    static void spreadMines(Tile*** &mapTiles, const unsigned int w, const unsigned int h, const unsigned int count) {
      for(unsigned int m = 0; m < count; m++) {
        unsigned int x = rand() % w;
        unsigned int y = rand() % h;

        if(mapTiles[y][x]->getType() == MINE) {
          m--;
          continue;
        }

        delete mapTiles[y][x];
        mapTiles[y][x] = new Mine(x, y);

        for(int ya = -1; ya <= 1; ya++) {
          for(int xa = -1; xa <= 1; xa++) {
            int xt = x + xa;
            int yt = y + ya;

            if(xt < 0 || xt >= w || yt < 0 || yt >= h) {
              continue;
            }

            mapTiles[yt][xt]->increaseNum();
          }
        }
      }
    }
};

class MinesweeperMap {
  private:
    unsigned int w;
    unsigned int h;
    unsigned int mineCount;
    Tile*** tiles;
    bool ready = false;
  public:
    MinesweeperMap(const unsigned int width, const unsigned int height, const unsigned int mines): w(width), h(height), mineCount(mines) {
      generateMap(width, height, mines);
    }

    ~MinesweeperMap() {
      freeAll();
    }

    void generateMap(const unsigned int width, const unsigned int height, const unsigned int mines) {
      freeAll();

      MapGenerator::initMap(tiles, width, height);
      MapGenerator::spreadMines(tiles, width, height, mines);

      ready = true;
    }

    void freeAll() {
      if(ready) {
        for(unsigned int y = 0; y < h; y++) {
          for(unsigned int x = 0; x < w; x++) {
            delete tiles[y][x];
          }
          delete [] tiles[y];
        }
        delete [] tiles;

        ready = false;
      }
    }

    const unsigned int getWidth() const { return w; }
    const unsigned int getHeight() const { return h; }
    const unsigned int getMineCount() const { return mineCount; }
    const Tile* getTile(const unsigned int x, const unsigned int y) const { return tiles[y][x]; }

    void reveal(const unsigned int x, const unsigned int y) const { tiles[y][x]->reveal(); }
    void flag(const unsigned int x, const unsigned int y) const { tiles[y][x]->flag(); }
    void print() const;
};

void MinesweeperMap::print() const {
  cout << " Width: " << w << endl;
  cout << " Height: " << h << endl;
  cout << " Mine Count: " << mineCount << endl << endl;

  cout << " ~*~*~* Map *~*~*~ " << endl;
  for(unsigned int y = 0; y < h; y++) {
    for(unsigned int x = 0; x < w; x++) {
      cout << " ";
      if(tiles[y][x]->getType() == MINE) {
        cout << "M";
      } else {
        cout << tiles[y][x]->getNum();
      }
    }
    cout << endl;
  }
}
