#include <iostream>
using namespace std;

int main() {
  int twoD[3][4] = {
    { 1,  2,  3,  4 },
    { 5,  6,  7,  8 },
    { 9, 10, 11, 12 }
  };
  int oneD[3 * 4];

  cout << "2D array" << endl;
  for(int y = 0; y < 3; y++) {
    for(int x = 0; x < 4; x++) {
      cout << twoD[y][x] << " ";
      oneD[y * 4 + x] = twoD[y][x];
    }
    cout << endl;
  }
  cout << endl;

  cout << "1D array" << endl;
  for(int x = 0; x < 3 * 4; x++) {
    cout << oneD[x] << " ";
  }
  cout << endl;

  return 0;
}
