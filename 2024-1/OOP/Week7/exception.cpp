#include <iostream>
using namespace std;

double safeDivide(double num, double den) {
  if (den == 0) {
    throw invalid_argument("Divide by zero");
  }

  return num / den;
}

int main() {
  try {
    cout << safeDivide(5, 2) << endl;
    cout << safeDivide(10, 0) << endl;
    cout << safeDivide(3, 3) << endl;
  } catch(const exception &e) {
    cout << "Exception caught: " << e.what() << endl;
  }

  return 1;
}
