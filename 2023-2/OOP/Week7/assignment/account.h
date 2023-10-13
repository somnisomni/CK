#pragma once

#include <iostream>
#include <cstring>
#include <string>
using namespace std;

#define ACCOUNT_MAX 100

class Account {
  private:
    int accId;     // 계좌번호
    string regId;  // 주민번호
    char *name;   // 이름
    int balance;   // 잔액
  public:
    Account(int aId, string rId, char *n, int b): accId(aId), regId(rId), balance(b) {
      name = new char[strlen(n) + 1];
      strcpy(name, n);
    }
    Account(const Account& copy) {
      accId = copy.accId;
      regId = copy.regId;
      balance = copy.balance;

      name = new char[strlen(copy.name) + 1];
      strcpy(name, copy.name);
    }
    ~Account() {
      delete [] name;
    }

    /* Getters */
    int getAccId() const { return accId; }
    string getRegId() const { return regId; }
    char* getName() const { return name; }
    int getBalance() const { return balance; }

    /* Actions */
    static int generateRandomAccId() { return rand() % 90000 + 10000; }
    void deposit(int amount) { balance += amount; }
    bool withdraw(int amount) {
      if(balance < amount) return false;
      balance -= amount;
      return true;
    }
    void showAll() const {
      cout << "성함: " << name << endl;
      cout << "계좌번호: " << accId << endl;
      cout << "주민번호: " << regId << endl;
      cout << "잔액: " << balance << endl;
    }
};

class AccountManager {
  private:
    Account* accArr[ACCOUNT_MAX];
    int accNum = 0;
  public:
    AccountManager() { }
    ~AccountManager() {
      for (int i = 0; i < accNum; i++) {
        delete accArr[i];
      }
    }

    /* Getters */
    Account* getAccounts() const { return *accArr; }
    int getAccountNum() const { return accNum; }

    /* Actions */
    bool addAccount(Account* acc) {
      if(accNum >= ACCOUNT_MAX) {
        cout << "[!] 더 이상 계좌를 추가할 수 없습니다." << endl;
        return false;
      }

      accArr[accNum++] = acc;
      return true;
    }
    Account* findAccountByAccId(int accId) const {
      for(int i = 0; i < accNum; i++) {
        if(accArr[i]->getAccId() == accId) {
          return accArr[i];
        }
      }
      return NULL;
    }
    Account* findAccountByRegId(string regId) const {
      for(int i = 0; i < accNum; i++) {
        if(accArr[i]->getRegId() == regId) {
          return accArr[i];
        }
      }
      return NULL;
    }
    void showAll() const {
      if(accNum <= 0) {
        cout << "[!] 등록된 계좌가 없습니다." << endl;
        return;
      }

      for(int i = 0; i < accNum; i++) {
        accArr[i]->showAll();
        cout << endl;
      }
    }
    void showAllSimple() const {
      if(accNum <= 0) {
        cout << "[!] 등록된 계좌가 없습니다." << endl;
        return;
      }

      for (int i = 0; i < accNum; i++) {
        cout << "성함: " << accArr[i]->getName() << " / ";
        cout << "잔액: " << accArr[i]->getBalance() << endl;
        cout << endl;
      }
    }
};
