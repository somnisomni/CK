#include <iostream>
#include <string>
using namespace std;

class Student {
  private:
    string name;
    string stdid;

  public:
    bool init(string s_name, string s_stdid) {
      if(s_name.empty() || s_stdid.empty())
        return false;

      name = s_name;
      stdid = s_stdid;
      return true;
    }

    void show() {
      cout << "학생명: " << name << endl;
      cout << "학번: " << stdid << endl;
    }
};

void create(Student *student) {
  string s_name, s_stdid;

  cout << "학생명: ";
  cin >> s_name;
  cout << "학번: ";
  cin >> s_stdid;
  cout << endl;

  if(!student->init(s_name, s_stdid)) {
    cout << "학생 정보를 정확히 입력해주세요." << endl;
    return;
  }
}

int main() {
  Student student;
  create(&student);

  student.show();

  return 0;
}
