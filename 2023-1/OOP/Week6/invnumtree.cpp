#include <iostream>
using namespace std;

int main() {
  for(int i = 9; i >= 1; i--) {
    for(int j = 0; j < i; j++) {
      cout << i;
    }
    cout << endl;
  }

  return 0;
}
