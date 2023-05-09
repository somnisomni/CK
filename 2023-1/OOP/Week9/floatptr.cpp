#include <iostream>
using namespace std;

int main() {
  float fnum[10] = { 2.4f, 3.5f, 64.53f, 72.15f, 55.55f, 10.05f, 8839.259f, 4.99f, 1.2345f, 9876.5432f };
  float *p_fnum = fnum;
  int size = sizeof(fnum) / sizeof(float);

  cout << "fnum[0] = " << *p_fnum << endl;
  cout << "fnum[" << size << "] = " << *(p_fnum + (size - 1)) << endl;

  return 0;
}
