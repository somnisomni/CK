#include <iostream>
using namespace std;

int main() {
  int update = 6;
  int *p_update;

  p_update = &update;
  cout << "값: update = " << update;
  cout << ", p_update = " << *p_update << endl;

  cout << "주소: update = " << &update;
  cout << ", p_update = " << p_update << endl;

  *p_update = *p_update + 1;
  cout << "변경된 update = " << update << endl;

  return 0;
}
