#include <iostream>
#include <cmath>
using namespace std;

struct Point {
  int x, y;
};

struct Line {
  struct Point start, end;
};

int main() {
  Point pStart = { 10, 20 };
  Point pEnd = { 30, 40 };
  Line line = { pStart, pEnd };

  cout << "Line start: (" << line.start.x << ", " << line.start.y << ")" << endl;
  cout << "Line end: (" << line.end.x << ", " << line.end.y << ")" << endl;
  cout << "Line length: " << sqrt(pow(line.end.x - line.start.x, 2) + pow(line.end.y - line.start.y, 2)) << endl;

  return 0;
}
