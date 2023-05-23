#include <iostream>
#include <string>
using namespace std;

struct Person {
  string name;
  string phoneNumber;
};

struct PersonInfo {
  Person *pp;
  string subject;
  int score;
};

int main() {
  Person per;
  PersonInfo personInfo;
  personInfo.pp = &per;

  cout << "이름: ";
  cin >> (personInfo.pp)->name;
  cout << "핸드폰: ";
  cin >> (personInfo.pp)->phoneNumber;
  cout << "과목: ";
  cin >> personInfo.subject;
  cout << "점수: ";
  cin >> personInfo.score;

  cout << endl;
  cout << "이름\t핸드폰\t\t과목\t점수" << endl;
  cout << (personInfo.pp)->name << "\t";
  cout << (personInfo.pp)->phoneNumber << "\t";
  cout << personInfo.subject << "\t";
  cout << personInfo.score << endl;

  return 0;
}
