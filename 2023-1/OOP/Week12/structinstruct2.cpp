#include <iostream>
#include <cmath>
using namespace std;

struct Point {
  int x, y;
};

struct Rectangle {
  Point bottomLeft, topRight;
};

inline int rectArea(const Rectangle &rect) {
  return abs(rect.topRight.x - rect.bottomLeft.x) * abs(rect.topRight.y - rect.bottomLeft.y);
}

int main() {
  Rectangle rect1 = { { 1, 1 }, { 4, 4 } };
  Rectangle rect2 = { { 0, 0 }, { 7, 5 } };

  cout << "Rect #1 area: " << rectArea(rect1) << endl;
  cout << "Rect #2 area: " << rectArea(rect2) << endl;

  return 0;
}
