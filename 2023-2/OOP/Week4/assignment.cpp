#include <iostream>
#include <string>
using namespace std;

class Person {
  private:
    string name;
  public:
    string getName() const { return name; }
    void setName(const string name) { this->name = name; }
    void show() const {
      cout << "이름: " << name << endl;
    }
};

class Family {
  private:
    Person *persons;
    string name;
    unsigned int size;
  public:
    Family(const string name, const unsigned int size): name(name), size(size) {
      this->persons = new Person[size]();
    }
    ~Family() {
      delete [] persons;
    }
    string getName() const { return name; }
    void setMemberName(const unsigned int index, const string name) {
      this->persons[index].setName(name);
    }
    void show() const {
      cout << endl;
      cout << "=== " << name << " Family ===" << endl;
      for(int i = 0; i < size; i++) {
        cout << "[#" << i + 1 << "] ";
        persons[i].show();
      }
      cout << endl;
    }
};

int main() {
  Family *simpson = new Family("Simpsons", 3);
  simpson->setMemberName(0, "Mr. Simpson");
  simpson->setMemberName(1, "Mrs. Simpson");
  simpson->setMemberName(2, "Bart Simpson");

  simpson->show();

  delete simpson;
  return 0;
}
