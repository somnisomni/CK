#include <iostream>
using namespace std;

int main() {
  char b = 'b';
  cout << "소문자 b의 ASCII 코드값: " << (int)b << endl;

  int ascii = 90;
  cout << "ASCII 코드값 90에 해당하는 문자: " << (char)ascii << endl;

  char h = 'H';
  cout << "알파벳 'H' 다음 문자: " << (char) (h + 1) << endl;

  char p = 'p';
  cout << "알파벳 'p' 대문자 변환: " << (char) (p - 32) << endl;

  return 0;
}
