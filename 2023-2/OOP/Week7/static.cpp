#include <iostream>
#include <string>
using namespace std;

class Student {
  private:
    string name;
    string id;
  public:
    static int STUDENT_COUNT;
    Student(string name, string id): name(name), id(id) {
      cout << "constructor call" << endl;
      STUDENT_COUNT++;
    }
    ~Student() {
      cout << "destructor call" << endl;
      STUDENT_COUNT--;
    }
    string getName() const { return name; }
    string getId() const { return id; }
};
int Student::STUDENT_COUNT = 0;

int main() {
  cout << "학생 수: " << Student::STUDENT_COUNT << endl;

  Student *s1 = new Student("홍길동", "20230001");
  Student *s2 = new Student("이순신", "20230002");

  cout << "학생 수: " << Student::STUDENT_COUNT << endl;

  delete s1;
  delete s2;

  cout << "학생 수: " << Student::STUDENT_COUNT << endl;

  return 0;
}
