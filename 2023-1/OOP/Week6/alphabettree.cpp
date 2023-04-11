#include <iostream>
using namespace std;

int main() {
  int count = 'Z' - 'A'; // chars count between A ~ Z

  for(int i = 0; i <= count; i++) { // y axis
    for(int k = 0; k <= count - i; k++) { // x axis left padding
      cout << " ";
    }

    for(int j = 0; j <= i; j++) { // x axis chars
      cout << (char) ('A' + j) << " ";
    }

    cout << endl;
  }

  return 0;
}
