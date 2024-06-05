#include <iostream>
using namespace std;

void printData(char* pData) {
  cout << pData << endl;
}

void printDetailData(const char* pData) {
  printData(const_cast<char*>(pData));
}

int main() {
  const char* pData = "Hello, World!";
  printDetailData(pData);
  return 0;
}
