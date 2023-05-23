#include <iostream>
using namespace std;

struct Body {
  double height;
  double weight;
};

int main() {
  Body body;
  Body *ptr = &body;

  cout << "신장: ";
  cin >> (*ptr).height;
  cout << "몸무게: ";
  cin >> (*ptr).weight;

  (*ptr).height += 10;
  ptr->weight += 2.5;

  cout << endl;
  cout << "조작된 신장: " << (*ptr).height << endl;
  cout << "조작된 몸무게: " << ptr->weight << endl;

  return 0;
}
