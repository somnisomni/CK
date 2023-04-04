#include <iostream>
using namespace std;

#define LENGTH 5

int main() {
  int x = 1, y = 1;

  while(y <= LENGTH) {
    x = 0;
    while(x < (y - 1)) {
      cout << "o ";
      x++;
    }
    cout << "*" << endl;
    y++;
  }

  return 0;
}
