#include <iostream>
using namespace std;

class Point {
  private:
    int x;
    int y;
  public:
    Point(int x, int y): x(x), y(y) { }
    void setXY(int x, int y) { this->x = x; this->y = y; }
    void setX(int x) { this->x = x; }
    void setY(int y) { this->y = y; }
    int getX() const { return x; }
    int getY() const { return y; }
};

int main() {
  Point *p1 = new Point(10, 10);
  Point *p2 = new Point(20, 20);
  Point *p3 = new Point(30, 30);
  Point *points = new Point[3] { *p1, *p2, *p3 };

  for(int i = 0; i < 3; i++) {
    cout << "(" << points[i].getX() << ", " << points[i].getY() << ")" << endl;
  }

  delete p1, p2, p3;
  delete [] points;
  return 0;
}
