#include <iostream>
#include <cstring>
using namespace std;

class Person {
  private:
    char *name;
    char *stdId;
  public:
    Person(char *name, char *stdId) {
      this->name = new char[strlen(name) + 1];
      strcpy(this->name, name);
      this->stdId = new char[strlen(stdId) + 1];
      strcpy(this->stdId, stdId);
    }
    ~Person() {
      delete [] name;
      delete [] stdId;
    }
    char* getName() const { return name; }
    char* getStudentId() const { return stdId; }
};

class Student: public Person {
  private:
    char *major;
  public:
    Student(char *name, char *stdId, char *major): Person(name, stdId) {
      this->major = new char[strlen(major) + 1];
      strcpy(this->major, major);
    }
    ~Student() {
      delete [] major;
    }
    char* getMajor() const { return major; }
    void showMyInfo() const {
      cout << "이름: " << getName() << endl;
      cout << "학번: " << getStudentId() << endl;
      cout << "전공: " << getMajor() << endl;
    }
};

int main() {
  Student std1("장동건", "20230001", "수학과");
  std1.showMyInfo();
  Student std2("아이유", "20230002", "게임학과");
  std2.showMyInfo();
  return 0;
}
