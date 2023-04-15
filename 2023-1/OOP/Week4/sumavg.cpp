#include <iostream>
using namespace std;

int main() {
  int korean, english, math;
  int sum;
  float avg;

  cout.precision(4);

  cout << "국어 성적을 입력하세요: ";
  cin >> korean;
  cout << "영어 성적을 입력하세요: ";
  cin >> english;
  cout << "수학 성적을 입력하세요: ";
  cin >> math;

  sum = korean + english + math;
  avg = sum / 3.0f;

  cout << "합계 : " << sum << endl;
  cout << "평균 : " << avg << endl;
}
