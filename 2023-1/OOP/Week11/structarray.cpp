#include <iostream>
#include <string>
using namespace std;

struct Student {
  string name;
  string postnum;
  string addr;
};

int main() {
  Student s[3];

  for(int i = 0; i < 3; i++) {
    cout << endl;
    cout << "이름: ";
    getline(cin, s[i].name);
    cout << "우편번호: ";
    getline(cin, s[i].postnum);
    cout << "주소: ";
    getline(cin, s[i].addr);
  }

  cout << endl;
  cout << "이름\t우편번호\t주소" << endl;
  for(int i = 0; i < 3; i++) {
    cout << s[i].name << "\t" << s[i].postnum << "\t" << s[i].addr << endl;
  }

  return 0;
}
