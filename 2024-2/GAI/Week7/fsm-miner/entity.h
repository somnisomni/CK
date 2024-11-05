#pragma once
#include <string>
using namespace std;

class GameEntityBase {
  protected:
    string name;
  public:
    GameEntityBase(string name): name(name) { }
    virtual ~GameEntityBase() = default;

    virtual void update() = 0;

    string getName() const { return name; }
};
