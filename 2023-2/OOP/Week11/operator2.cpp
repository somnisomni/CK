#include <iostream>
using namespace std;

class My {
  private:
    int val;
  public:
    My(int data): val(data) { }
    void list() const { cout << val << endl; }

    friend const My& operator++(My &m);
    friend const My operator++(My &m, int);
};

const My& operator++(My &m) {
  m.val++;
  return m;
}

const My operator++(My &m, int) {
  const My copy(m.val);
  m.val++;
  return copy;
}

int main() {
  My a = 5;
  My x = a++;
  a.list();
  x.list();
  My y = ++a;
  a.list();
  y.list();

  return 0;
}
