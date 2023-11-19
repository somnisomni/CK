#pragma once
#include "gameobject.h"
#include "gameobjectlist.h"
#include "inputmanager.h"
#include <conio.h>

enum SnakeDirection {
  D_UP, D_DOWN, D_LEFT, D_RIGHT
};

class SnakeCell: public GameObject {
  protected:
    SnakeDirection facing;
  public:
    SnakeCell(int initPosX, int initPosY, const wchar_t *img = L"¡Ý", SnakeDirection facing = D_LEFT)
      : GameObject(initPosX, initPosY, img, "SNAKE_CELL"), facing(facing) { };
};

class Snake: public SnakeCell {
  private:
    GameObjectList* cell;

    int _initPosX, _initPosY, _initCellSize;
    bool _imgState = false;
  public:
    Snake(int initPosX, int initPosY, int initCellSize = 3)
      : SnakeCell(initPosX, initPosY, L"¢Ä"), _initPosX(initPosX), _initPosY(initPosY), _initCellSize(initCellSize) {
      setTag("SNAKE_HEAD");
      reset();
    }
    ~Snake() {
      delete cell;
    }

    GameObjectList* getCells() const { return cell; }
    
    void reset() {
      setXY(_initPosX, _initPosY);
      facing = D_LEFT;

      if(cell) delete cell;
      cell = new GameObjectList();
      for(int i = 1; i <= _initCellSize; i++) {
        cell->append(new SnakeCell(_initPosX + i, _initPosY));
      }
    }

    void draw() override {
      GameObject::draw();
      cell->draw();
    }

    void update() override {
      int curX = getX(), curY = getY();

      // SNAKE HEAD IMAGE
      _imgState = !_imgState;
      if(_imgState) setImg(L"¢Ä");
      else setImg(L"¢Å");

      // USER INPUT
      switch(InputManager::getInstance()->popLastInput()) {
        case UP:
          if(facing != D_DOWN) facing = D_UP;
          break;
        case DOWN:
          if(facing != D_UP) facing = D_DOWN;
          break;
        case LEFT:
          if(facing != D_RIGHT) facing = D_LEFT;
          break;
        case RIGHT:
          if(facing != D_LEFT) facing = D_RIGHT;
          break;
      }

      // PROCESS BY FACING
      switch(facing) {
        case D_UP:
          setXY(curX, curY - 1);
          break;
        case D_DOWN:
          setXY(curX, curY + 1);
          break;
        case D_LEFT:
          setXY(curX - 1, curY);
          break;
        case D_RIGHT:
          setXY(curX + 1, curY);
          break;
      }

      // CELL PROCESS
      int pos = 0;
      GameObject *obj;
      while((obj = cell->getObject(pos++)) != nullptr) {
        int nextX = obj->getX(), nextY = obj->getY();
        obj->setXY(curX, curY);
        curX = nextX; curY = nextY;
      }
    }

    int getInitialCellSize() const { return _initCellSize; }

    bool isCollidedWithCell() {
      int pos = 0;
      GameObject* obj;
      while((obj = cell->getObject(pos++)) != nullptr) {
        if(collision(obj)) return true;
      }
      return false;
    }
    
    void addSingleCell() {
      GameObject* lastCell = cell->getObject(cell->getSize() - 1);
      cell->append(new SnakeCell(lastCell->getX(), lastCell->getY()));
    }
};
