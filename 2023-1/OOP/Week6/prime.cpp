#include <iostream>
using namespace std;

int main() {
  int input, primeCount = 0;
  cout << "정수 입력: ";
  cin >> input;

  for(int x = 2; x <= input; x++) {
    bool check = true;
    for(int y = 2; y <= x - 1; y++) {
      if(x % y == 0) {
        check = false;
        break;
      }
    }

    if(check) {
      cout << "소수: " << x << endl;
      primeCount += 1;
    }
  }

  cout << "소수 총 개수: " << primeCount << endl;

  return 0;
}
