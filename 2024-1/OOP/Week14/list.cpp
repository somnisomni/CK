#include <iostream>
#include <list>
#include <string>
using namespace std;

void printList(list<string> data) {
  for(const auto value : data) {
    cout << value << " ";
  }
  cout << endl;
}

int main() {
  list<string> data;
  data.push_back("A0");
  data.push_front("B1");
  data.push_front("C2");
  data.push_back("D3");
  printList(data);

  data.pop_back();
  data.push_front("E4");
  data.pop_front();
  printList(data);

  data.insert(data.begin(), "F5");
  auto empRefData = data.emplace_back("G6");
  auto empData = data.emplace(data.end(), "H7");
  printList(data);

  return 0;
}
