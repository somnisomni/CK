#include <iostream>
using namespace std;

template <class T>
T sumArray(T arr[], int len) {
  T sum = 0;
  for(int i = 0; i < len; i++) {
    sum += arr[i];
  }

  return sum;
}

int main() {
  int arr1[] = { 10, 20, 30 };
  cout << sumArray<int>(arr1, sizeof(arr1) / sizeof(int)) << endl;
  double arr2[] = { 10.2, 20.3, 30.8 };
  cout << sumArray<double>(arr2, sizeof(arr2) / sizeof(double)) << endl;

  return 0;
}
