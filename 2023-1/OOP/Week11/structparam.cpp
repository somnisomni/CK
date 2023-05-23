#include <iostream>
using namespace std;

typedef struct Point {
  int x;
  int y;
} pos;

void swapPoint(pos &p1, pos &p2) {
  pos temp = p1;
  p1 = p2;
  p2 = temp;
}

int main() {
  pos s1 = {2, 4};
  pos s2 = {7, 9};

  cout << "s1 = {" << s1.x << ", " << s1.y << "}" << endl;
  cout << "s2 = {" << s2.x << ", " << s2.y << "}" << endl;

  swapPoint(s1, s2);

  cout << endl << "after swap" << endl;
  cout << "s1 = {" << s1.x << ", " << s1.y << "}" << endl;
  cout << "s2 = {" << s2.x << ", " << s2.y << "}" << endl;

  return 0;
}
