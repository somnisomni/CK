#include <iostream>
using namespace std;

int main() {
  char input, lowerChar;

  cout << "대문자를 입력하세요: ";
  cin >> input;

  lowerChar = (char) input + 32;
  cout << input << "의 소문자는 " << lowerChar << "입니다." << endl;
  return 0;
}

// lowercase <-> uppercase: alphabet ^ 0b100000
