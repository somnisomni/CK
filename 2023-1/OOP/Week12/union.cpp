#include <iostream>
#include <string>
using namespace std;

#define STUDENT_TYPE_KOREAN 1
#define STUDENT_TYPE_FOREIGN 2

union StudentIdentifier {
  int studentNumber;
  char foreignSerial[10];
};

struct Student {
  short type;
  string name;
  StudentIdentifier identifier;
};

int main() {
  Student student;

  cout << "학생 이름: ";
  cin >> student.name;
  cout << "학생 구분(내국인 - " << STUDENT_TYPE_KOREAN << ", 외국인 - " << STUDENT_TYPE_FOREIGN << "): ";
  cin >> student.type;
  switch(student.type) {
    case STUDENT_TYPE_KOREAN:
      cout << "학번: ";
      cin >> student.identifier.studentNumber;
      break;
    case STUDENT_TYPE_FOREIGN:
      cout << "외국인등록번호: ";
      cin >> student.identifier.foreignSerial;
      break;
    default:
      cout << "잘못된 구분입니다." << endl;
      return 1;
  }

  cout << endl << endl;

  cout << "학생 이름: " << student.name << endl;
  switch(student.type) {
    case STUDENT_TYPE_KOREAN:
      cout << "학생 구분: 내국인" << endl;
      cout << "학번: " << student.identifier.studentNumber << endl;
      break;
    case STUDENT_TYPE_FOREIGN:
      cout << "학생 구분: 외국인" << endl;
      cout << "외국인등록번호: " << student.identifier.foreignSerial << endl;
      break;
  }

  return 0;
}
