#include <iostream>
using namespace std;

int main() {
  for(int r = 1; r <= 9; r++) {
    for(int l = 2; l <= 9; l++) {
      cout << l << "*" << r << "=" << l * r << "\t";
    }
    cout << endl;
  }

  cout << endl << endl;

  for(int l = 2; l <= 9; l++) {
    for(int r = 1; r <= 9; r++) {
      cout << l << "*" << r << "=" << l * r << "\t";
    }
    cout << endl;
  }

  return 0;
}
