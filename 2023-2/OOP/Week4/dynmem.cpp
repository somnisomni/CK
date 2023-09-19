#include <iostream>
using namespace std;

class Point {
  private:
    int x;
    int y;
  public:
    Point(int x, int y): x(x), y(y) { }
    int getX() { return x; }
    int getY() { return y; }
    void setX(int x) { this->x = x; }
    void setY(int y) { this->y = y; }
    void print() { cout << "(" << x << ", " << y << ")" << endl; }
};

int main() {
  Point *p = new Point(3, 10);
  p->print();

  delete p;
  return 0;
}
