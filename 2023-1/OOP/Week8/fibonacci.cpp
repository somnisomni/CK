#include <iostream>
using namespace std;

int fibonacci(int n) {
  if(n > 2) return fibonacci(n - 1) + fibonacci(n - 2);
  else return 1;
}

int main() {
  int n = 0;
  cout << "n = ";
  cin >> n;

  for(int i = 1; i <= n; i++) {
    cout << fibonacci(i) << " ";
  }
  cout << endl;

  return 0;
}
