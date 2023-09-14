#pragma once
#include <iostream>
using namespace std;

class Shape {
  private:
    int color;
  public:
    Shape(int c): color(c) { }
    ~Shape() { }

    void rotate(float rad);
    void move(int x, int y);
    int getColor() { return color; }
    void fillColor(int c) { color = c; }

    virtual double calcArea() = 0;
    virtual void draw() = 0;
};

void Shape::rotate(float rad) {
  cout << "Rotate " << rad << "rad" << endl;
}

void Shape::move(int x, int y) {
  cout << "Move to (" << x << ", " << y << ")" << endl;
}
