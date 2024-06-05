#include <iostream>
using namespace std;

class Parent {
  public:
    virtual ~Parent() = default;
};

class Child : public Parent {
  public:
    virtual ~Child() = default;
};

int main() {
  Parent* parent = nullptr;
  Child* child = new Child();

  cout << "parent: " << parent << endl;
  cout << "child: " << child << endl;

  parent = child;
  child = dynamic_cast<Child*>(parent);

  cout << "parent: " << parent << endl;
  cout << "child: " << child << endl;

  cout << endl << " --- " << endl << endl;

  try {
    Parent refParent;
    Child refChild;
    Parent& refP = refParent;
    Child& refC = dynamic_cast<Child&>(refP);

    cout << "refParent: " << &refParent << endl;
    cout << "refChild: " << &refChild << endl;
    cout << "refP: " << &refP << endl;
    cout << "refC: " << &refC << endl;
  } catch(const bad_cast& e) {
    cout << "Exception: " << e.what() << endl;
  }

  delete parent;
  return 0;
}
