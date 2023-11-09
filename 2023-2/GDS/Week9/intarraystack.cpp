#include <iostream>
using namespace std;

class IntArrayStack {
  private:
    int *stack;
    int topIdx;
    int max;
  public:
    IntArrayStack(int max): max(max) {
      stack = new int[max];
      topIdx = 0;
    }
    ~IntArrayStack() {
      if(stack) delete [] stack;
    }

    void push(int item) { isFull() ? -1 : stack[topIdx++] = item; }
    void pop() { isEmpty() ? -1 : topIdx--; }
    int getTop() { return isEmpty() ? -1 : stack[topIdx - 1]; }
    bool isEmpty() { return topIdx == 0; }
    bool isFull() { return topIdx == max; }
};

int main() {
  IntArrayStack intStack(10);
  for(int i = 0; i < 5; i++) intStack.push(i * 10);

  cout << "Top: " << intStack.getTop() << endl;

  intStack.pop();
  cout << "Top: " << intStack.getTop() << endl;

  intStack.push(1000);
  cout << "Top: " << intStack.getTop() << endl;

  return 0;
}
