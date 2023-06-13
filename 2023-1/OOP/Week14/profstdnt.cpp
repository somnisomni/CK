#include <iostream>
#include <string>
using namespace std;

enum PersonType {
  PROFESSOR = 0,
  STUDENT = 1
};

struct Professor {
  char mail[50];
  char mobile[12];
};

struct Student {
  char major[50];
  int id;
  float score;
};

struct Person {
  PersonType type;
  string name;
  union {
    Professor prof;
    Student stdnt;
  } info;
};

void printPersonInfo(const Person person) {
  cout << "인원 분류: " << (person.type == PROFESSOR ? "교수" : "학생") << endl;
  cout << "이름: " << person.name << endl;
  switch(person.type) {
    case PROFESSOR:
      cout << "이메일 주소: " << person.info.prof.mail << endl;
      cout << "휴대폰 번호: " << person.info.prof.mobile << endl;
      break;
    case STUDENT:
      cout << "전공: " << person.info.stdnt.major << endl;
      cout << "학번: " << person.info.stdnt.id << endl;
      cout << "학점: " << person.info.stdnt.score << endl;
      break;
  }
}

void inputPersonInfo(Person &person) {
  int pType;
  cout << "인원 분류 (교수: 0, 학생: 1): ";
  cin >> pType;
  person.type = (PersonType)pType;
  cout << "이름: ";
  cin >> person.name;

  switch(person.type) {
    case PROFESSOR:
      cout << "이메일 주소: ";
      cin >> person.info.prof.mail;
      cout << "휴대폰 번호: ";
      cin >> person.info.prof.mobile;
      break;
    case STUDENT:
      cout << "전공: ";
      cin >> person.info.stdnt.major;
      cout << "학번: ";
      cin >> person.info.stdnt.id;
      cout << "학점: ";
      cin >> person.info.stdnt.score;
      break;
  }
}

int main() {
  int pType;
  Person person;

  inputPersonInfo(person);

  cout << endl << endl;

  printPersonInfo(person);

  return 0;
}
