#include <iostream>
using namespace std;

class First {
  public:
    virtual void simpleFunc() const {
      cout << "First" << endl;
    }
};

class Second: public First {
  public:
    virtual void simpleFunc() const {
      cout << "Second" << endl;
    }
};

int main() {
  First *ptr = new First();
  ptr->simpleFunc();
  delete ptr;

  ptr = new Second();
  ptr->simpleFunc();
  delete ptr;

  return 0;
}
