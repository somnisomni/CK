#include <iostream>
using namespace std;

int main() {
  int donuts = 10000;
  double cups = 5000.2048;

  cout << "도나쯔: " << donuts;
  cout << ", 도나쯔의 주소: " << &donuts << endl;
  cout << "컵: " << cups << ", 컵의 주소: " << &cups << endl;

  return 0;
}
