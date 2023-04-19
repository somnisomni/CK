#include <iostream>
using namespace std;

int square(int n);
float square(float n);

int main() {
  cout << "정수 2의 제곱: " << square(2) << endl;
  cout << "정수 8의 제곱: " << square(8) << endl;
  cout << "실수 2.4의 제곱: " << square(2.4f) << endl;
  cout << "실수 6.7의 제곱: " << square(6.7f) << endl;

  return 0;
}

int square(int n) {
  return n * n;
}

float square(float n) {
  return n * n;
}
