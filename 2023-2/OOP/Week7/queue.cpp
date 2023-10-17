#include <iostream>
using namespace std;

class BaseArray {
  private:
    int capacity;
    int *mem;
  protected:
    BaseArray(int cap = 100): capacity(cap) {
      mem = new int[cap];
    }
    ~BaseArray() { delete [] mem; }
    void put(const int index, const int val) { mem[index] = val; }
    const int get(const int index) const { return mem[index]; }
    const int getCapacity() const { return capacity; }
};

class MyQueue: protected BaseArray {
  private:
    int startOffset = 0;
    int endOffset = 0;
  public:
    MyQueue(int cap = 100): BaseArray(cap) { }
    void inqueue(const int val) {
      put(endOffset++, val);
    }
    const int dequeue() {
      return get(startOffset++);
    }
    const int capacity() const { return getCapacity(); }
    const int length() const { return endOffset - startOffset; }
};

int main() {
  MyQueue mq(100);
  int n;
  cout << "큐에 다섯 개의 정수를 입력하세요: ";
  for(int i = 0; i < 5; i++) {
    cin >> n;
    mq.inqueue(n);
  }
  cout << "큐의 용량: " << mq.capacity() << endl;
  cout << "현재 큐의 크기: " << mq.length() << endl;
  while(mq.length() != 0) {
    cout << mq.dequeue() << " ";
  }
  cout << endl;

  return 0;
}