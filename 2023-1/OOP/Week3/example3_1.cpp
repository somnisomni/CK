#include <iostream>
using namespace std;

int main() {
  char input, nextChar;

  cout << "문자를 입력해주세요: ";
  cin >> input;

  nextChar = (char) (input + 1);
  cout << input << "의 다음 문자는 " << nextChar << "입니다." << endl;
  return 0;
}
