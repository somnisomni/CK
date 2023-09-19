#include <iostream>
#include <cstring>
using namespace std;

class Person {
  private:
    char *name;
    char *address;
    int age;
  public:
    Person() { };
    Person(const char *name, const char *address, int age);
    ~Person();
    void print();
};

Person::Person(const char *name, const char *address, int age) {
  int nameSize = strnlen(name, 30);
  int addrSize = strnlen(address, 100);

  this->name = new char[nameSize + 1];
  strncpy(this->name, name, nameSize);
  this->address = new char[addrSize + 1];
  strncpy(this->address, address, addrSize);
  this->age = age;
}

Person::~Person() {
  delete [] name;
  delete [] address;
}

void Person::print() {
  cout << endl;
  cout << "이름: " << name << endl;
  cout << "주소: " << address << endl;
  cout << "나이: " << age << endl;
  cout << endl;
}

int main() {
  Person *p = new Person((const char *) "홍길동", (const char *) "경기도 이천시", 23);
  p->print();

  delete p;
  return 0;
}
