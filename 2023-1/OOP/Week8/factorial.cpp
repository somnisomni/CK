/* 테스트 */

#include <iostream>
using namespace std;

long long int factorial(int n) {
  if(n == 0L) return 1L;
  else return n * factorial(n - 1);
}

int main() {
  int x = 0;
  cin >> x;
  cout << factorial(x) << endl;
}
