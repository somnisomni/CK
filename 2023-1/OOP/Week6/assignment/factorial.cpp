#include <iostream>
using namespace std;

int main() {
  int input;
  long long int result = 1;
  cout << "정수 입력: ";
  cin >> input;

  for(int i = 1; i <= input; i++) {
    result *= i;
  }

  cout << input << "! 결과값: " << result << endl;

  return 0;
}
