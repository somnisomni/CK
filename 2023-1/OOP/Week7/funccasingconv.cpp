#include <iostream>
using namespace std;

char caseconv(char target);

int main() {
  char input;
  cout << "알파벳 문자 입력: ";
  cin >> input;

  cout << caseconv(input) << endl;
  return 0;
}

char caseconv(char target) {
  return target ^ 32; // XOR 0b100000
}
