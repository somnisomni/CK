#include <iostream>
#include <climits>
using namespace std;

int main() {
  int arr[5] = { 0, };
  int size = sizeof(arr) / sizeof(int);

  int max = 0, min = INT_MAX, sum = 0;

  for(int i = 0; i < size; i++) {
    cout << "정수 입력 (" << i + 1 << "/" << size << "): ";
    cin >> arr[i];

    // 별도 for 루프 필요 없이
    // if(max < arr[i]) max = arr[i];
    // if(min > arr[i]) min = arr[i];
    // sum += arr[i];
  }

  max = min = arr[0];
  for(int i = 0; i < size; i++) {
    if(max < arr[i]) max = arr[i];
    if(min > arr[i]) min = arr[i];
    sum += arr[i];
  }

  cout << "최대값: " << max << endl;
  cout << "최소값: " << min << endl;
  cout << "합: " << sum << endl;

  return 0;
}
