#include <iostream>
using namespace std;

class Point {
  private:
    int x, y;
  public:
    Point(int x = 0, int y = 0): x(x), y(y) { }

    friend ostream& operator<<(ostream& os, const Point& p) {
      os << "(" << p.x << ", " << p.y << ")";
      return os;
    }
};

template <class T>
class CArrayPoint {
  private:
    T* arr;
    int len;
  public:
    CArrayPoint(int len) {
      this->len = len;
      arr = new T[len];
    }
    ~CArrayPoint() { delete [] arr; }

    T& operator[](int i) const { return arr[i]; }

    int getLenght() const { return len; }
};

int main() {
  CArrayPoint<int> iarr(5);
  for(int i = 0; i < 5; i++) iarr[i] = i + 1;
  for(int i = 0; i < 5; i++) cout << iarr[i] << " ";
  cout << endl;

  CArrayPoint<Point> oarr(3);
  oarr[0] = Point(3, 4);
  oarr[1] = Point(2, 8);
  oarr[2] = Point(7, 5);
  for(int i = 0; i < oarr.getLenght(); i++) cout << oarr[i] << " ";
  cout << endl;

  typedef Point* POINT_PTR;
  CArrayPoint<POINT_PTR> parr(3);
  parr[0] = new Point(1,2);
  parr[1] = new Point(3,4);
  parr[2] = new Point(5,6);
  for(int i = 0; i < parr.getLenght(); i++) cout << *(parr[i]) << " ";
  cout << endl;
  for(int i = 0; i < parr.getLenght(); i++) delete parr[i];

  return 0;
}
