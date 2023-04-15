#include <iostream>
using namespace std;

int main() {
  int input = 0;
  cout << "정수 입력: ";
  cin >> input;

  for(int x = 0; x < input; x++) {
    cout << "*";
  }
  cout << endl;

  return 0;
}
