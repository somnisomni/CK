#include <iostream>
#include <cmath>
using namespace std;

int main() {
  short var = 0;

  while(true) {
    var += 1;
    cout << var << endl;

    // 방법 2: sizeof 함수 이용, 변수의 가능한 최저값에 도달하면 오버플로로 인식
    //         unsigned 자료형이라면 pow, sizeof 함수를 쓸 필요 없이 0으로 대체하면 됨
    if(var <= -(pow(2, sizeof(var)))) {
      cout << "OVERFLOW!" << endl;
      break;
    }
  }

  return 0;
}
