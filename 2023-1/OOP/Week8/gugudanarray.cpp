#include <iostream>
using namespace std;

int main() {
  int result[3][9] = { 0, };

  for(int dan = 2; dan <= 4; dan++) {
    for(int num = 1; num <= 9; num++) {
      result[dan - 2][num - 1] = dan * num;
    }
  }

  for(int y = 0; y < 3; y++) {
    cout << y + 2 << "단: ";
    for(int x = 0; x < 9; x++) {
      cout << "\t" << result[y][x];
    }
    cout << endl;
  }

  return 0;
}
