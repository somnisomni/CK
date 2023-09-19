#include <iostream>
using namespace std;

#define PI 3.141562f

class Circle {
  private:
    unsigned int radius;
  public:
    Circle(unsigned int radius): radius(radius) { }
    int getRadius() { return radius; }
    void setRadius(int radius) { this->radius = radius; }
    double getArea() { return radius * radius * PI; }
    void print();
};

void Circle::print() {
  cout << endl;
  cout << "원의 반지름: " << radius << endl;
  cout << "원의 넓이  : " << getArea() << endl;
  cout << endl;
}

int main() {
  unsigned int radius;
  cout << "원의 반지름 입력: ";
  cin >> radius;

  Circle *c = new Circle(radius);
  c->print();

  delete c;
  return 0;
}
