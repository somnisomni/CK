#include <iostream>
#include <string>
using namespace std;

class Student {
  private:
    string name;
    string stdid;
    unsigned int oop;
    unsigned int unity;

  public:
    Student(const string s_name, const string s_stdid, const unsigned int s_oop, const unsigned int s_unity) {
      name = s_name;
      stdid = s_stdid;
      oop = s_oop;
      unity = s_unity;
    }

    void show() {
      cout << "학생명: " << name << endl;
      cout << "학번: " << stdid << endl;
      cout << "객체지향 점수: " << oop << endl;
      cout << "Unity 점수: " << unity << endl;
    }
};

Student* initStudent() {
  string s_name, s_stdid;
  int s_oop, s_unity;

  cout << "학생명: ";
  cin >> s_name;
  cout << "학번: ";
  cin >> s_stdid;
  cout << "객체지향 점수: ";
  cin >> s_oop;
  cout << "Unity 점수: ";
  cin >> s_unity;
  cout << endl;

  return new Student(s_name, s_stdid, s_oop, s_unity);
}

int main() {
  Student *student = initStudent();

  student->show();

  return 0;
}
