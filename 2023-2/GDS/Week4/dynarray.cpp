#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

#define ARRAY_Y 3
#define ARRAY_X 5

int main() {
  srand((unsigned) time(NULL));

  // Dynamic 2D array
  int **arr = new int*[ARRAY_Y];
  for(int y = 0; y < ARRAY_Y; y++) {
    arr[y] = new int[ARRAY_X];
  }

  // Fill array with random numbers
  for(int y = 0; y < ARRAY_Y; y++) {
    for(int x = 0; x < ARRAY_X; x++) {
      arr[y][x] = rand() % 10000;
    }
  }

  // Print array
  for(int y = 0; y < ARRAY_Y; y++) {
    cout << "arr[" << y << "]: ";
    for(int x = 0; x < ARRAY_X; x++) {
      cout << arr[y][x] << " ";
    }
    cout << endl;
  }

  // Cleanup
  for(int y = 0; y < ARRAY_Y; y++) {
    delete [] arr[y];
  }

  return 0;
}
