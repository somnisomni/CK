#include <iostream>
using namespace std;

class Number {
  private:
    int num;
  public:
    Number(): num(0) { }
    Number(int data): num(data) { }
    Number operator+(const Number& n) const { return Number(num + n.num); }
    void show() { cout << num << endl; }
};

int main() {
  Number a(5);
  Number b(3);
  Number c;

  c = a + b;
  c.show();

  return 0;
}
