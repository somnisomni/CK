#include <iostream>
using namespace std;

void addOne(int &num);
void changeSign(int &num);

int main() {
  int num = 0, t1 = 0, t2 = 0;
  cout << "정수 입력: ";
  cin >> num;
  t1 = t2 = num;

  addOne(t1);
  changeSign(t2);

  cout << endl;
  cout << "1 증가: " << t1 << endl;
  cout << "부호 변경: " << t2 << endl;

  return 0;
}

void addOne(int &num) {
  num += 1;
}

void changeSign(int &num) {
  num *= -1;
}
