#include <iostream>
#include <list>
using namespace std;

struct Item {
  int code;
  int money;
  Item(int c, int m): code(c), money(m) { }
};

int main() {
  list<Item> items;

  items.push_back(Item(100, 100));
  items.push_front(Item(200, 200));

  list<Item>::iterator it;
  it = items.begin();
  it++;
  items.insert(it, Item(50, 50));

  for(it = items.begin(); it != items.end(); it++)
    cout << it->code << ", " << it->money << endl;

  return 0;
}
