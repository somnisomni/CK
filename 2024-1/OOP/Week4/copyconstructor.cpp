#include <iostream>
using namespace std;

class Car {
  protected:
    string name;

  public:
    Car(string name): name(name) { }
    // 복사생성자 선언 없음 (컴파일러가 생성)

    string getName() const { return name; }
};

class RacingCar: public Car {
  public:
    RacingCar(string name): Car(name) { }
    RacingCar(const RacingCar& src): Car(src) {
      cout << "RacingCar: Copy constructor of Car called" << endl;
    }
};

class UniqueCar: public Car {
  public:
    UniqueCar(string name): Car(name) { }
    UniqueCar(const UniqueCar& src) = delete;
};

int main() {
  RacingCar car1("Car1");
  RacingCar copyCar1(car1);

  UniqueCar car2("Car2");
  // UniqueCar copyCar2(car2);   // Use of deleted function

  cout << "car1 original name: " << car1.getName() << endl;
  cout << "car1 copy name: " << copyCar1.getName() << endl;

  return 0;
}
