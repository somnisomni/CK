#include <iostream>
#include <string>
using namespace std;

class Cat {
  public:
    string name;
    string type;
    int age;
    void print();
};

void Cat::print() {
  cout << "이름: " << name << endl;
  cout << "종: " << type << endl;
  cout << "나이: " << age << endl;
}

int main() {
  Cat momo;
  momo.name = "모모";
  momo.type = "코리안 숏헤어";
  momo.age = 2;

  momo.print();

  return 0;
}
