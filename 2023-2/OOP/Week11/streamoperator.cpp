#include <iostream>
#include <cstring>
using namespace std;

class PhoneNumber {
  private:
    char areaCode[4];
    char exchange[5];
    char line[5];
  public:
    PhoneNumber(): areaCode(""), exchange(""), line("") { }
    PhoneNumber(char *areaCode, char *exchange, char *line) {
      strncpy(this->areaCode, areaCode, 3);
      strncpy(this->exchange, exchange, 4);
      strncpy(this->line, line, 4);
    }

    friend ostream& operator<<(ostream &out, const PhoneNumber &pn);
    friend istream& operator>>(istream &in, PhoneNumber &pn);
};

ostream& operator<<(ostream &out, const PhoneNumber &pn) {
  out << "(" << pn.areaCode << ") " << pn.exchange << "-" << pn.line;
  return out;
}

istream& operator>>(istream &in, PhoneNumber &pn) {
  in >> pn.areaCode >> pn.exchange >> pn.line;
  return in;
}

int main() {
  PhoneNumber pn;
  cin >> pn;
  cout << pn << endl;

  return 0;
}
