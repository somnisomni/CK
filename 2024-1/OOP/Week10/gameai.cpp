#include <iostream>
using namespace std;

class GameAI {
  public:
    virtual void takeTurn() { }
    virtual void collectResources() { }
    virtual void buildStructures() = 0;
    virtual void buildUnits() = 0;
    virtual void attack() { }
    virtual void sendScout() = 0;
    virtual void sendWarrior() = 0;
};

class OrcAI: public GameAI {
  public:
    virtual void buildStructures() override {
      cout << "OrcAI buildStructures()" << endl;
    }

    virtual void buildUnits() override {
      cout << "OrcAI buildUnits()" << endl;
    }

    virtual void sendScout() override {
      cout << "OrcAI sendScout()" << endl;
    }

    virtual void sendWarrior() override {
      cout << "OrcAI sendWarrior()" << endl;
    }
};

class HumanAI: public GameAI {
  public:
    virtual void collectResources() override {
      cout << "HumanAI collectResources()" << endl;
    }

    virtual void buildStructures() override {
      cout << "HumanAI buildStructures()" << endl;
    }

    virtual void buildUnits() override {
      cout << "HumanAI buildUnits()" << endl;
    }

    virtual void attack() override {
      cout << "HumanAI attack()" << endl;
    }

    virtual void sendScout() override {
      cout << "HumanAI sendScout()" << endl;
    }

    virtual void sendWarrior() override {
      cout << "HumanAI sendWarrior()" << endl;
    }
};

int main() {
  GameAI *orc = new OrcAI();
  orc->takeTurn();
  orc->collectResources();
  orc->buildStructures();
  orc->buildUnits();
  orc->attack();
  orc->sendScout();
  orc->sendWarrior();
  delete orc;

  GameAI *human = new HumanAI();
  human->takeTurn();
  human->collectResources();
  human->buildStructures();
  human->buildUnits();
  human->attack();
  human->sendScout();
  human->sendWarrior();
  delete human;

  return 0;
}
