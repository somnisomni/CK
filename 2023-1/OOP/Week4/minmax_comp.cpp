#include <iostream>
using namespace std;

int main() {
  int x, y;
  cout << "첫 번째 수 입력 : ";
  cin >> x;
  cout << "두 번째 수 입력 : ";
  cin >> y;

  if(x >= y) {
    cout << "큰 수 : " << x << endl;
    cout << "작은 수 : " << y << endl;
  } else {
    cout << "큰 수 : " << y << endl;
    cout << "작은 수 : " << x << endl;
  }

  return 0;
}
