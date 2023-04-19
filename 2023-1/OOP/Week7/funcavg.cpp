#include <iostream>
using namespace std;

float average(int x, int y);

int main() {
  int x = 0, y = 0;
  cout << "두 정수 입력: ";
  cin >> x >> y;

  cout << "평균: " << average(x, y) << endl;
  return 0;
}

float average(int x, int y) {
  return (x + y) / 2.0f;
}
