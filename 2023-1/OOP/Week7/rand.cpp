#include <iostream>
#include <stdlib.h>
#include <time.h>
using namespace std;

inline int randCoin() { return rand() % 2; }

int main() {
  srand((unsigned) time(NULL));
  cout << randCoin() << endl;
  return 0;
}
