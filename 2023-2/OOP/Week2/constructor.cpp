#include <iostream>
using namespace std;

class Point {
  private:
    int x, y;
  public:
    Point();
    ~Point();
    void show();
};

Point::Point() {
  cout << "Constructor call" << endl;
}

Point::~Point() {
  cout << "Destructor call" << endl;
}

void Point::show() {
  cout << "show() function call" << endl;
}

int main() {
  cout << "main() procedure start" << endl;

  Point p;
  p.show();

  return 0;
}
