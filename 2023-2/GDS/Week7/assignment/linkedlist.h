#pragma once

struct Node {
  int data;
  Node *next;
  Node(int item): data(item), next(nullptr) { }
};

class IntLinkedList {
  private:
    Node *head;
    int count;
  public:
    IntLinkedList();
    ~IntLinkedList();
    void insert(int pos, int item);
    void remove(int pos);
    int retrieve(int pos) const;
    int getLength() const;
    bool isEmpty() const;
    void print() const;
};
