#include <iostream>
using namespace std;

template<typename T>
void printmin(T& val1, T& val2) {
  T temp = val1;

  if(val1 < val2) {
      cout << "val1 " << val1 << " < val2 " << val2 << endl;
  } else {
      cout << "val1 " << val1 << " >= val2 " << val2 << endl;
  }

  temp = val1;

  cout << "temp: " << temp << endl;
}

int main() {
  int val1 = 15;
  int& rval1 = val1;
  const int cval1 = val1;
  const int& crval1 = val1;
  int val2 = 25;
  int& rval2 = val2;
  const int cval2 = val2;
  const int& crval2 = val2;

  printmin(val1, val2);
  printmin(rval1, rval2);
  printmin(cval1, cval2);   // <- compile error
  printmin(crval1, crval2); // <- compile error
}
