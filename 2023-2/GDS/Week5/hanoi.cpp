#include <iostream>
using namespace std;

void hanoiTower(int n, char from, char to, char aux) {
  if(n == 1) {
    cout << "n = " << n << " Move from " << from << " to " << to << endl;
    return;
  }

  hanoiTower(n - 1, from, aux, to);
  cout << "n = " << n << " Move from " << from << " to " << to << endl;
  hanoiTower(n - 1, aux, to, from);
}

int main() {
  hanoiTower(5, 'A', 'B', 'C');
  return 0;
}
