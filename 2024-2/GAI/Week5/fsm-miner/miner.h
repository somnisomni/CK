#pragma once
#include <random>
#include "entity.h"
#include "state.h"
#include "miner_states.h"
using namespace std;

class Miner : public GameEntityBase {
  private:
    static const int MAX_THIRST = 5;
    static const int MAX_GOLD_CARRIED = 3;
    static const int MONEY_RICH = 10;

    StateBase<Miner>* currentState;
    int goldCarried = 0;
    int moneyInBank = 0;
    int thirst = 0;
  public:
    Miner(string name): GameEntityBase(name) {
      changeState(MinerRestState::getInstance());
    }
    ~Miner() { }

    void update() override {
      increaseThirst();
      currentState->execute(this);
    }

    void changeState(StateBase<Miner>* newState) {
      if(currentState != nullptr) {
        currentState->exit(this);
      }
      currentState = newState;
      currentState->enter(this);
    }

    void addGold(int gold) {
      goldCarried += gold;
    }
    bool isPocketFull() const {
      return goldCarried >= MAX_GOLD_CARRIED;
    }
    void depositGold() {
      moneyInBank += goldCarried;
      goldCarried = 0;
    }
    int getMoney() const {
      return moneyInBank;
    }
    void useMoney(int money) {
      moneyInBank -= money;

      if(moneyInBank < 0) {
        moneyInBank = 0;
      }
    }
    bool isRich() const {
      return moneyInBank >= MONEY_RICH;
    }
    void increaseThirst() {
      thirst++;
    }
    void resetThirst() {
      thirst = 0;
    }
    bool isThirst() const {
      return thirst >= MAX_THIRST;
    }
};
