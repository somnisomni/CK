#include <iostream>
using namespace std;

int main() {
  char c;
  cout << "문자를 입력하세요: ";
  cin >> c;

  if(c >= 'a' && c <= 'z') { // islower(c)
    cout << "소문자";
  } else if(c >= 'A' && c <= 'Z') { // isupper(c)
    cout << "대문자";
  } else if(c >= '0' && c <= '9') { // isdigit(c)
    cout << "숫자";
  } else {
    cout << "기타 문자";
  }

  cout << "입니다." << endl;

  return 0;
}
