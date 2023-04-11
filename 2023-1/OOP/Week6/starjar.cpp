#include <iostream>
using namespace std;

#define COUNT 11

int main() {
  int dir = 1;

  for(int i = 0; i >= 0 && i < COUNT; i += dir) {
    for(int k = 0; k <= (COUNT / 2) - i; k++) {
      cout << " ";
    }

    for(int j = 0; j < ((i + 1) * 2) - 1; j++) {
      cout << "*";
    }

    if(i == COUNT / 2) {
      dir = -1;
    }

    cout << endl;
  }

  return 0;
}
