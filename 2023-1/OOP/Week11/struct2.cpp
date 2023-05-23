#include <iostream>
using namespace std;

struct Point {
  int x;
  int y;
};

int main() {
  Point point;

  cout << "X좌표: ";
  cin >> point.x;
  cout << "Y좌표: ";
  cin >> point.y;

  cout << "P = (" << point.x << ", " << point.y << ")" << endl;

  return 0;
}
