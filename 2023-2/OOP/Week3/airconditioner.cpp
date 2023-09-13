#include <iostream>
#include <time.h>

#if defined UNIX || defined LINUX || defined __APPLE__
#include <unistd.h>
#define SLEEP(x) sleep(x)
#endif
#if defined _WIN32 || defined _WIN64
#include <windows.h>
#define SLEEP(x) Sleep(x * 1000)
#endif

using namespace std;

class AirConditionerSensor {
  private:
    double roomTemperature = 20.0f;
  public:
    void setRoomTemperature(double temp) { roomTemperature = temp; }
    double getRoomTemperature() const { return roomTemperature; }
};

class AirConditioner {
  private:
    AirConditionerSensor *sensor;
    double targetTemperature = 26.0f;
    bool power = false;
  public:
    AirConditioner(AirConditionerSensor *sensor);
    void turnOn() { power = true; }
    void turnOff() { power = false; }
    void setTargetTemperature(double temp) { targetTemperature = temp; }
    void increaseTargetTemperature() { targetTemperature += 1.0f; }
    void decreaseTargetTemperature() { targetTemperature -= 1.0f; }
    double getTargetTemperature() const { return targetTemperature; }
    AirConditionerSensor *getSensor() const { return sensor; }
    void showStatus() const;
};

AirConditioner::AirConditioner(AirConditionerSensor *_sensor) {
  sensor = _sensor;
}

void AirConditioner::showStatus() const {
  cout << endl;
  cout << " ================== " << endl;
  cout << " ==== 에 어 컨 ==== " << endl;
  cout << " ================== " << endl;
  cout << endl;
  cout << "  * 전원 상태: " << (power ? "켜짐" : "꺼짐") << endl;
  cout << "  * 방 온도  : " << sensor->getRoomTemperature() << "도" << endl;
  cout << "  * 목표 온도: " << targetTemperature << "도" << endl;
  cout << endl;
}

void tick(AirConditioner *ac, int secondsElapsed) {
  if(secondsElapsed % 3 == 0) {
    cout << " 방 온도 " << ac->getSensor()->getRoomTemperature() << "도 -> ";
    if(ac->getSensor()->getRoomTemperature() > ac->getTargetTemperature()) {
      ac->getSensor()->setRoomTemperature(ac->getSensor()->getRoomTemperature() - 1.0f);
    } else if(ac->getSensor()->getRoomTemperature() < ac->getTargetTemperature()) {
      ac->getSensor()->setRoomTemperature(ac->getSensor()->getRoomTemperature() + 1.0f);
    }
    cout << ac->getSensor()->getRoomTemperature() << "도" << endl;
  }
}

int main() {
  AirConditionerSensor *acs = new AirConditionerSensor;
  AirConditioner *ac = new AirConditioner(acs);

  cout << "  >>> 초기 상태 <<<" << endl;
  ac->showStatus();

  cout << endl << "  >>> 전원 ON <<<" << endl;
  ac->turnOn();
  ac->showStatus();

  cout << endl << "  >>> 온도 변화 (+) <<<" << endl;
  cout << "  >>> 방 온도  : " << ac->getSensor()->getRoomTemperature() << "도 <<<" << endl;
  cout << "  >>> 목표 온도: " << ac->getTargetTemperature() << "도 <<<" << endl;
  for(int i = 1; i <= 3 * 10; i++) {
    cout << i << "초 " << flush;
    tick(ac, i);
    SLEEP(1);
  }
  ac->showStatus();

  cout << endl << "  >>> 온도 변화 (-) <<<" << endl;
  ac->setTargetTemperature(20.0f);
  cout << "  >>> 방 온도  : " << ac->getSensor()->getRoomTemperature() << "도 <<<" << endl;
  cout << "  >>> 목표 온도: " << ac->getTargetTemperature() << "도 <<<" << endl;
  for(int i = 1; i <= 3 * 10; i++) {
    cout << i << "초 " << flush;
    tick(ac, i);
    SLEEP(1);
  }
  ac->showStatus();

  cout << endl << "  >>> 전원 OFF <<<" << endl;
  ac->turnOff();
  ac->showStatus();

  return 0;
}
