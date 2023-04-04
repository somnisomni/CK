#include <iostream>
using namespace std;

int main() {
  while(true) {
    int input;

    cout << "정수 입력: ";
    cin >> input;

    if(input != 0) {
      cout << input << "이(가) 입력되었습니다." << endl;
    } else {
      cout << "종료" << endl;
      break;
    }
  }

  return 0;
}
