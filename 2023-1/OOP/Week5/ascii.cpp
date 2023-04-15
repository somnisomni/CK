#include <iostream>
using namespace std;

int main() {
  while(true) {
    char input;

    cout << "문자 입력: ";
    cin >> input;

    if(('a' <= input && input <= 'z') || ('A' <= input && input <= 'Z')) {
      cout << "문자 '" << input << "'의 ASCII 코드: " << int(input) << endl;
    } else {
      cout << "종료" << endl;
      break;
    }
  }

  return 0;
}
