#include <iostream>
using namespace std;

class Point {
  private:
    int x, y;
  public:
    Point(): x(0), y(0) { }
    Point(int x, int y): x(x), y(y) { }

    int getX() const { return x; }
    int getY() const { return y; }
    void showPosition() const {
      cout << "(" << x << ", " << y << ")" << endl;
    }

    Point operator*(const int &n) { return Point(x * n, y * n); }
    friend Point operator*(const int &l, const Point &r);
    bool operator==(const Point &other) { return (x == other.x && y == other.y); }
    bool operator!=(const Point &other) { return !(*this == other); }
    // Point& operator++() {
    //   x++;
    //   y++;
    //   return *this;
    // }
    // const Point operator++(int) {
    //   const Point copy(x, y);
    //   x++;
    //   y++;
    //   return copy;
    // }
    friend const Point& operator++(Point &p);
    friend const Point operator++(Point &p, int);
};

Point operator*(const int &l, const Point &r) {
  return Point(l * r.x, l * r.y);
}

const Point& operator++(Point &p) {
  p.x++;
  p.y++;
  return p;
}

const Point operator++(Point &p, int) {
  const Point copy(p.x, p.y);
  p.x++;
  p.y++;
  return copy;
}

int main() {
  Point p(1, 2);
  p.showPosition();

  Point q(3, 5);
  q = p * 3;
  q.showPosition();

  q = p * 3 * 2;
  q.showPosition();

  q = 3 * p;
  q.showPosition();

  q = 4 * p * 6;
  q.showPosition();

  Point b = q++;
  b.showPosition();
  q.showPosition();

  Point c = ++q;
  c.showPosition();
  q.showPosition();

  return 0;
}
