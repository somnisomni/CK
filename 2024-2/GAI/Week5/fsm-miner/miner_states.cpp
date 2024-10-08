#include <iostream>
#include "state.h"
#include "miner.h"
#include "miner_states.h"
using namespace std;

StateBase<Miner>* MinerMiningState::getInstance() {
  static MinerMiningState instance;
  return &instance;
}

void MinerMiningState::enter(Miner* entity) {
  cout << entity->getName() << " is walking to the mine" << endl;
}

void MinerMiningState::execute(Miner* entity) {
  cout << entity->getName() << " has mined a gold nugget" << endl;
  entity->addGold(1);

  if(entity->isPocketFull()) {
    cout << entity->getName() << "'s pocket is full, need to deposit the golds" << endl;
    entity->changeState(MinerDepositGoldState::getInstance());
  } else if(entity->isThirst()) {
    cout << entity->getName() << " is thirsty, need to drink a vodka" << endl;
    entity->changeState(MinerQuenchThirstState::getInstance());
  }
}

void MinerMiningState::exit(Miner* entity) {
  cout << entity->getName() << " is leaving the mine" << endl;
}

/* === */

StateBase<Miner>* MinerDepositGoldState::getInstance() {
  static MinerDepositGoldState instance;
  return &instance;
}

void MinerDepositGoldState::enter(Miner* entity) {
  cout << entity->getName() << " is going to the bank" << endl;
}

void MinerDepositGoldState::execute(Miner* entity) {
  cout << entity->getName() << " has deposited gold nuggets all they have" << endl;
  entity->depositGold();

  if(entity->isRich()) {
    cout << entity->getName() << " is rich enough, will go to home and take a rest" << endl;
    entity->changeState(MinerRestState::getInstance());
  } else {
    cout << entity->getName() << " is not rich enough yet! Going back to the mine" << endl;
    entity->changeState(MinerMiningState::getInstance());
  }
}

void MinerDepositGoldState::exit(Miner* entity) {
  cout << entity->getName() << " is leaving the bank" << endl;
}

/* === */

StateBase<Miner>* MinerQuenchThirstState::getInstance() {
  static MinerQuenchThirstState instance;
  return &instance;
}

void MinerQuenchThirstState::enter(Miner* entity) {
      cout << entity->getName() << " is going to the saloon" << endl;
}

void MinerQuenchThirstState::execute(Miner* entity) {
  cout << entity->getName() << " has drunk a vodka" << endl;
  entity->resetThirst();

  cout << entity->getName() << " is going back to the mine" << endl;
  entity->changeState(MinerMiningState::getInstance());
}

void MinerQuenchThirstState::exit(Miner* entity) {
  cout << entity->getName() << " is leaving the saloon" << endl;
}

/* === */

StateBase<Miner>* MinerRestState::getInstance() {
  static MinerRestState instance;
  return &instance;
}

void MinerRestState::enter(Miner* entity) {
  cout << entity->getName() << " is going to the home" << endl;
}

void MinerRestState::execute(Miner* entity) {
  cout << entity->getName() << " is taking a rest, and sure, resting also costs some money" << endl;
  entity->useMoney(random() % 3 + 1);
  cout << entity->getName() << " has " << entity->getMoney() << " money left" << endl;

  if(entity->getMoney() <= 0) {
    cout << entity->getName() << " is out of money, need to go back to the mine" << endl;
    entity->changeState(MinerMiningState::getInstance());
  } else {
    cout << entity->getName() << " is still rich, will keep resting" << endl;
  }
}

void MinerRestState::exit(Miner* entity) {
  cout << entity->getName() << " is leaving the home" << endl;
}
