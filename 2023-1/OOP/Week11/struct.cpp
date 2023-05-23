#include <iostream>
#include <string>
using namespace std;

struct Student {
  string school;
  int grade;
  string name;
};

int main() {
  Student me;
  me.school = "청강문화산업대학교";
  me.grade = 1;
  me.name = "아무개";

  cout << "학교: " << me.school << endl;
  cout << "학년: " << me.grade << "학년" << endl;
  cout << "이름: " << me.name << endl;
  cout << sizeof(me) << endl;

  return 0;
}
