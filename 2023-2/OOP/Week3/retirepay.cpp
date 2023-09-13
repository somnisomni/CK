#include <iostream>
#include <string>
using namespace std;

class Employee {
  private:
    string name;
    unsigned int age;
    unsigned int yos = 0; // Year of Service
    unsigned int monthSalary = 2000000;
  public:
    Employee(string _name, unsigned int _age);
    Employee(string _name, unsigned int _age, unsigned int _yos, unsigned int _monthSalary);
    int getRetirementPay();
    void showInfo();
};

Employee::Employee(string _name, unsigned int _age) {
  name = _name;
  age = _age;
}

Employee::Employee(string _name, unsigned int _age, unsigned int _yos, unsigned int _monthSalary) {
  name = _name;
  age = _age;
  yos = _yos;
  monthSalary = _monthSalary;
}

int Employee::getRetirementPay() {
  return monthSalary * yos;
}

void Employee::showInfo() {
  cout << "=== " << name << " ===" << endl;
  cout << "나이: " << age << "세" << endl;
  cout << "근속연수: " << yos << "년" << endl;
  cout << "월급: " << monthSalary << "원" << endl;
  cout << "퇴직금: " << getRetirementPay() << "원" << endl;
  cout << endl;
}

int main() {
  Employee *employees[3] = {
    new Employee("강한국", 27, 2, 3500000),
    new Employee("김호산", 35, 7, 5000000),
    new Employee("아이유", 25)
  };

  for(int i = 0; i < 3; i++) {
    employees[i]->showInfo();
  }

  return 0;
}
