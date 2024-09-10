#include <iostream>
using namespace std;

class IPerson {
  public:
    virtual void drawStyle() = 0;
};

class IDecorator : public IPerson {
  public:
    virtual void drawStyle() = 0;
};

class Boy : public IPerson {
  private:
    string name;
  public:
    Boy(string name): name(name) { }
    void drawStyle() {
      cout << "이름: " << name << endl;
      cout << "착용: 청바지, T셔츠" << endl;
    }
};

class Girl : public IPerson {
  private:
    string name;
  public:
    Girl(string name): name(name) { }
    void drawStyle() {
      cout << "이름: " << name << endl;
      cout << "착용: 원피스" << endl;
    }
};

class Hat : public IDecorator {
  private:
    IPerson* person;
  public:
    Hat(IPerson* person): person(person) { }
    void drawStyle() {
      person->drawStyle();
      cout << "모자 착용" << endl;
    }
};

class Globe : public IDecorator {
  private:
    IPerson* person;
  public:
    Globe(IPerson* person): person(person) { }
    void drawStyle() {
      person->drawStyle();
      cout << "장갑 착용" << endl;
    }
};

int main() {
  IPerson* boy = new Boy("홍길동");
  boy = new Hat(boy);
  boy->drawStyle();

  IPerson* girl = new Globe(new Hat(new Girl("홍길순")));
  girl->drawStyle();

  return 0;
}
