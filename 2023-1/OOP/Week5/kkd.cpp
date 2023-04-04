#include <iostream>
using namespace std;

int main() {
  int input = 0, i = 1;

  cout << "구구단 단수를 입력하세요: ";
  cin >> input;

  while(i <= 9) {
    cout << input << " * " <<       i  << " = " << input *       i  << "\t";
    cout << input << " * " << (10 - i) << " = " << input * (10 - i) << endl;
    i++;
  }

  return 0;
}
