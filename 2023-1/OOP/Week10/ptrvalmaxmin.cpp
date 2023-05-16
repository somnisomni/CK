#include <iostream>
#include <time.h>
#include <stdlib.h>
using namespace std;

void MaxAndMin(int *arr, int size, int **maxPtr, int **minPtr);

int main() {
  srand((unsigned) time(NULL));

  const int size = 5;
  int arr[size] = { 0, };
  int *maxPtr = &arr[0], *minPtr = &arr[0];

  cout << "arr[" << size << "] = ";
  for(int i = 0; i < size; i++) {
    arr[i] = rand() % 100;
    cout << arr[i] << " ";
  }
  cout << endl << endl;

  MaxAndMin(arr, size, &maxPtr, &minPtr);
  cout << "max = " << *maxPtr << ", addr: " << maxPtr << endl;
  cout << "min = " << *minPtr << ", addr: " << minPtr << endl;
}

void MaxAndMin(int *arr, int size, int **maxPtr, int **minPtr) {
  for(int i = 0; i < size; i++) {
    if(**maxPtr < arr[i]) {
      *maxPtr = &arr[i];
    }
    if(**minPtr > arr[i]) {
      *minPtr = &arr[i];
    }
  }
}
