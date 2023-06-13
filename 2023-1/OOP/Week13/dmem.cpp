#include <iostream>
using namespace std;

int main() {
  const int size = 10;
  int *num = new int[size];
  for(int i = 0; i < size; i++) {
    num[i] = i + 1;
  }

  // sum & avg
  int sum = 0;
  for(int i = 0; i < size; i++) {
    sum += num[i];
  }
  cout << "합계: " << sum << endl;
  cout << "평균: " << (float) sum / size << endl;

  delete [] num;

  return 0;
}
