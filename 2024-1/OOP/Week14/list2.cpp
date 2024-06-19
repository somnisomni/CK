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

bool confirmFunc(const string str) {
  cout << "str size: " << str.size() << endl;
  if(str.size() > 5) return true;
  return false;
}

bool sortFunc(const string str1, const string str2) {
  return str1.size() < str2.size();
}

int main() {
  list<string> data;
  data.push_back("A0");
  data.push_back("A0");
  data.push_front("B11");
  data.push_front("C222");
  data.push_back("D3333");
  data.push_back("E44444");
  data.push_back("F555555");
  data.push_front("F555555");
  data.push_front("G6666666");
  printList(data);

  data.unique();
  printList(data);

  data.sort(sortFunc);
  printList(data);

  data.reverse();
  printList(data);

  data.remove_if(confirmFunc);
  printList(data);

  return 0;
}
