#pragma once
#include "./shape.h"

class Circle: public Shape {
  private:
    double radius;
  public:
    Circle(int c, float r): Shape(c), radius(r) { }
    ~Circle() { }

    double calcArea() override;
    void draw() override;
};

double Circle::calcArea() {
  return 3.14f * radius * radius;
}

void Circle::draw() {
  cout << "Circle" << endl;
  cout << "Color: " << getColor() << endl;
  cout << "Radius: " << radius << endl;
  cout << "Area: " << calcArea() << endl;
}
