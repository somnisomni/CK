#include <iostream>
using namespace std;

int main() {
  int arr[6] = { 0, };

  for(int i = 0; i < sizeof(arr) / sizeof(int); i++) {
    cout << "정수 입력: ";
    cin >> arr[i];
  }

  cout << endl;
  for(int i = 0; i < sizeof(arr) / sizeof(int); i++) {
    cout << arr[i] << "\t";
  }
  cout << endl;

  return 0;
}
