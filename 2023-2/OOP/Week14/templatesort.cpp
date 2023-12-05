#include <iostream>
#include <cstring>
using namespace std;

template <class T>
void sortArray(T arr[], int len) {
  T sorted[len];
  for(int i = 0; i < len; i++) {
    sorted[i] = arr[i];
  }

  for(int i = 0; i < len - 1; i++) {
    for(int j = i + 1; j < len; j++) {
      if(sorted[i] > sorted[j]) {
        T temp = sorted[i];
        sorted[i] = sorted[j];
        sorted[j] = temp;
      }
    }
  }

  for(int i = 0; i < len; i++) {
    cout << sorted[i] << " ";
  }
  cout << endl;
}

int main() {
  int var[] = { 3, 5, 1, 9, 4 };
  char str[] = "gasgdargc";
  cout << str << endl;
  sortArray(str, strlen(str));

  for(int i = 0; i < 5; i++) cout << var[i] << ", ";
  cout << endl;
  sortArray(var, sizeof(var) / sizeof(var[0]));

  return 0;
}
