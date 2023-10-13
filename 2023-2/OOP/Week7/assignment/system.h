#pragma once

#include <iostream>
#include <string>
#include <cstdlib>
#include "account.h"
using namespace std;

enum MainMenuSelection {
  EXIT = 0,
  CREATE_ACCOUNT = 1,
  DEPOSIT,
  WITHDRAW,
  SHOW_ALL
};

class AppMenu {
  public:
    static MainMenuSelection showMenu() {
      int selection;

      cout << endl;
      cout << "----- Menu -----" << endl;
      cout << "1. 계좌개설" << endl;
      cout << "2. 입금" << endl;
      cout << "3. 출금" << endl;
      cout << "4. 전체 고객 잔액 조회" << endl;
      cout << "0. 프로그램 종료" << endl;
      cout << "선택: ";
      cin >> selection;

      return static_cast<MainMenuSelection>(selection);
    }

    static Account* showCreateAccountMenu() {
      string name;
      string regId;
      int initialBalance;

      cout << "[ 계좌개설 ]" << endl;
      cout << "성함: ";
      cin >> name;
      cout << "주민번호 앞자리: ";
      cin >> regId;
      cout << "초기 입금액: ";
      cin >> initialBalance;

      return new Account(Account::generateRandomAccId(), regId, (char *) name.c_str(), initialBalance);
    }

    static bool showDepositMenu(AccountManager& am) {
      if(am.getAccountNum() == 0) {
        cout << "[!] 입금할 수 있는 계좌가 존재하지 않습니다." << endl;
        return false;
      }

      string regId;
      int amount;

      cout << "[ 입금 ]" << endl;
      cout << "주민번호: ";
      cin >> regId;

      Account* acc = am.findAccountByRegId(regId);
      if(!acc) {
        cout << "[!] 해당 고객이 존재하지 않습니다." << endl;
        return false;
      }

      cout << acc->getName() << "님, ";
      cout << "입금하실 금액: ";
      cin >> amount;

      acc->deposit(amount);

      cout << "입금이 완료되었습니다." << endl;
      cout << acc->getName() << "님의 현재 잔액은 " << acc->getBalance() << "원 입니다." << endl;
      return true;
    }

    static bool showWithdrawMenu(AccountManager& am) {
      if(am.getAccountNum() == 0) {
        cout << "[!] 출금할 수 있는 계좌가 존재하지 않습니다." << endl;
        return false;
      }

      string regId;
      int amount;

      cout << "[ 출금 ]" << endl;
      cout << "주민번호: ";
      cin >> regId;

      Account* acc = am.findAccountByRegId(regId);
      if(!acc) {
        cout << "[!] 해당 고객이 존재하지 않습니다." << endl;
        return false;
      }

      cout << acc->getName() << "님, ";
      cout << "출금하실 금액: ";
      cin >> amount;

      if(!acc->withdraw(amount)) {
        cout << "[!] 잔액이 부족합니다." << endl;
        return false;
      }

      cout << "출금이 완료되었습니다." << endl;
      cout << acc->getName() << "님의 현재 잔액은 " << acc->getBalance() << "원 입니다." << endl;
      return true;
    }

    static void showAllInfoMenu(AccountManager& am) {
      cout << "[ 전체 고객 잔액 조회 ]" << endl;
      am.showAllSimple();
      cout << endl;
    }
};
