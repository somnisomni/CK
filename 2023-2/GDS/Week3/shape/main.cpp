#include <iostream>
#include "./shape.h"
#include "./triangle.h"
#include "./circle.h"
using namespace std;

int main() {
  Shape *poly;

  Circle circle(0, 64);
  poly = &circle;
  poly->rotate(30);
  poly->move(50, 300);
  poly->calcArea();
  poly->draw();

  cout << endl;

  Triangle tri(255, 10, 20);
  poly = &tri;
  poly->rotate(45);
  poly->move(100, 200);
  poly->calcArea();
  poly->draw();

  cout << endl;

  return 0;
}
