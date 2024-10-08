#include <iostream>
#include <thread>
#include "miner.h"
using namespace std;

int main() {
  Miner miner("Kowalski");

  for(int i = 0; i < 20; i++) {
    miner.update();
    this_thread::sleep_for(800ms);
  }

  cout << endl << "Game update complete" << endl;
  cin.get();

  return 0;
}
