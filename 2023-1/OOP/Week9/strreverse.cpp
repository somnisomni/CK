#include <iostream>
#include <string>
#include <string.h>
using namespace std;

void reverseString(const char src[], char dst[]) {
  int size = sizeof((const char *) src) / sizeof(char);

  for(int i = size; i >= 0; i--) {
    dst[size - i] = src[i];
  }
}

// void reverseString2(char* src, char* dst) {
//   string srcStr = string(src);
//   string dstStr = "";

//   for(int i = srcStr.length(); i >= 0; i--) {
//     dstStr += srcStr[i];
//   }

//   strcpy(dst, dstStr.c_str());
// }

int main() {
  char src[] = "Game Over", dst[40] = { 0, };
  reverseString(src, dst);

  cout << "소스 문자열: " << src << endl;
  cout << "결과 문자열: " << dst << endl;

  cout << endl;


  // char input[101], inpDst[101] = { 0, }, inpDst2[101] = { 0, };
  // cout << "문자열 입력 (최대 100자): ";
  // cin >> input;

  // reverseString(input, inpDst);
  // reverseString2(input, inpDst2);

  // cout << "결과 문자열 1: " << inpDst << endl;
  // cout << "결과 문자열 2: " << inpDst2 << endl;

  return 0;
}
