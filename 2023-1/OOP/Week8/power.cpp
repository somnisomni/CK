#include <iostream>
using namespace std;

long long int power_of_two(int n) {
  if(n == 1) return 2;
  else return 2 * power_of_two(n - 1);
}

int main() {
  int n = 0;
  cout << "n = ";
  cin >> n;

  cout << power_of_two(n) << endl;

  return 0;
}
