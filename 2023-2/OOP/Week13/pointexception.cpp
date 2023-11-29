#include <iostream>
#include <string>
using namespace std;

class Exception {
  private:
    string msg;
  public:
    Exception(const string msg = "오류"): msg(msg) { }

    string getMsg() const { return "[!] " + msg; }
};

class Point {
  private:
    int x, y;
  public:
    Point(const int x = 0, const int y = 0) {
      setPosition(x, y);
    }

    void setPosition(const int x, const int y) {
      try {
        if(x < 0 || y < 0) throw Exception("음수 좌표로 설정할 수 없음");
        this->x = x;
        this->y = y;
      } catch(Exception &e) {
        cout << e.getMsg() << endl;
      }
    }
    void print() const {
      cout << "(" << x << ", " << y << ")" << endl;
    }
};

int main() {
  int x, y;
  Point *p = new Point();
  cin >> x >> y;
  p->setPosition(x, y);
  p->print();

  delete p;
  return 0;
}
