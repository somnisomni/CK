#include <iostream>
using namespace std;

int main() {
  double d = 123.456;

  cout << d << endl;
  cout.setf(ios::fixed, ios::floatfield);
  cout.precision(2);
  cout << "money = " << d << endl;
  return 0;
}
