#include <iostream>
#include <bitset>
using namespace std;

int main() {
  int value = 37;

  cout << "10진수: " << value << endl;
  cout << "8진수: " << oct << value << endl;
  cout << "16진수: " << hex << value << endl;
  cout << "2진수: " << bitset<32>(value) << endl;

  return 0;
}
