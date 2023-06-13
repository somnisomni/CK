#include <iostream>
using namespace std;

int main() {
  char *name = new char[10];
  char *addr = new char[80];

  cout << "이름: ";
  cin >> name;
  cout << "주소: ";
  cin >> addr;

  cout << endl << endl;

  cout << "이름: " << name << endl;
  cout << "주소: " << addr << endl;

  delete [] name;
  delete [] addr;

  return 0;
}
