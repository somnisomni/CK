#include <iostream>
using namespace std;

class Point {
  private:
    int x = 0;
    int y = 0;
  public:
    Point(int x, int y): x(x), y(y) { };
    void setX(int _x) { x = _x; }
    void setY(int _y) { y = _y; }
    int getX() const { return x; }
    int getY() const { return y; }
};

class Rectangle {
  private:
    const Point *leftTop;
    const Point *rightBottom;
  public:
    Rectangle(Point *_lt, Point *_rb): leftTop(_lt), rightBottom(_rb) { };
    Rectangle(const Point *_lt, const Point *_rb): leftTop(_lt), rightBottom(_rb) { };
    int calculateArea() const;
    void showInfo() const;
};

int Rectangle::calculateArea() const {
  return (rightBottom->getX() - leftTop->getX()) * (rightBottom->getY() - leftTop->getY());
}

void Rectangle::showInfo() const {
  cout << " * 좌상단 좌표: (" << leftTop->getX() << ", " << leftTop->getY() << ")" << endl;
  cout << " * 우하단 좌표: (" << rightBottom->getX() << ", " << rightBottom->getY() << ")" << endl;
  cout << " * 넓이: " << calculateArea() << endl;
}

int main() {
  const Point *leftTop = new Point(10, 10);
  const Point *rightBottom = new Point(100, 50);
  Rectangle *rect = new Rectangle(leftTop, rightBottom);

  rect->showInfo();

  return 0;
}
