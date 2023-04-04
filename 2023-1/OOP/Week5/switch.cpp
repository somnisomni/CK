#include <iostream>
using namespace std;

int main() {
  char select;

  cout << "다음 내용 중 하나를 선택하시오. (앞의 영어 문자를 입력하세요.)" << endl;
  cout << "  a) 카메라" << endl;
  cout << "  b) 피아니스트" << endl;
  cout << "  c) 나무" << endl;
  cout << "  d) 게임" << endl;
  cout << "입력 >>>>> ";
  cin >> select;

  switch(select) {
    case 'a':
      cout << "카메라를 선택했습니다." << endl;
      break;
    case 'b':
      cout << "피아니스트를 선택했습니다." << endl;
      break;
    case 'c':
      cout << "나무를 선택했습니다." << endl;
      break;
    case 'd':
      cout << "게임을 선택했습니다." << endl;
      break;
    default:
      cout << "잘못 선택했습니다." << endl;
      break;
  }

  return 0;
}
