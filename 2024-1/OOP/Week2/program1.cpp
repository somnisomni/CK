#include <iostream>
using namespace std;

int main() {
  int w, h;
  cout << "Enter buffer width: ";
  cin >> w;
  cout << "Enter buffer height: ";
  cin >> h;

  for(int y = 0; y < h; y++) {
    for(int x = 0; x < w; x++) {
      cout << static_cast<char>(65 + (y % 26));
    }
    cout << endl;
  }

  while(true) {
    int input;
    cout << "Enter print line (1 ~ height / 0 to exit): ";
    cin >> input;

    if(input == 0) break;
    else {
      if(input < 0 || input > h) {
        cout << "Not in range" << endl;
        continue;
      }

      for(int x = 0; x < w; x++) {
        cout << static_cast<char>(65 + ((input - 1) % 26));
      }
      cout << endl;
    }
  }

  return 0;
}
