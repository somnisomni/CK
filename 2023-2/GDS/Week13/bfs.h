#pragma once
#include "gamemap.h"
#include "base.h"
#include "pointerqueue.h"

class BFS {
  private:
    PointerQueue<Point> queue;
    GameMap *map;
    int startX, startY, targetX, targetY;

    Point **parents;
    VisitType **visitInfo;

    Direction move[4];
  public:
    BFS(int sx, int sy, int tx, int ty, GameMap *map):
      startX(sx), startY(sy), targetX(tx), targetY(ty), map(map) {
      int width = map->getWidth();
      int height = map->getHeight();
      
      parents = new Point*[height];
      visitInfo = new VisitType*[height];

      for(int y = 0; y < height; y++) {
        parents[y] = new Point[width];
        visitInfo[y] = new VisitType[width];

        for(int x = 0; x < width; x++) {
          parents[y][x] = { -1, -1 };
          visitInfo[y][x] = NOT_VISITED;
        }
      }
    }
    ~BFS() {
      for(int y = 0; y < map->getHeight(); y++) {
        delete[] parents[y];
        delete[] visitInfo[y];
      }

      delete[] parents;
      delete[] visitInfo;
    }

    void initDirection();
    GameMap *getMap() const { return map; }

    bool findPath();
    void print();
};

void BFS::initDirection() {
  move[0] = { -1, 0 }; // LEFT
  move[1] = {  1, 0 }; // RIGHT
  move[2] = { 0, -1 }; // TOP
  move[3] = { 0,  1 }; // BOTTOM
}

bool BFS::findPath() {
  Point pos = { startX, startY };
  queue.push(pos);
  visitInfo[startY][startX] = VISITED;
  parents[startY][startX] = pos;

  bool found = false;
  Point front;
  Point nextPos;

  while(!queue.empty()) {
    front = queue.front();
    queue.pop();

    if(front.x == targetX && front.y == targetY) {
      found = true;
      break;
    }

    for(int dir = 0; dir < 4; dir++) {
      nextPos.x = front.x + move[dir].horizontal;
      nextPos.y = front.y + move[dir].vertical;

      if(visitInfo[nextPos.y][nextPos.x] == NOT_VISITED &&
        map->getTile(nextPos.x, nextPos.y) == BLANK) {
        visitInfo[nextPos.y][nextPos.x] = VISITED;
        parents[nextPos.y][nextPos.x] = front;
        queue.push(nextPos);
      }
    }
  }

  if(found) {
    Point p = { targetX, targetY };
    map->setTile(p.x, p.y, PATH);

    do {
      p = parents[p.y][p.x];
      map->setTile(p.x, p.y, PATH);
    } while(p.x != startX || p.y != startY);
  }

  return found;
}

void BFS::print() {

}