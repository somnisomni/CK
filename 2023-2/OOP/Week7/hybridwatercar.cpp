#include <iostream>
using namespace std;

class Car {
  private:
    int gasoline;
  public:
    Car() { }
    Car(int gasoline): gasoline(gasoline) { }
    int getGasGuage() const { return gasoline; }
};

class HybridCar: public Car {
  private:
    int electric;
  public:
    HybridCar() { }
    HybridCar(int electric): electric(electric) { }
    HybridCar(int gasoline, int electric): Car(gasoline), electric(electric) { }
    int getElecGuage() const { return electric; }
};

class HybridWaterCar: public HybridCar {
  private:
    int water;
  public:
    HybridWaterCar() { }
    HybridWaterCar(int water): water(water) { }
    HybridWaterCar(int electric, int water): HybridCar(electric), water(water) { }
    HybridWaterCar(int gasoline, int electric, int water): HybridCar(gasoline, electric), water(water) { }
    void showCurGuage() const {
      cout << "Gasoline: " << getGasGuage() << endl;
      cout << "Electric: " << getElecGuage() << endl;
      cout << "Water: " << water << endl;
    }
};

int main() {
  HybridWaterCar hbCar(79, 65, 34);
  hbCar.showCurGuage();
  return 0;
}