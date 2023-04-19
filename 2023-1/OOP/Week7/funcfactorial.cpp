#include <iostream>
using namespace std;

long long int factorial(int n);

int main() {
  int x = 0;
  cout << "n! 정수 입력: ";
  cin >> x;

  cout << factorial(x) << endl;
}

long long int factorial(int n) {
  long long int temp = 1L;

  for(int i = 1; i <= n; i++) {
    temp *= i;
  }

  return temp;
}
