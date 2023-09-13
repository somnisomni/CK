#include <iostream>
#include <string>
using namespace std;

class Car {
  private:
    string gamerId;
    double fuelGuage = 1000.0f;
    double currentSpeed = 0.0f;
  public:
    Car(string _gamerId);
    bool isOutOfFuel();
    void accelerate();
    void brake();
    void showStatus();
};

Car::Car(string _gamerId) {
  gamerId = _gamerId;
}

bool Car::isOutOfFuel() {
  return fuelGuage <= 0.0f;
}

void Car::accelerate() {
  if(fuelGuage < 5.0f) {
    cout << "연료가 부족합니다." << endl;
    return;
  }

  if(currentSpeed >= 180.0f) {
    cout << "최고 속도입니다." << endl;
    return;
  }

  fuelGuage -= 5.0f;
  currentSpeed += 10.0f;
}

void Car::brake() {
  if(fuelGuage < 10.0f) {
    cout << "연료가 부족합니다." << endl;
    return;
  }

  if(currentSpeed <= 0.0f) {
    cout << "이미 정지 상태입니다." << endl;
    return;
  }

  fuelGuage -= 10.0f;
  currentSpeed = 0.0f;
}

void Car::showStatus() {
  cout << " ===== 게이머: " << gamerId << " ===== " << endl;
  cout << "  * 연료량   : " << fuelGuage << "L" << endl;
  cout << "  * 현재 속도: " << currentSpeed << "km/h" << endl;
}

void process(char selection, Car *car) {
  switch(selection) {
    case 'q': return;
    case 'a':
      car->accelerate();
      car->showStatus();
      break;
    case 'b':
      car->brake();
      car->showStatus();
      break;
    case 's':
      car->showStatus();
      break;
    default:
      cout << "잘못된 입력입니다." << endl;
      break;
  }
}

void loop(Car *car) {
  char selection;

  do {
    if(car->isOutOfFuel()) {
      cout << "연료 모두 소모, 게임 종료" << endl;
      return;
    }

    cout << endl;
    cout << " ~~ 제어 메뉴 ~~" << endl;
    cout << "  a. 가속" << endl;
    cout << "  b. 브레이크" << endl;
    cout << "  s. 현재 상태 출력" << endl;
    cout << "  q. 종료" << endl;
    cout << "    입력: ";
    cin >> selection;
    cout << endl;

    process(selection, car);
  } while(selection != 'q');
}

int main() {
  string gamerId;
  cout << "게이머 ID 입력: ";
  cin >> gamerId;

  Car *car = new Car(gamerId);

  loop(car);

  delete car;

  return 0;
}
