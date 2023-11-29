#include <iostream>
using namespace std;

class Point {
  private:
    int x, y;
  public:
    Point(int x = 0, int y = 0): x(x), y(y) {}

    friend ostream& operator<<(ostream &out, const Point &p);
};

ostream& operator<<(ostream& out, const Point& p) {
  out << "(" << p.x << ", " << p.y << ")";
  return out;
}

class PointArray {
  private:
    Point *arr;
    int size;
  public:
    PointArray(int len): size(len) {
      arr = new Point[size];
    }
    ~PointArray() {
      delete [] arr;
    }
    Point& operator[](int index) {
      if(index < 0 || index > size - 1) {
        cout << "Out of index" << endl;
        exit(1);
      }

      return arr[index];
    }

    int getSize() const { return size; }
};

int main() {
  PointArray arr(3);

  arr[0] = Point(3, 4);
  arr[1] = Point(2, 8);
  arr[2] = Point(7, 5);

  for(int i = 0; i < arr.getSize(); i++)
    cout << arr[i] << endl;

  // Out of Index
  cout << arr[5] << endl;

  return 0;
}
