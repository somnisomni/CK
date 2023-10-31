#include <iostream>
using namespace std;

class Car {
  protected:
    int num;
    double gas;
  public:
    Car(int n, double g): num(n), gas(g) { }
    virtual void show() const {
      cout << "자동차 차량 번호: " << num << endl;
      cout << "자동차 연료량: " << gas << endl;
    }
};

class RacingCar: public Car {
  private:
    int course;
  public:
    RacingCar(int n, double g, int c): Car(n, g), course(c) { }
    virtual void show() const {
      cout << "레이싱카 차량 번호: " << num << endl;
      cout << "레이싱카 연료량: " << gas << endl;
      cout << "코스 번호: " << course << endl;
    }
};

int main() {
  Car *pCar[2] = {
    new Car(4352, 35.5),
    new RacingCar(4344, 32.1, 3)
  };

  for(int i = 0; i < 2; i++) {
    pCar[i]->show();
    cout << endl;
  }
  for(int i = 0; i < 2; i++) delete pCar[i];

  return 0;
}
