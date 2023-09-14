#pragma once
#include "./shape.h"

class Triangle: public Shape {
  private:
    float base;
    float height;
  public:
    Triangle(int c, float b, float h): Shape(c), base(b), height(h) { }
    ~Triangle() { }

    double calcArea() override;
    void draw() override;
};

double Triangle::calcArea() {
  return base * height / 2;
}

void Triangle::draw() {
  cout << "Triangle" << endl;
  cout << "Color: " << getColor() << endl;
  cout << "Base: " << base << endl;
  cout << "Height: " << height << endl;
  cout << "Area: " << calcArea() << endl;
}
