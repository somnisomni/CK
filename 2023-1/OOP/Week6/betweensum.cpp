#include <iostream>
using namespace std;

int main() {
  int x = 0, y = 0, sum = 0;

  cout << "정수 2개 입력: ";
  cin >> x >> y;

  for(; x <= y; x++) {
    sum += x;
  }

  cout << "합: " << sum << endl;

  return 0;
}
