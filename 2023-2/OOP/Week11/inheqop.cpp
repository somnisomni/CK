#include <iostream>
using namespace std;

class First {
  private:
    int num1;
  public:
    First(int n1): num1(n1) { }
    void showData() { cout << num1 << endl; }
    First& operator=(const First& ref) {
      cout << "First& operator= 실행" << endl;
      num1 = ref.num1;
      return *this;
    }
};

class Second: public First {
  private:
    int num2;
  public:
    Second(int n1, int n2): First(n1), num2(n2) { }
    void showData() {
      First::showData();
      cout << num2 << endl;
    }
    Second& operator=(const Second& ref) {
      cout << "Second& operator= 실행" << endl;
      First::operator=(ref);
      num2 = ref.num2;
      return *this;
    }
};

int main() {
  Second sec1(111, 222);
  Second sec2(333, 444);
  sec1 = sec2;
  sec1.showData();
  return 0;
}
