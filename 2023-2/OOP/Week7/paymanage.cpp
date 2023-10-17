#include <iostream>
#include <string>
#include <cstring>
using namespace std;

class PermanentWorker {
  private:
    char name[100];
    uint salary;
  public:
    PermanentWorker(const char *n, const uint s): salary(s) {
      strcpy(name, n);
    }
    float getPay() const { return salary / 12.0f; }
    void showSalaryInfo() const {
      cout << "사원명: " << name << endl;
      cout << "연봉  : " << salary << endl;
      cout << "월 급여 : " << getPay() << endl;
      cout << endl;
    }
};

class EmployeeHandler {
  private:
    PermanentWorker *empList[50];
    int empNum = 0;
  public:
    EmployeeHandler(): empNum(0) { };
    ~EmployeeHandler() {
      for(int i = 0; i < empNum; i++) delete empList[i];
    }
    void addEmployee(PermanentWorker *emp) {
      empList[empNum++] = emp;
    }
    void showAllSalaryInfo() const {
      for(int i = 0; i < empNum; i++) {
        empList[i]->showSalaryInfo();
      }
    }
    void showTotalSalary() const {
      uint total = 0;
      for(int i = 0; i < empNum; i++) {
        total += empList[i]->getPay();
      }
      
      cout << "이번달 급여 총액: " << total << endl;
    }
};

int main() {
  EmployeeHandler handler;

  handler.addEmployee(new PermanentWorker("JUN", 2000));
  handler.addEmployee(new PermanentWorker("LEE", 3500));

  handler.showAllSalaryInfo();
  handler.showTotalSalary();
}