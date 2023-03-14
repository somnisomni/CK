#include <iostream>
#include <climits>
using namespace std;

int main() {
  short max = SHRT_MAX;
  unsigned short min = 0;

  cout << "max의 값은 " << max << "이고 min의 값은 " << min << "이다." << endl;

  max = max + 1;
  min = min - 1;
  cout << "max에 1을 더하면 " << max << "이 되고, ";
  cout << "min에 1을 빼면 " << min << "가 된다." << endl;

  return 0;
}
