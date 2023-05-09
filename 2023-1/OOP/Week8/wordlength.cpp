#include <iostream>
using namespace std;

int main() {
  char arr[100];
  int count = 0;
  cout << "영단어 입력 (100자 이내): ";
  cin >> arr;

  for(char c: arr) {
    if(!c) break;
    count += 1;
  }

  cout << "문자열 길이: " << count << endl;

  return 0;
}
