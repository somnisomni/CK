#include <iostream>
#include "./linkedlist.h"
using namespace std;

IntLinkedList::IntLinkedList() {
  head = nullptr;
  count = 0;
}

IntLinkedList::~IntLinkedList() {
  Node *temp = head;

  while(temp != nullptr) {
    Node *next = temp->next;
    delete temp;
    temp = next;
  }
}

void IntLinkedList::insert(int pos, int item) {
  if(pos < 0 || pos > count) {
    cout << "Position out of index" << endl;
    return;
  }

  Node *newNode = new Node(item);

  if(pos == 0) {
    newNode->next = head;
    head = newNode;
  } else {
    Node *temp = head;
    for(int i = 0; i < pos - 1; i++) {
      temp = temp->next;
    }
    newNode->next = temp->next;
    temp->next = newNode;
  }

  count++;
}

void IntLinkedList::remove(int pos) {
  if(pos < 0 || pos >= count) {
    cout << "Position out of index" << endl;
    return;
  }

  Node *temp = head;

  if(pos == 0) {
    head = head->next;
    delete temp;
  } else {
    for(int i = 0; i < pos - 1; i++) {
      temp = temp->next;
    }

    Node *temp2 = temp->next;
    temp->next = temp->next->next;
    delete temp2;
  }

  count--;
}

int IntLinkedList::retrieve(int pos) const {
  if(pos < 0 || pos >= count) {
    cout << "Position out of index" << endl;
    return -1;
  }

  Node *temp = head;

  for(int i = 0; i < pos; i++) {
    temp = temp->next;
  }

  return temp->data;
}

int IntLinkedList::getLength() const {
  return count;
}

bool IntLinkedList::isEmpty() const {
  return count == 0;
}

void IntLinkedList::print() const {
  Node *temp = head;

  cout << "(list)";
  while(temp != nullptr) {
    cout << " -> [" << temp->data << "]";
    temp = temp->next;
  }
  cout << endl;
}

int main() {
  srand((unsigned) time(NULL));

  IntLinkedList list;

  for(int i = 0; i < 20; i++) {
    list.insert(i, rand() % 100);
  }
  list.print();

  cout << "list.getLength(): " << list.getLength() << endl;
  cout << "list.isEmpty(): " << list.isEmpty() << endl;

  for(int i = 0; i < 10; i++) {
    int idx = rand() % list.getLength();
    cout << "random retrieve (idx: " << idx << "): " << list.retrieve(idx) << endl;
  }

  cout << endl;

  for(int i = 0; i < 10; i++) {
    int idx = rand() % list.getLength();
    cout << "random remove (idx: " << idx << ")" << endl;
    list.remove(idx);
  }
  list.print();

  cout << endl;

  for(int i = 0; i < 5; i++) {
    int idx = rand() % list.getLength();
    int val = rand() % 100;
    cout << "random insert (idx: " << idx << ", val: " << val << ")" << endl;
    list.insert(idx, val);
  }
  list.print();

  return 0;
}
