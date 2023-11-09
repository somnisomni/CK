#include <iostream>
#include <string>
using namespace std;

class HomeAppliance {
  protected:
    string modelName;
    int price;
    string color;
    HomeAppliance(string modelName, int price, string color): modelName(modelName), price(price), color(color) { }

  public:
    virtual ~HomeAppliance() { }
    virtual void show() const = 0;
};

class Refrigerator: public HomeAppliance {
  private:
    int capacity;
  public:
    Refrigerator(string modelName, int price, string color, int capacity): HomeAppliance(modelName, price, color), capacity(capacity) { }
    virtual ~Refrigerator() { }
    virtual void show() const {
      cout << " === 냉장고 === " << endl;
      cout << "모델명: " << modelName << endl;
      cout << "가격  : " << price << endl;
      cout << "색상  : " << color << endl;
      cout << "용량  : " << capacity << endl;
    }
};

class Washer: public HomeAppliance {
  private:
    float capacity;
  public:
    Washer(string modelName, int price, string color, float capacity): HomeAppliance(modelName, price, color), capacity(capacity) { }
    virtual ~Washer() { }
    virtual void show() const {
      cout << " === 세탁기 === " << endl;
      cout << "모델명: " << modelName << endl;
      cout << "가격  : " << price << endl;
      cout << "색상  : " << color << endl;
      cout << "용량  : " << capacity << endl;
    }
};

class Humidifier: public HomeAppliance {
  private:
    bool automatic;
  public:
    Humidifier(string modelName, int price, string color, bool automatic): HomeAppliance(modelName, price, color), automatic(automatic) { }
    virtual ~Humidifier() { }
    virtual void show() const {
      cout << " === 가습기 === " << endl;
      cout << "모델명: " << modelName << endl;
      cout << "가격  : " << price << endl;
      cout << "색상  : " << color << endl;
      cout << "자동  : " << (automatic ? "O" : "X") << endl;
    }
};

int main() {
  HomeAppliance *apps[3] = {
    new Refrigerator("LG DIOS", 2000000, "White", 125),
    new Washer("Samsung Grande", 760000, "Black", 7.6f),
    new Humidifier("Xiaomi Smart Humidifier", 125000, "White", true)
  };

  for(int i = 0; i < 3; i++) {
    apps[i]->show();
    cout << endl;
  }

  for(int i = 0; i < 3; i++) delete apps[i];
  return 0;
}
