#include <iostream>
using namespace std;

class DynamicArray {
  private:
    int *arr;
    int size;
  public:
    DynamicArray(int arrSize) {
      arr = new int[arrSize];
      size = arrSize;
    }
    DynamicArray(const DynamicArray &copy) {
      arr = new int[copy.size];
      for(int i = 0; i < copy.size; i++) {
        arr[i] = copy.arr[i];
      }
      size = copy.size;
    }
    ~DynamicArray() {
      delete [] arr;
      cout << "dynamic array destruction" << endl;
    }
    void showData() {
      for(int i = 0; i < size; i++) {
        cout << arr[i] << " ";
      }
      cout << endl;
    }
    bool setData(int index, int value) {
      if(index < 0 || index >= size) {
        return false;
      }

      arr[index] = value;
      return true;
    }
};

int main() {
  int size = 1;
  cout << "0보다 큰 정수 입력: ";
  cin >> size;
  DynamicArray da1(size);
  for(int i = 0; i < size; i++) {
    if(!da1.setData(i, i + 1)) {
      cout << "index 오류" << endl;
      return 0;
    }
  }
  da1.showData();

  DynamicArray da2 = da1;
  for(int i = 0; i < size; i++) {
    if(!da2.setData(i, i - 1)) {
      cout << "index 오류" << endl;
      return 0;
    }
  }
  da2.showData();

  return 0;
}
