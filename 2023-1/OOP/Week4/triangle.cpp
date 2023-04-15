#include <iostream>
using namespace std;

int main() {
  float bs, h;

  cout << "밑변 길이: ";
  cin >> bs;

  cout << "높이: ";
  cin >> h;

  cout << "면적 : " << bs * h * (1.0f / 2.0f) << endl;

  return 0;
}
