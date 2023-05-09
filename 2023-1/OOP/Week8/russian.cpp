#include <iostream>
#include <stdlib.h>
#include <time.h>
using namespace std;

#define PLAYERS 5
#define SLOTS 6

int main() {
  srand((unsigned) time(NULL));

  for(int i = 1; i <= PLAYERS; i++) {
    cout << "Player " << i << ", press Enter to roll... ";
    cin.get();

    bool hasBullet = ((rand() % SLOTS) == 0);
    cout << "Rolled... press Enter to pull trigger... ";
    cin.get();

    if(hasBullet) {
      cout << "Slot has the bullet! Player " << i << " dead..." << endl << endl;
      break;
    } else {
      cout << "No bullet! Player " << i << " survived";

      if(i < PLAYERS) {
        cout << ", hand over to next player..." << endl << endl;
      } else {
        cout << "." << endl << endl;
      }
    }
  }

  cout << endl << "GAME OVER." << endl;

  return 0;
}
