#include <iostream>
using namespace std;

int maxNumber(int *arr);

int main() {
  int array[10] = { 3, 5, 4, 9, 10, 2, 8, 14, 23, 11 };
  int max = maxNumber(array);

  cout << "Max: " << max << endl;

  return 0;
}

int maxNumber(int *arr) {
  int max = arr[0];

  for(int i = 1; i < 10; i++) {
    if(arr[i] > max) {
      max = arr[i];
    }
  }

  return max;
}
