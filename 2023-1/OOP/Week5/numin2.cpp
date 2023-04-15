#include <iostream>
using namespace std;

#define MAXCOUNT 5

int main() {
  int sum = 0, count = 1;

  while(count <= MAXCOUNT) {
    int input = 0;
    cout << "정수 입력 (" << count << "/" << MAXCOUNT << "): ";
    cin >> input;

    if(input > 0) {
      count++;
      sum += input;
    } else {
      cout << "잘못된 입력입니다. 다시 입력하세요." << endl;
    }
  }

  cout << "합계: " << sum << endl;

  return 0;
}
