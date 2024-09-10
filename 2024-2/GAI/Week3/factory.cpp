#include <iostream>
#include <list>
using namespace std;

class Pizza {
  protected:
    string name;
    string dough;
    string sauce;
    list<string> topping;
  public:
    Pizza(void) { }
    ~Pizza(void) { }

    void prepare() {
      cout << "준비중: " << name << endl;
      cout << "도우: " << dough << endl;
      cout << "소스: " << sauce << endl;
      cout << "토핑: ";
      for(list<string>::iterator it = topping.begin(); it != topping.end(); it++) {
        cout << *it << " ";
      }
      cout << endl;
    }

    void bake() { cout << "굽는 중: 25분, 350도" << endl; }
    void cut() { cout << "커팅 중" << endl; }
    void box() { cout << "포장 중" << endl; }
    string getName() const { return name; }
};

class PizzaNYOne : public Pizza {
  public:
    PizzaNYOne(void) {
      name = "맛있는 피자";
      dough = "일반";
      sauce = "토마토";
      topping.push_back("올리브");
      topping.push_back("스위트콘");
    }
    ~PizzaNYOne(void) { }
};

class PizzaNYTwo : public Pizza {
  public:
    PizzaNYTwo(void) {
      name = "게살피자";
      dough = "밀가루";
      sauce = "크림";
      topping.push_back("게살");
      topping.push_back("피망");
    }
    ~PizzaNYTwo(void) { }
};

class PizzaStore {
  public:
    PizzaStore(void) { }
    ~PizzaStore(void) { }

    Pizza* orderPizza(string type) {
      Pizza* pizza = createPizza(type);
      pizza->prepare();
      pizza->bake();
      pizza->cut();
      pizza->box();
      return pizza;
    }

    virtual Pizza* createPizza(string type) = 0;
};

class NYPizzaStore : public PizzaStore {
  public:
    NYPizzaStore(void) { }
    ~NYPizzaStore(void) { }

    Pizza* createPizza(string type) override {
      Pizza* pizza = nullptr;
      if(type == "one") {
        pizza = new PizzaNYOne();
      } else if(type == "two") {
        pizza = new PizzaNYTwo();
      }

      return pizza;
    }
};

int main() {
  PizzaStore* nyStore = new NYPizzaStore();
  Pizza* pizza1 = nyStore->orderPizza("one");
  cout << "주문한 피자: " << pizza1->getName() << endl << endl;

  Pizza* pizza2 = nyStore->orderPizza("two");
  cout << "주문한 피자: " << pizza2->getName() << endl << endl;

  return 0;
}
