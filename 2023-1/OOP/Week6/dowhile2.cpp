#include <iostream>
using namespace std;

int main() {
  int input, sum = 0;

  do {
    cout << "정수 입력: ";
    cin >> input;

    sum += input;
  } while(input != 0);

  cout << "결과: " << sum << endl;

  return 0;
}
