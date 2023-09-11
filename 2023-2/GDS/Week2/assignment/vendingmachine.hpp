#include <iostream>
#include <string>
#include <cstdlib>
using namespace std;

#define MAX_PRODUCT_COUNT 9

/* == Product == */
struct Product {
  int price;
  string name;
};

/* == ProductProcessor == */
struct ProductProcessor {
  Product *products[MAX_PRODUCT_COUNT];
  int productCount = 0;

  void addProduct(Product *product);
  ~ProductProcessor() {
    for(int i = 0; i < productCount; i++) {
      delete products[i];
    }
  }
};

void ProductProcessor::addProduct(Product *product) {
  if(productCount >= MAX_PRODUCT_COUNT) {
    cout << "등록 가능한 제품 개수 초과" << endl;
    return;
  }

  products[productCount++] = product;
}

/* == MoneyProcessor == */
struct MoneyProcessor {
  int money = 0;

  void insert(int amount) { money += amount; }
  bool use(int amount);
  int refund() { int temp = money; money = 0; return temp; }
};

bool MoneyProcessor::use(int amount) {
  if(money < amount) return false;

  money -= amount;
  return true;
}

/* == VendingMachine == */
struct VendingMachine {
  ProductProcessor *productProc;
  MoneyProcessor *moneyProc;

  void displayMenu();
  void displayOptions();
  bool processInput(char input);
  void loop();
  ~VendingMachine();
};

void VendingMachine::displayMenu() {
  cout << " ====================" << endl;
  cout << " ===== 자 판 기 =====" << endl;
  cout << " ====================" << endl;
  cout << " 현재 투입 금액: " << moneyProc->money << "원" << endl;
  cout << endl;
  cout << " ** 메뉴 **" << endl;
  for(int i = 0; i < productProc->productCount; i++) {
    cout << " " << i + 1 << ". ";
    cout << productProc->products[i]->name;
    cout << " (" << productProc->products[i]->price << "원)" << endl;
  }
  cout << endl;
}

void VendingMachine::displayOptions() {
  cout << " ** 명령 **" << endl;
  cout << " a. 100원 투입" << endl;
  cout << " b. 500원 투입" << endl;
  cout << " c. 전액 반환" << endl;
  cout << " q. 종료" << endl;
  cout << endl;
}

bool VendingMachine::processInput(char input) {
  system("cls");  // only for Windows

  if(input >= '1' && input <= '9') {
    int prodIndex = (input - '0') - 1;
    if(prodIndex >= productProc->productCount) {
      cout << "존재하지 않는 상품입니다." << endl;
      return true;
    }

    Product &target = *(productProc->products[prodIndex]);

    cout << target.name << " 구매 중..." << endl;
    if(moneyProc->use(target.price)) {
      cout << "[O] " << target.name << " 구매 완료!" << endl;
    } else {
      cout << "[X] 잔액이 부족합니다." << endl;
    }
  } else if(input == 'a') {
    moneyProc->insert(100);
    cout << "100원 투입 완료!" << endl;
  } else if(input == 'b') {
    moneyProc->insert(500);
    cout << "500원 투입 완료!" << endl;
  } else if(input == 'c') {
    int refund = moneyProc->refund();
    cout << "전액 반환 완료! (반환 금액: " << refund << "원)" << endl;
  } else if(input == 'q') {
    cout << "자판기를 종료합니다." << endl;
    return false;
  } else {
    cout << "잘못된 명령입니다." << endl;
  }

  cout << endl;
  cout << "계속하려면 아무 키나 누르세요...";
  cin.get();
  cin.get(); // workaround...?

  return true;
}

void VendingMachine::loop() {
  char input;

  do {
    system("cls");  // only for Windows

    displayMenu();
    displayOptions();

    cout << " 명령 입력: ";
    cin >> input;
  } while(processInput(input));
}

VendingMachine::~VendingMachine() {
  delete productProc;
  delete moneyProc;
}
