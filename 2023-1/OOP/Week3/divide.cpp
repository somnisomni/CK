#include <iostream>
using namespace std;

int main() {
  int num1, num2, div, rem;

  cout << "첫 번째 정수를 입력하세요: ";
  cin >> num1;
  cout << "두 번째 정수를 입력하세요: ";
  cin >> num2;

  div = num1 / num2;
  rem = num1 % num2;

  cout << "몫: " << div << ", 나머지: " << rem << endl;

  // === //
  cout << endl << endl;
  // === //

  int secondInput, min, sec;

  cout << "초 단위의 시간을 입력하세요: ";
  cin >> secondInput;
  min = secondInput / 60;
  sec = secondInput % 60;

  cout << secondInput << "초는 " << min << "분 " << sec << "초 입니다." << endl;

  return 0;
}
