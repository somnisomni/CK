#include <iostream>
using namespace std;

double divide(int a, int b) {
  if(b == 0) throw "Divide by zero";
  return (double)a / b;
}

int multiply(int a, int b) {
  if(a < 0) throw "left is negative";
  return a * b;
}

int main() {
  int a, b;
  cout << "두 수 입력: ";
  cin >> a >> b;

  try {
    cout << a << " / " << b << " = " << divide(a, b) << endl;
    cout << a << " * " << b << " = " << multiply(a, b) << endl;
  } catch(char *msg) {
    cout << "오류 발생: " << msg << endl;
  }

  return 0;
}
