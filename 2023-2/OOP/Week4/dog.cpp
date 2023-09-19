#include <iostream>
#include <cstring>
using namespace std;

class Dog {
  private:
    char *name;
    unsigned short age;
    unsigned short weight;
  public :
    Dog(const char *name, unsigned short age, unsigned short weight);
    ~Dog();
    void print();
};

Dog::Dog(const char *name, unsigned short age, unsigned short weight) {
  int nameLen = strnlen(name, 100);

  this->name = new char[nameLen + 1];
  strncpy(this->name, name, nameLen);

  this->age = age;
  this->weight = weight;
}

Dog::~Dog() {
  delete [] name;
}

void Dog::print() {
  cout << endl;
  cout << "이름  : " << this->name << endl;
  cout << "나이  : " << this->age << endl;
  cout << "몸무게: " << this->weight << endl;
  cout << endl;
}

Dog* createDogWithInput() {
  char name[100];
  unsigned short age;
  unsigned short weight;

  cout << "이름: ";
  cin >> name;
  cout << "나이: ";
  cin >> age;
  cout << "몸무게: ";
  cin >> weight;

  return new Dog((const char *) name, age, weight);
}

int main() {
  Dog *dog = createDogWithInput();
  dog->print();

  delete dog;
  return 0;
}
