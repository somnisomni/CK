#include <iostream>
#include <stack>
using namespace std;

int main() {
  stack<int> d;
  int num;
  cout << "input: ";
  cin >> num;

  while(num != 0) {
    d.push(num % 2);
    num /= 2;
  }
  while(!d.empty()) {
    cout << d.top();
    d.pop();
  }

  return 0;
}
