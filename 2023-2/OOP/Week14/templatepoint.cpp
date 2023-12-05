#include <iostream>
using namespace std;

template <class T>
class CPoint {
  private:
    T x, y;
  public:
    CPoint(T x = 0, T y = 0): x(x), y(y) { }

    CPoint<T> operator+(const CPoint<T>& p) const {
      return CPoint<T>(x + p.x, y + p.y);
    }
    friend ostream& operator<<(ostream& os, const CPoint<T>& p) {
      os << "(" << p.x << ", " << p.y << ")";
      return os;
    }

    void show() const {
      cout << "(" << x << ", " << y << ")" << endl;
    }
};

int main() {
  CPoint<int> a(1, 2);
  CPoint<int> b(3, 4);
  CPoint<int> c = a + b;
  cout << a << " + " << b << " = " << c << endl;

  CPoint<double> d(1.2, 3.4);
  CPoint<double> e(5.6, 7.8);
  CPoint<double> f = d + e;
  cout << d << " + " << e << " = " << f << endl;

  return 0;
}
