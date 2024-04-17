#pragma once
#include "item.h"

class Inventory {
  private:
    Item* items;
    int size;
    int capacity;

  public:
    Inventory(int capacity): items(new Item[capacity]), size(0), capacity(capacity) { }
    ~Inventory() { delete[] items; }

    void replaceAt(int index, Item item) {
      if(index >= 0 && index < size) {
        items[index] = item;
      } else {
        throw "Inventory: Index out of bounds";
      }
    }

    void append(Item item) {
      if(size < capacity) {
        items[size++] = item;
      } else {
        throw "Inventory: Full";
      }
    }

    void removeAt(int index) {
      if(index >= 0 && index < size) {
        for(int i = index; i < size - 1; i++) {
          items[i] = items[i + 1];
        }

        size--;
      } else {
        throw "Inventory: Index out of bounds";
      }
    }

    Item get(int index) const {
      return items[index];
    }
};
