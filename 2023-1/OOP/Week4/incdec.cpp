#include <iostream>
using namespace std;

int main() {
  int a = 0;
  int b = 0;

  b = a++;
  cout << "a = " << a << endl;
  cout << "b = " << b << endl << endl;

  a = 0; b = 0;
  b = ++a;
  cout << "a = " << a << endl;
  cout << "b = " << b << endl;
  cout << endl << endl;

  return 0;
}
