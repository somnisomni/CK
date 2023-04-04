#include <iostream>
using namespace std;

int main() {
  int x;
  cout << "정수 입력: ";
  cin >> x;

  if(x != 99) {
    cout << "Good, ";
    x++;
  }

  cout << "x = " << x << endl;

  return 0;
}
