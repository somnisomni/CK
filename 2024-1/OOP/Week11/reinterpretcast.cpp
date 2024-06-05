#include <iostream>
using namespace std;

int main() {
  int iNumber = 100;
  float fNumber = 25.5f;

  cout << "iNumber: " << iNumber << endl;
  cout << "fNumber: " << fNumber << endl;

  int* pNumber = &iNumber;
  float* pfNumber = &fNumber;

  cout << "pNumber addr: " << pNumber << endl;
  cout << "pfNumber addr: " << pfNumber << endl;

  pNumber = reinterpret_cast<int*>(pfNumber);
  void* pVoidNumber = pNumber;
  pfNumber = reinterpret_cast<float*>(pVoidNumber);

  cout << "pVoidNumber addr: " << pVoidNumber << endl;
  cout << "pNumber addr: " << pNumber << endl;
  cout << "pNumber val: " << *pNumber << endl;
  cout << "pfNumber addr: " << pfNumber << endl;
  cout << "pfNumber val: " << *pfNumber << endl;

  return 0;
}
