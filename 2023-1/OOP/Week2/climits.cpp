#include <iostream>
#include <climits>
using namespace std;

int main() {
  int n_int = INT_MAX;
  short n_short = SHRT_MAX;
  long n_long = LONG_MAX;

  cout << "int는 " << sizeof(int) << "바이트이다." << endl;
  cout << "short는 " << sizeof(short) << "바이트이다." << endl;
  cout << "long는 " << sizeof(long) << "바이트이다." << endl;

  cout << "int의 최대값 : " << n_int << endl;
  cout << "short의 최대값 : " << n_short << endl;
  cout << "long의 최대값 : " << n_long << endl;

  return 0;
}
