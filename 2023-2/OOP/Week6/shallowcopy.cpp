#include <iostream>
#include <cstring>
using namespace std;

class Person {
  private:
    char *name;
    int age;
  public:
    Person(char *myname, int myage) {
      int len = strlen(myname) + 1;
      name = new char[len];
      strcpy(name, myname);
      age = myage;
    }
    ~Person() {
      delete [] name;
      cout << "called destruction" << endl;
    }
    void showData() const {
      cout << name << "\t" << age << endl;
    }
};

int main() {
  Person man1("Hong Gildong", 24);
  Person man2 = man1;
  man1.showData();
  man2.showData();
  return 0;
}
