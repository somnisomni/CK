#include <iostream>
using namespace std;

template<typename T>
T maxFunc(T v1, T v2) {
  T result;

  if(v1 > v2) {
    cout << "첫 번째 수가 큽니다." << endl;
    result = v1;
  } else if(v1 < v2) {
    cout << "두 번째 수가 큽니다." << endl;
    result = v2;
  } else {
    cout << "두 수가 같습니다." << endl;
    result = v1;
  }

  return result;
}

int main() {
  maxFunc(1, 2);
  maxFunc(3.4, 2.5);
  maxFunc('z', 'B');
  maxFunc(2147483647, 2147483647);
  
  return 0;
}
