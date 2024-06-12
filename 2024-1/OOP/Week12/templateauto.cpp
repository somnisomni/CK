#include <iostream>
using namespace std;

template<typename T1, typename T2>
auto minAuto(T1 val1, T2 val2) {
  return (val1 < val2) ? val1 : val2;
}

int main() {
  int i = 3;
  float f = 3.14;
  double d = 9.81;
  short s = 42;

  cout << "minAuto(i, f): " << minAuto(i, f) << endl;  // float
  cout << "minAuto(f, d): " << minAuto(f, d) << endl;  // float
  cout << "minAuto(d, s): " << minAuto(d, s) << endl;  // double
  cout << "minAuto(s, i): " << minAuto(s, i) << endl;  // int
}
