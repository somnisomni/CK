#include <iostream>
using namespace std;

template<typename T>
void getArraySize(T valArray) {
  cout << sizeof valArray / sizeof valArray[0] << endl;
}

template<typename T>
void getArraySizeExt(T& refArray) {
  cout << sizeof refArray / sizeof refArray[0] << endl;
}

int main() {
  int arr[] = { 1, 2, 3, 4, 5 };

  getArraySize(arr);
  getArraySizeExt(arr);
}
