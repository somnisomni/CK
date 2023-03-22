#include <iostream>
using namespace std;

int main() {
  unsigned char c;

  c = 255;
  c = c + 1;
  cout << (int)c << endl;

  c = 0;
  c = c - 1;
  cout << (int)c << endl;

  return 0;
}
