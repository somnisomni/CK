#include <iostream>
using namespace std;

int main() {
  int sum = 0, x = 0;

  while(x <= 100) {
    sum += x;
    x += 2;
  }

  cout << sum << endl;
}
