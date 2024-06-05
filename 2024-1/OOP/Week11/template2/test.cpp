#include <iostream>
#include "test.h"
using namespace std;

int minVal(int v1, int v2) {
  return v1 > v2 ? v2 : v1;
}

template<typename T>
T minVal(T v1, T v2) {
  return v1 > v2 ? v2 : v1;
}

int main() {
  cout << "minVal(10, 20): " << minVal(10, 20) << endl;
  cout << "minVal(10.125, 10.05): " << minVal(10.125, 10.05) << endl;

  return 0;
}
