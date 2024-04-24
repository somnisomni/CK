#include <iostream>
using namespace std;

class S {
  public:
    char c;

    S(char c): c(c) {
      cout << "S(" << c << ") created" << endl;
    }
    ~S() {
      cout << "S(" << c << ") destroyed" << endl;
    }
};

void foo() {
  S s('f');
  throw 'f';
}

int main() {
  set_terminate([]() {
    cout << "Program termination (unhandled exception)" << endl << flush;
    exit(1);
  });

  try {
    S s('m');
    foo();
  } catch(const char &e) {
    cout << "Exception caught: " << e << endl;
  }

  try {
    S s('m');
    foo();
  } catch(const exception &e) {
    cout << "Exception caught: " << e.what() << endl;
  }

  return 0;
}
