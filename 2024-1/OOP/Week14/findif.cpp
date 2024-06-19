#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

bool checkNumber(int number) {
  return (number > 3);
}

int main() {
  vector<int> numVector;
  numVector.push_back(9);
  numVector.push_back(5);
  numVector.push_back(3);

  auto beginIterator = cbegin(numVector);
  auto endIterator = cend(numVector);
  auto findNumber = 3;

  if(auto finditerator = find(beginIterator, endIterator, findNumber); finditerator == endIterator) {
    cout << "not founded number" << endl;
  } else {
    cout << "found nunmber : " << *finditerator << endl;
  }

  auto findIterator = find_if(beginIterator, endIterator, checkNumber);
  if(findIterator == endIterator) {
    cout << "not founded number" << endl;
  } else {
    cout << "found number : " << *findIterator << endl;
  }
}
