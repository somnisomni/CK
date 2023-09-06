#include <iostream>
using namespace std;

int main() {
  int n = 1, input = 0;
  cout << "양의 정수를 입력하세요: ";
  cin >> input;
  cout << endl;

  while(n <= input) {
    cout << 3 * n << endl;
    n++;
  }

  return 0;
}
