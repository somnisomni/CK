#include <iostream>
using namespace std;

#define LENGTH 5

int main() {
  int x = 0, y = 0;

  while(y < LENGTH) {
    x = 0;
    while(x < LENGTH) {
      if(x >= (LENGTH - y - 1)) {
        cout << "*";
      } else {
        cout << " ";
      }
      x++;
    }
    cout << endl;
    y++;
  }

  return 0;
}
