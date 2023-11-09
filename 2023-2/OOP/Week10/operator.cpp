#include <iostream>
using namespace std;

class Point {
  private:
    int x, y;
  public:
    Point(int x = 0, int y = 0): x(x), y(y) { }

    int getX() const { return x; }
    int getY() const { return y; }

    void show() const {
      cout << "(" << x << ", " << y << ") ";
    }

    Point operator+(const Point& p) const {
      return Point(x + p.x, y + p.y);
    }
    Point& operator+=(const Point& p) {
      x += p.x;
      y += p.y;
      return *this;
    }
    friend Point operator-(const Point& p1, const Point& p2);
    friend bool operator==(const Point& p1, const Point& p2);
    friend bool operator!=(const Point& p1, const Point& p2);
};

Point operator-(const Point& p1, const Point& p2) {
  return Point(p1.getX() - p2.getX(), p1.getY() - p2.getY());
}

bool operator==(const Point& p1, const Point& p2) {
  return (p1.getX() == p2.getX()) && (p1.getY() == p2.getY());
}

bool operator!=(const Point& p1, const Point& p2) {
  return !(p1 == p2);
}

int main() {
  cout << endl;

  Point p1(10, 20), p2(50, 10), p3(-40, -90);

  Point p4 = p1 + p2;
  Point p5 = p4 + p3;
  Point p6 = p5 - p1;

  cout << "p4 = p1(10, 20) + p2(50, 10)   = "; p4.show(); cout << endl << endl;
  cout << "p5 = p4         + p3(-40, -90) = "; p5.show(); cout << endl << endl;
  cout << "p6 = p5         - p1(10, 20)   = "; p6.show(); cout << endl << endl;

  Point p7(50, 50);
  p7 += p2;
  cout << "p7(50, 50) += p2(50, 10)       = "; p7.show(); cout << endl << endl;

  Point p8(40, 40), p9(40, 40);
  cout << "p8(40, 40) == p9(40, 40)       = " << ((p8 == p9) ? "true" : "false") << endl << endl;
  cout << "p8(40, 40) == p1(10, 20)       = " << ((p8 == p1) ? "true" : "false") << endl << endl;
  cout << "p8(40, 40) != p2(50, 10)       = " << ((p8 != p2) ? "true" : "false") << endl << endl;
  cout << "p8(40, 40) != p9(40, 40)       = " << ((p8 != p9) ? "true" : "false") << endl << endl;

  return 0;
}
