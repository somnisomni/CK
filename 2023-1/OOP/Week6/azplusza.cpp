#include <iostream>
using namespace std;

int main() {
  // 원시적인 접근
  for(int a = 0; a <= 9; a++) {
    for(int z = 0; z <= 9; z++) {
      if((a * 10 + z) + (z * 10 + a) == 99) {
        cout << "A = " << a << ", Z = " << z << endl;
      }
    }
  }

  cout << endl << endl;

  // AZ + ZA = 99라면 A + Z = 9
  for(int x = 0; x <= 9; x++) {
    cout << "A = " << x << ", Z = " << 9 - x << endl;
  }

  return 0;
}
