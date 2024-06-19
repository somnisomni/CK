#include <iostream>
#include <string>
#include <map>
#include <utility>
using namespace std;

int main() {
  map<string, int> intMapData;
  intMapData.insert({ "USA", 1 });
  intMapData.insert({ "KOREA", 3 });

  pair<map<string, int>::iterator, bool> pairValue = intMapData.insert({ "SWEDEN", 5 });
  if(pairValue.second) {
    cout << pairValue.first->first << endl;
    cout << pairValue.first->second << endl;
  }

  auto pairAutoValue = intMapData.insert(make_pair("Spain", 4));
  if(pairAutoValue.second) {
    cout << pairAutoValue.first->first << endl;
    cout << pairAutoValue.first->second << endl;
  }
}
