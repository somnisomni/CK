#include <iostream>
#include <string>
#include <climits>
using namespace std;

void reverse(string str, int index = INT_MAX) {
  if(index == 0) {
    cout << str[index] << endl;
    return;
  }

  index = min(index, (int) str.length() - 1);
  cout << str[index];
  reverse(str, --index);
}

int main() {
  reverse("abcd");
  return 0;
}
