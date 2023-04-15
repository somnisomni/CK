#include <iostream>
using namespace std;

int main() {
  int x;
  cout << "정수 입력: ";
  cin >> x;

  if(x % 2 == 0) {
    cout << "짝수입니다." << endl;
    return 0;
  }

  cout << "홀수입니다." << endl;
  return 0;

  // else 안쓰기 ^ㅠ^
}
