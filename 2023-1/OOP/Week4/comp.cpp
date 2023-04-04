#include <iostream>
using namespace std;

int main() {
  int x;
  cout << "하나의 정수를 입력하세요. : ";
  cin >> x;

  if(x >= 5 && x < 10) {
    cout << "5보다 크거나 같고 10 미만" << endl;
  } else {
    cout << "그 외의 정수" << endl;
  }

  return 0;
}
