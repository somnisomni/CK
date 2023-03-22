#include <iostream>
using namespace std;

int main() {
  float a = 1.0f / 3.0f;
  float sum = 0.0f;

  for(int i = 0; i < 30000; i++) {
    sum += a;
  }

  cout.setf(ios::fixed);
  cout.precision(13);
  cout << sum << endl;

  return 0;
}
