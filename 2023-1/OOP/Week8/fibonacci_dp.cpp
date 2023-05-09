/* Dynamic Programming으로 푸는 법 다시 떠올리기 */

#include <iostream>
using namespace std;

unsigned long long int dp[100] = { 0, };

unsigned long long int fibonacci(int n) {
  if(dp[n] <= 0) {
    dp[n] = fibonacci(n - 1) + fibonacci(n - 2);
  }

  return dp[n];
}

int main() {
  dp[1] = 1UL;
  dp[2] = 1UL;

  int n = 0;
  cout << "n = ";
  cin >> n;

  for(int i = 1; i <= n; i++) {
    cout << fibonacci(i) << " ";
  }
  cout << endl;

  return 0;
}
