#include <iostream>
using namespace std;

class Item {
  private:
    string name;

  public:
    Item() { name = "Unnamed Item"; }
    Item(string name): name(name) { }

    string getName() const { return name; }
};

class Inventory {
  private:
    Item *items;
    int itemNum;

  public:
    Inventory(): itemNum(0), items(nullptr) { }
    Inventory(int itemNum): itemNum(itemNum) {
      items = new Item[itemNum];
    }
    Inventory(const Inventory &src): itemNum(src.itemNum) {
      cout << "Copy" << endl;

      items = new Item[src.itemNum];
      for(int i = 0; i < src.itemNum; i++) {
        items[i] = src.items[i];
      }
    }
    ~Inventory() {
      cout << "Destruct" << endl;
      delete[] items;
    }

    Inventory &operator=(const Inventory &rhs) {
      cout << "Assign" << endl;

      if(this == &rhs) return *this;
      if(items != nullptr) delete[] items;

      itemNum = rhs.itemNum;
      items = new Item[rhs.itemNum];
      for(int i = 0; i < rhs.itemNum; i++) {
        items[i] = rhs.items[i];
      }

      return *this;
    }

    void print() const {
      for(int i = 0; i < itemNum; i++) {
        cout << "Item #" << i + 1 << ": " << items[i].getName() << endl;
      }
      cout << endl;
    }
};

int main() {
  Inventory inventory(10);
  inventory.print();

  Inventory copy1(inventory);
  copy1.print();

  Inventory copy2;
  copy2 = inventory;
  copy2.print();

  return 0;
}
