#include <iostream>
using namespace std;

#define LENGTH 9

int main() {
  int x = 1, y = 1;

  while(y <= LENGTH) {
    x = 1;
    while(x <= LENGTH * 2) {
      int tmp = x;

      if(x <= LENGTH) {
        tmp = LENGTH - x + 1;
        if(tmp <= y - 1) {
          cout << tmp + 1;
        } else {
          cout << " ";
        }
      } else {
        tmp = x - LENGTH;
        if(tmp <= y) {
          cout << tmp;
        } else {
          cout << " ";
        }
      }

      x += 1;
    }

    y += 1;
    cout << endl;
  }
}
