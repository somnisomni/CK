#pragma once

template <class T>
struct Node {
  T data;
  Node* next;
  Node(T item): data(item), next(nullptr) { }
};

template <class T>
class PointerStack {
  private:
    Node<T> *top;
  public:
    PointerStack(): top(nullptr) { }
    ~PointerStack() { while(top) pop(); }

    void push(T item) {
      Node<T> *inNode = new Node<T>(item);
      inNode->next = top;
      top = inNode;
    }
    T pop() {
      if(isEmpty()) return T();
      
      Node<T> *outNode = top;
      T outData = outNode->data;
      top = top->next;
      delete outNode;
      return outData;
    }
    T getTop() { return isEmpty() ? T() : top->data; }
    bool isEmpty() { return top == nullptr; }
};
