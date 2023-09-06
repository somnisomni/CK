#include <iostream>
#include <string>
using namespace std;

class Student {
  private:
    string name;
    string stdid;
    int korean;
    int english;

  public:
    bool init(string s_name, string s_stdid, int s_korean, int s_english) {
      if(s_name.empty() || s_stdid.empty() || s_korean < 0 || s_english < 0)
        return false;

      name = s_name;
      stdid = s_stdid;
      korean = s_korean;
      english = s_english;
      return true;
    }

    void show() {
      cout << "학생명: " << name << endl;
      cout << "학번: " << stdid << endl;
      cout << "국어 점수: " << korean << endl;
      cout << "영어 점수: " << english << endl;
    }
};

bool initStudent(Student *student) {
  string s_name, s_stdid;
  int s_korean, s_english;

  cout << "학생명: ";
  cin >> s_name;
  cout << "학번: ";
  cin >> s_stdid;
  cout << "국어 점수: ";
  cin >> s_korean;
  cout << "영어 점수: ";
  cin >> s_english;
  cout << endl;

  if(!student->init(s_name, s_stdid, s_korean, s_english)) {
    cout << "학생 정보를 정확히 입력해주세요." << endl;
    return false;
  }
  return true;
}

int main() {
  Student student;

  if(initStudent(&student)) {
    student.show();
  }

  return 0;
}
