#pragma once

template <class T>
class ArrayStack {
  private:
    T *stack;
    int topIdx;
    int max;
  public:
    ArrayStack(int max): max(max) {
      stack = new T[max];
      topIdx = 0;
    }
    ~ArrayStack() {
      if(stack) delete [] stack;
    }

    void push(T item) { isFull() ? -1 : stack[topIdx++] = item; }
    void pop() { isEmpty() ? -1 : topIdx--; }
    T getTop() { return isEmpty() ? T() : stack[topIdx - 1]; }
    int getMax() const { return max; }
    bool isEmpty() { return topIdx == 0; }
    bool isFull() { return topIdx == max; }
};
