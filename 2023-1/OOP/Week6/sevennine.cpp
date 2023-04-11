#include <iostream>
using namespace std;

int main() {
  for(int i = 1; i <= 100; i++) {
    if(i % 7 == 0 || i % 9 == 0) {
      cout << i << " ";
    }
  }
  cout << endl;

  return 0;
}
