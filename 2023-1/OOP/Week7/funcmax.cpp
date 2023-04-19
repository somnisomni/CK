#include <iostream>
using namespace std;

int nummax(int x, int y);

int main() {
  int x = 0, y = 0;
  cout << "두 정수 입력: ";
  cin >> x >> y;

  cout << "최대값: " << nummax(x, y) << endl;

  return 0;
}

int nummax(int x, int y) {
  if(x >= y) return x;
  else return y;
}
