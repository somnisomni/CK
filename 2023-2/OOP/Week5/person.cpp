#include <iostream>
#include <string>
using namespace std;

class Person {
  private:
    string name;
    unsigned short age;
    string phone;
  public:
    Person() { }
    Person(string name, unsigned short age, string phone): name(name), age(age), phone(phone) { }
    string getName() const { return name; }
    unsigned short getAge() const { return age; }
    string getPhone() const { return phone; }
    void print() {
      cout << "이름: " << name << ", 나이: " << age << ", 전화번호: " << phone << endl;
    }
};

int main() {
  static const int MAXSIZE = 3;
  unsigned int currentPos = 0;
  Person *persons[MAXSIZE];

  bool shouldBreak = false;
  while(!shouldBreak) {
    cout << endl << endl;
    cout << " ~~ 메뉴 ~~ " << endl;
    cout << "  1. 추가" << endl;
    cout << "  2. 모두 보기" << endl;
    cout << "  0. 종료" << endl;
    cout << " 현재 " << currentPos << "명이 저장되어 있습니다." << endl;
    cout << endl;

    unsigned int selection;
    cout << " 입력> ";
    cin >> selection;

    switch(selection) {
      case 0: {
        shouldBreak = true;
        break;
      }
      case 1: {
        if(currentPos >= MAXSIZE) {
          cout << "더 이상 저장할 수 없습니다." << endl;
          break;
        }

        string name;
        unsigned short age;
        string phone;

        cout << "이름: ";
        cin >> name;
        cout << "나이: ";
        cin >> age;
        cout << "전화번호: ";
        cin >> phone;

        Person *person = new Person(name, age, phone);
        persons[currentPos++] = person;

        cout << "추가 완료." << endl;
        break;
      }
      case 2: {
        if(currentPos == 0) {
          cout << "저장된 데이터가 없습니다." << endl;
          break;
        }

        for(int i = 0; i < currentPos; i++) {
          persons[i]->print();
        }
        break;
      }
      default: {
        cout << "잘못 입력하였습니다." << endl;
        cin.get();
        continue;
      }
    }
  }

  for(int i = 0; i < currentPos; i++) delete persons[i];
  return 0;
}
