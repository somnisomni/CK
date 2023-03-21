#include <iostream>
using namespace std;

int main() {
  int divInt = 7 / 4;
  float divFloat = 7 / 4;
  float divFloat2 = 7.0f / 4.0f;

  cout << "정수 나눗셈: " << divInt << endl;
  cout << "정수 나눗셈 (float 변수에 저장): " << divFloat << endl;
  cout << "실수 나눗셈: " << divFloat2 << endl;
}
