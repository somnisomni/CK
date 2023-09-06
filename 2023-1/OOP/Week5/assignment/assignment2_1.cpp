#include <iostream>
using namespace std;

int main() {
  short var = 0, before = 0;

  while(true) {
    before = var;
    var += 1;
    cout << var << endl;

    // 방법 1: 직전 값과 현재 값 비교, 직전 값이 더 크다면(= 비정상적인 상황) 오버플로로 인식
    if(before > var) {
      cout << "OVERFLOW!" << endl;
      break;
    }
  }

  return 0;
}
