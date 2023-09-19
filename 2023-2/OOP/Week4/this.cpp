#include <iostream>
using namespace std;

class WhoAmI {
  public:
    int id;
    WhoAmI(int id_arg);
    void showYourself() const;
};

WhoAmI::WhoAmI(int id_arg) {
  id = id_arg;
}

void WhoAmI::showYourself() const {
  cout << id << " this: " << this << endl;
}

int main() {
  WhoAmI obj1(1);
  WhoAmI obj2(2);
  WhoAmI obj3(3);

  obj1.showYourself();
  obj2.showYourself();
  obj3.showYourself();

  cout << "&obj1: " << &obj1 << endl;
  cout << "&obj2: " << &obj2 << endl;
  cout << "&obj3: " << &obj3 << endl;

  return 0;
}
