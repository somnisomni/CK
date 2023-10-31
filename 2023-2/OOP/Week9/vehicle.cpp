#include <iostream>
using namespace std;

class Vehicle {
  protected:
    int speed;
  public:
    Vehicle(int s): speed(s) { }
    ~Vehicle() { }

    virtual void show() = 0;
};

class Car: public Vehicle {
  protected:
    int num;
    double gas;
  public:
    Car(int s, int num, double gas): Vehicle(s), num(num), gas(gas) { }
    ~Car() { }

    virtual void show() {
      cout << "자동차 속도: " << speed << endl;
      cout << "자동차 번호: " << num << endl;
      cout << "자동차 연료량: " << gas << endl;
    }
};

class Plane: public Vehicle {
  protected:
    int flight;
  public:
    Plane(int s, int f): Vehicle(s), flight(f) { }
    ~Plane() { }

    virtual void show() {
      cout << "비행기 속도: " << speed << endl;
      cout << "비행기 편명: " << flight << endl;
    }
};

int main() {
  Vehicle *pv[2];
  Car c(8604, 25.5, 80);
  pv[0] = &c;
  Plane pl(940, 500);
  pv[1] = &pl;

  for(int i = 0; i < 2; i++) {
    pv[i]->show();
    cout << endl;
  }

  return 0;
}
