#include <iostream>
using namespace std;

int main() {
  double ted = 3.5;
  double *p_ted = &ted;

  cout << "ted = " << *p_ted << endl;

  return 0;
}
