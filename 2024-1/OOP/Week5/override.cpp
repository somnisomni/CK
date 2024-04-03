#include <iostream>
using namespace std;

class PlayerBase {
  private:
    int defensePoint;
  protected:
    int attackPoint;
  public:
    virtual void damage() {
      cout << "PlayerBase::damage()" << endl;
    }
    virtual void damageExt(int attack) {
      cout << "PlayerBase::damageExt(int) " << attack << endl;
    }
};

class PlayerDerived: public PlayerBase {
  public:
    virtual void damage() override {
      cout << "PlayerDerived::damage()" << endl;
    }
    virtual void damageExt(double attack) {
      cout << "PlayerDerived::damageExt(double) " << attack << endl;
    }
    virtual void calcExp() {
      cout << "PlayerDerived::calcExp()" << endl;
    }
};

int main() {
  PlayerBase *player = new PlayerDerived();
  player->damage();
  player->damageExt(10);

  delete player;
  return 0;
}
