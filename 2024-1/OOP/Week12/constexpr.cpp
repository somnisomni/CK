#include <iostream>
using namespace std;

template<typename T> constexpr T pi = T(3.1415926535897932385L);
template<> const char* pi<const char*> = "3.14";
template<> string pi<string> = "3.14";

int main() {
  cout << "pi<int>: " << pi<int> << endl;
  cout << "pi<float>: " << pi<float> << endl;
  cout << "pi<double>: " << pi<double> << endl;
  cout << "pi<long double>: " << pi<long double> << endl;
  cout << "pi<const char*>: " << pi<const char*> << endl;
  cout << "pi<string>: " << pi<string> << endl;

  return 0;
}
