#include <iostream>
#include <cstdlib>
#include <ctime>
#include "account.h"
#include "system.h"
using namespace std;

int main() {
  srand((unsigned) time(NULL));

  AccountManager manager = AccountManager();

  while(true) {
    MainMenuSelection s = AppMenu::showMenu();
    cout << endl;

    switch(s) {
      case CREATE_ACCOUNT:
        if(manager.addAccount(AppMenu::showCreateAccountMenu())) {
          cout << "[*] 계좌가 개설되었습니다." << endl;
        }
        break;
      case DEPOSIT:
        AppMenu::showDepositMenu(manager);
        break;
      case WITHDRAW:
        AppMenu::showWithdrawMenu(manager);
        break;
      case SHOW_ALL:
        AppMenu::showAllInfoMenu(manager);
        break;
      case EXIT:
        return 0;
      default:
        cout << "[!] 잘못된 입력입니다." << endl;
        cout << endl;
    }
  }

  cout << "[*] 종료" << endl;
  return 0;
}
