#include <iostream>
using namespace std;

class Array {
  private:
    int *arr;
    int size;
  public:
    Array(int len): size(len) {
      arr = new int[size];
    }
    ~Array() {
      delete [] arr;
    }
    int& operator[](int index) {
      return arr[index];
    }
};

int main() {
  Array obj(5);

  for(int i = 0; i < 5; i++)
    obj[i] = i;
  for(int j = 0; j < 5; j++)
    cout << obj[j] << endl;

  return 0;
}
