#include <iostream>
using namespace std;

int main() {
  char c;
  cout << "알파벳 입력: ";
  cin >> c;

  // 비트 연산 ^ㅠ^
  cout << ((char) (c ^ 32)) << endl; // XOR 0b100000

  ///// if-else if 사용
  // if(c >= 'a' && c <= 'z') {
  //   cout << ((char) (c - 32)) << endl;
  // } else if(c >= 'A' && c <= 'Z') {
  //   cout << ((char) (c + 32)) << endl;
  // }

  return 0;
}
