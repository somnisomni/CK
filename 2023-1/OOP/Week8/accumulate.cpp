#include <iostream>
using namespace std;

long long int accumulate(int n) {
  if(n == 1) return 1;
  else return n + accumulate(n - 1);
}

int main() {
  int n = 0;
  cout << "n = ";
  cin >> n;

  cout << accumulate(n) << endl;

  return 0;
}
