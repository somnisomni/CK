#include <iostream>
using namespace std;

template <class T>
class Info {
  private:
    T data;
  public:
    Info() { }

    void inputData() { cin >> data; }
    void showData() const { cout << data << endl; }
};

int main() {
  Info<int> i;
  Info<double> d;
  Info<char> c;

  cout << "정수 입력: "; i.inputData();
  cout << "실수 입력: "; d.inputData();
  cout << "문자 입력: "; c.inputData();

  i.showData();
  d.showData();
  c.showData();

  return 0;
}
