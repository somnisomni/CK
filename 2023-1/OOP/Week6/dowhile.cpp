#include <iostream>
using namespace std;

int main() {
  int x = 0, sum = 0;

  // solution #1
  do {
    sum += x;
    x += 2;
  } while(x <= 100);

  // solution #2
  // do {
  //   if(x % 2 == 0) {
  //     sum += x;
  //   }
  //   x++;
  // } while(x <= 100);

  cout << sum << endl;

  return 0;
}
