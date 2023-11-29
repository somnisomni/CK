#pragma once
#include "gameobject.h"

struct Node {
  GameObject *obj;
  Node *next;

  Node(GameObject *obj): obj(obj), next(nullptr) {}
};

class GameObjectList {
  private:
    Node *head;
    Node *tail;
    int count;
  public:
    GameObjectList(): head(nullptr), tail(nullptr), count(0) { }
    ~GameObjectList() {
      Node *delNode = head;
      Node *nextNode = head;
      while(delNode) {
        nextNode = nextNode->next;
        delete delNode;
        delNode = nextNode;
      }
      head = nullptr;
      tail = nullptr;
    }

    void insert(int pos, GameObject *obj) {
      if(pos < 0 || pos > count) return;

      Node *curNode = head;
      Node *inNode = new Node(obj);

      if(pos == 0) {
        inNode->next = head;
        head = inNode;
        if(count == 0) {
          tail = inNode;
        }
      } else {
        for(int cur = 0; cur < pos - 1; cur++) {
          curNode = curNode->next;
        }
        inNode->next = curNode->next;
        curNode->next = inNode;
        if(pos == count) {
          tail = inNode;
        }
        count++;
      }
    }                            
    void append(GameObject *obj) {
      Node *newNode = new Node(obj);
      
      if(tail != nullptr) {
        tail->next = newNode;
      }
      tail = newNode;

      if(head == nullptr) {
        head = newNode;
      }

      count++;
    }
    void remove(int pos) {
      if(head == nullptr || pos < 0 || pos > count - 1) return;

      Node *curNode = head;
      Node *delNode = nullptr;

      if(pos == 0) {
        delNode = head;
        head = head->next;
      } else {
        for(int i = 0; i < pos - 1; i++) {
          curNode = curNode->next;
        }
        delNode = curNode->next;

        if(pos == count - 1) {
          tail = curNode;
        }

        curNode->next = delNode->next;
      }

      delete delNode;
      count--;
    }

    GameObject *getObject(int pos) {
      if(head == nullptr || pos < 0 || pos > count - 1) return nullptr;

      Node *curNode = head;
      for(int i = 0; i < pos; i++) curNode = curNode->next;
      return curNode->obj;
    }
    int getPos(GameObject *obj) {
      int curPos = 0;
      int curX = obj->getX();
      int curY = obj->getY();

      Node *curNode = head;
      while(curNode) {
        if(curNode->obj->getX() == curX &&
           curNode->obj->getY() == curY) {
          return curPos;
        }
        curPos++;
        curNode = curNode->next;
      }

      return -1;
    }
    int getSize() const { return count; }

    void update() {
      Node *curNode = head;
      while(curNode != nullptr) {
        curNode->obj->update();
        curNode = curNode->next;
      }
    }
    void draw() {
      Node *curNode = head;
      while(curNode != nullptr) {
        curNode->obj->draw();
        curNode = curNode->next;
      }
    }
};