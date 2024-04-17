#include <iostream>
#include "inventory.h"
using namespace std;

int main() {
  Inventory inventory(5);

  inventory.append(Item(1, 10));
  inventory.append(Item(2, 20));
  inventory.append(Item(3, 30));
  inventory.append(Item(4, 40));
  inventory.append(Item(5, 50));

  for(int i = 0; i < 5; i++) {
    Item item = inventory.get(i);
    cout << "Item " << item.getId() << ": " << item.getCount() << endl;
  }
  cout << endl;

  inventory.replaceAt(2, Item(6, 60));
  inventory.removeAt(3);

  for(int i = 0; i < 4; i++) {
    Item item = inventory.get(i);
    cout << "Item " << item.getId() << ": " << item.getCount() << endl;
  }

  return 0;
}
