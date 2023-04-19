#include <iostream>
using namespace std;

bool even(int num);

int main() {
  int input = 0;
  cout << "정수 입력: ";
  cin >> input;

  if(even(input)) {
    cout << "짝수입니다." << endl;
  } else {
    cout << "홀수입니다." << endl;
  }

  return 0;
}

bool even(int num) {
  return num % 2 == 0;
}
