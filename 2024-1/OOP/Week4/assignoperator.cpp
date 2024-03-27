#include <iostream>
using namespace std;

class RacingCar {
  private:
    string name;

  public:
    RacingCar(string name): name(name) { }
    RacingCar(const RacingCar& src): name(src.name) {
      cout << "RacingCar: Copy constructor called" << endl;
    }

    RacingCar& operator=(const RacingCar& rhs) {
      if(this == &rhs) return *this;

      cout << "RacingCar: Assignment operator called" << endl;
      name = rhs.name;

      return *this;
    }

    string getName() const { return name; }
};

int main() {
  RacingCar car1("Car1");
  RacingCar car2("Car2");

  car2 = car1;

  cout << "car1 name: " << car1.getName() << endl;
  cout << "car2 name: " << car2.getName() << endl;

  return 0;
}
