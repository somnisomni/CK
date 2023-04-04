#include <iostream>
using namespace std;

int main() {
  char c;
  cout << "문자 입력: ";
  cin >> c;

  if(c >= 'A' && c <= 'Z') {
    cout << "대문자입니다." << endl;
  }

  return 0;
}
