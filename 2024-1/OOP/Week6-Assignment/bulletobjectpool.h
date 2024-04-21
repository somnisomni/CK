#pragma once

#include "bullet.h"
#include <iostream>
using namespace std;

class BulletObjectPool {
  private:
    static const int slotSizePerRow = 5;
    static const int rowSizeLimit = 20;
    int allocatedRowCount;

    Bullet*** slots;
    Bullet** inUseSlots;

    int inUseSize = 0;

  public:
    BulletObjectPool(int initialRows = 4): allocatedRowCount(initialRows) {
      /* Allocate objects in Slots */
      slots = new Bullet**[rowSizeLimit];
      for(int i = 0; i < allocatedRowCount; i++) {
        slots[i] = new Bullet*[slotSizePerRow];

        for(int j = 0; j < slotSizePerRow; j++) {
          slots[i][j] = new Bullet();
          slots[i][j]->setId((i * slotSizePerRow) + j);
        }
      }

      /* Prepare space of In-Use Slots */
      inUseSlots = new Bullet*[rowSizeLimit * slotSizePerRow];
      for(int i = 0; i < rowSizeLimit * slotSizePerRow; i++) {
        inUseSlots[i] = nullptr;
      }
    }

    ~BulletObjectPool() {
      for(int i = 0; i < allocatedRowCount; i++) {
        for(int j = 0; j < slotSizePerRow; j++) {
          delete slots[i][j];
        }

        delete[] slots[i];
      }

      delete[] slots;
    }

    Bullet* pop() {
      /* Find available first object */
      int foundRowIndex = -1, foundSlotIndex = -1;
      for(int i = 0; i < allocatedRowCount; i++) {
        for(int j = 0; j < slotSizePerRow; j++) {
          if(slots[i][j] != nullptr) {
            foundRowIndex = i;
            foundSlotIndex = j;
            break;
          }
        }

        if(foundRowIndex != -1) {
          break;
        }
      }

      /* If no available object, create new row */
      if(foundRowIndex == -1 && allocatedRowCount < rowSizeLimit) {
        Bullet** newRow = new Bullet*[slotSizePerRow];
        for(int i = 0; i < slotSizePerRow; i++) {
          newRow[i] = new Bullet();
          newRow[i]->setId((allocatedRowCount * slotSizePerRow) + i);
        }

        slots[allocatedRowCount] = newRow;

        foundRowIndex = allocatedRowCount++;
        foundSlotIndex = 0;
      } else if(foundRowIndex == -1 && allocatedRowCount >= rowSizeLimit) {
        throw "Row size limit reached. Cannot create more objects.";
      }

      /* Get first available object pointer */
      Bullet* bullet = slots[foundRowIndex][foundSlotIndex];

      /* Move object to In-Use Slots */
      inUseSlots[inUseSize++] = bullet;
      slots[foundRowIndex][foundSlotIndex] = nullptr;

      return bullet;
    }

    void push(Bullet* obj) {
      /* Find object in In-Use Slots */
      int foundInUseIndex = -1;
      for(int i = 0; i < inUseSize; i++) {
        if(inUseSlots[i] == obj) {
          foundInUseIndex = i;
          break;
        }
      }

      if(foundInUseIndex == -1) {
        throw "Object not found in Loaded Slots.";
      }

      /* Find empty slot in Slots */
      int foundEmptySlotRowIndex = -1, foundEmptySlotIndex = -1;
      for(int i = 0; i < allocatedRowCount; i++) {
        for(int j = 0; j < slotSizePerRow; j++) {
          if(slots[i][j] == nullptr) {
            foundEmptySlotRowIndex = i;
            foundEmptySlotIndex = j;
            break;
          }
        }

        if(foundEmptySlotRowIndex != -1) {
          break;
        }
      }

      /* Move found in-use object to Slots */
      slots[foundEmptySlotRowIndex][foundEmptySlotIndex] = inUseSlots[foundInUseIndex];

      /* Pull last object in In-Use Slots */
      inUseSlots[foundInUseIndex] = inUseSlots[--inUseSize];
    }

    void pushAll() {
      while(inUseSize > 0) {
        push(inUseSlots[inUseSize - 1]);
      }
    }

    void printPool() const {
      cout << "<< Available Bullets >>" << endl;
      for(int i = 0; i < allocatedRowCount; i++) {
        for(int j = 0; j < slotSizePerRow; j++) {
          if(slots[i][j] != nullptr) {
            cout << slots[i][j]->getId() << " ";
          } else {
            cout << "null ";
          }
        }
        cout << endl;
      }
      cout << endl;

      cout << "<< Loaded Bullets >>" << endl;
      for(int i = 0; i < inUseSize; i++) {
        cout << inUseSlots[i]->getId() << " ";
      }
      cout << endl << endl;
    }
};
