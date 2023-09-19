#include <iostream>
using namespace std;

class Simple {
  private:
    int num;
  public:
    Simple(int n);
    void showData();
    Simple *getThisPointer() { return this; }
};

Simple::Simple(int n) {
  num = n;
  cout << "addr: " << this << endl;
}

void Simple::showData() {
  cout << num << endl;
}

int main() {
  Simple obj(100);
  Simple *ptr1 = obj.getThisPointer();

  cout << ptr1 << endl;
  ptr1->showData();

  return 0;
}
