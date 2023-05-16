#include <iostream>
using namespace std;

int main() {
  double num = 3.14;
  double *ptr = &num;
  double **dptr = &ptr;
  double *ptr2;

  cout << ptr << " " << *dptr << endl;
  cout << num << " " << **dptr << endl;
  ptr2 = *dptr;
  *ptr = 19.3;
  cout << num << " " << **dptr << endl;
  return 0;
}
