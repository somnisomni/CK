#pragma once
#include <string>
#include "util.h"
using namespace std;

class GameObject {
  private:
    int x, y;
    wchar_t *img;
    string tag;
  protected:
    void setTag(string tag) { this->tag = tag; }
  public:
    GameObject(): x(0), y(0), img((wchar_t *) L" ") { }
    GameObject(int x, int y, const wchar_t *img, string tag = ""): x(x), y(y), img((wchar_t*)img), tag(tag) { }
    ~GameObject() { }

    int getX() const { return x; }
    int getY() const { return y; }
    wchar_t *getImg() const { return img; }
    string getTag() const { return tag; }

    void setXY(const int x, const int y) { this->x = x; this->y = y; }
    void setImg(const wchar_t *img) { this->img = (wchar_t *) img; }

    virtual bool collision(GameObject *other, string targetTag = "") {
      if(this->x == other->getX() && this->y == other->getY() && (targetTag == "" || other->getTag() == targetTag)) {
        return true;
      }
      return false;
    }

    virtual void update() { };

    virtual void draw() {
      ScreenPrint(x, y, img);
    }
};
