#include <iostream>
using namespace std;

int main() {
  int n;
  cout << "숫자 입력 (1 ~ 10): ";
  cin >> n;

  cout << "숫자 " << n << "은(는) ";
  if(n % 2 == 0 && n % 3 == 0) {
    cout << "2의 배수이자 3의 배수입니다." << endl;
  } else if(n % 2 == 0) {
    cout << "2의 배수입니다." << endl;
  } else if(n % 3 == 0) {
    cout << "3의 배수입니다." << endl;
  } else {
    cout << "2의 배수도 3의 배수도 아닙니다." << endl;
  }

  return 0;
}
