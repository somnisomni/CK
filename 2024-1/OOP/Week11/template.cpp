#include <iostream>
using namespace std;

template<typename T>
T minFunc(T v1, T v2) {
  return v1 < v2 ? v1 : v2;
}

int main() {
  cout << "min(1, 2): " << minFunc(1, 2) << endl;
  cout << "min(2.5, 3.5): " << minFunc(2.5, 3.5) << endl;
  cout << "min('a', 'b'): " << minFunc('a', 'b') << endl;
  return 0;
}
