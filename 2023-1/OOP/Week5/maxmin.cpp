#include <iostream>
using namespace std;

int main() {
  int a, b, c;
  int max, min;
  cout << "정수 세 개 입력: ";
  cin >> a >> b >> c;

  max = a >= b ? (c >= a ? c : a) : (c >= b ? c : b);
  min = a < b ? (c < a ? c : a) : (c < b ? c : b);

  // if(a >= b) {
  //   max = a;
  //   min = b;

  //   if(c >= a) {
  //     max = c;
  //   }

  //   if(c < b) {
  //     min = c;
  //   }
  // } else {  // a < b
  //   max = b;
  //   min = a;

  //   if(c >= b) {
  //     max = c;
  //   }

  //   if(c < a) {
  //     min = c;
  //   }
  // }

  cout << "최대값: " << max << endl;
  cout << "최소값: " << min << endl;

  return 0;
}
