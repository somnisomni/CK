#include <iostream>
#include <cstring>
using namespace std;

class InvalidDepositMoneyException {
  private:
    int amount;
  public:
    InvalidDepositMoneyException(int amount): amount(amount) { }

    string message() const {
      return "입금액이 유효하지 않습니다. (요청 금액: " + to_string(amount) + "원)";
    }
};

class Account {
  private:
    char accNum[50];
    int balance;
  public:
    Account(const char* acc, int money): balance(money) {
      strncpy(accNum, acc, strnlen(acc, 50) + 1);
    }

    void deposit(int money) {
      try {
        if(money < 0) throw InvalidDepositMoneyException(money);

        balance += money;
      } catch(InvalidDepositMoneyException& e) {
        cout << e.message() << endl;
        return;
      }
    }

    int getBalance() const { return balance; }
};

int main() {
  Account acc("1234-1234", 10000);
  acc.deposit(2000);
  acc.deposit(-100);
  cout << "잔액: " << acc.getBalance() << "원" << endl;

  return 0;
}
