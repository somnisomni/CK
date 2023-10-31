#include <iostream>
#include <string>
#include <cstring>
using namespace std;

class Car {
  private:
    string number;
    char *manufacturer;
  public:
    Car(string num, const char *manu): number(num) {
      manufacturer = new char[strlen(manu) + 1];
      strcpy(manufacturer, manu);
    }
    Car(const Car &copy): number(copy.number) {
      manufacturer = new char[strlen(copy.manufacturer) + 1];
      strcpy(manufacturer, copy.manufacturer);
    }
    ~Car() { delete [] manufacturer; }

    void show() const {
      cout << "차량 번호: " << number << endl;
      cout << "제조사: " << manufacturer << endl;
    }
};

class Automobile: public Car {
  private:
    string model;
  public:
    Automobile(string num, const char *manu, string model): Car(num, manu), model(model) { }
    ~Automobile() { }

    void show() const {
      Car::show();
      cout << "모델명: " << model << endl << endl;
    }
};

int main() {
  Automobile *pt[3];
  pt[0] = new Automobile("14다 4399", "기아", "K5");
  pt[1] = new Automobile("10가 1234", "기아", "K7");
  pt[2] = new Automobile("13가 5555", "기차", "K9");

  for(int i = 0; i < 3; i++) pt[i]->show();
  for(int i = 0; i < 3; i++) delete pt[i];

  return 0;
}
