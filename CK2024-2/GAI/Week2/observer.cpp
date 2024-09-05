#include <iostream>
#include <list>
using namespace std;

class IObserver {
  public:
    virtual void update(int num) = 0;
};

class ISubject {
  public:
    virtual void registerObserver(IObserver *obs) = 0;
    virtual void removeObserver(IObserver *obs) = 0;
    virtual void notifyObservers() = 0;
};

class ObserverA : public IObserver {
  public:
    ObserverA(ISubject *sub) {
      sub->registerObserver(this);
    }

    void update(int num) {
      cout << "Observer A received: " << num << endl;
    }
};

class ObserverB : public IObserver {
  public:
    ObserverB(ISubject *sub) {
      sub->registerObserver(this);
    }

    void update(int num) {
      cout << "Observer B received: " << num << endl;
    }
};

class SubjectA : public ISubject {
  private:
    list<IObserver *> observers;
    int num;

  public:
    SubjectA(): num(0) { }

    void setNumber(int num) {
      this->num = num;
      notifyObservers();
    }

    void registerObserver(IObserver *obs) override {
      observers.push_back(obs);
    }

    void removeObserver(IObserver *obs) override {
      observers.remove(obs);
    }

    void notifyObservers() override {
      for(auto obs : observers) {
        obs->update(num);
      }
    }
};

int main() {
  SubjectA *subjectA = new SubjectA();
  ObserverA *observerA = new ObserverA(subjectA);
  ObserverB *observerB = new ObserverB(subjectA);

  subjectA->setNumber(5);

  delete subjectA;
  delete observerA;
  delete observerB;
  return 0;
}
