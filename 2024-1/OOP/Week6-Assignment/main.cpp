#include "bullet.h"
#include "bulletobjectpool.h"
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <vector>  // 테스트를 위해 사용
using namespace std;

int main() {
  srand((unsigned)time(NULL));

  BulletObjectPool pool(4);
  vector<Bullet*> tempBullets;

  string lastMessage = "";
  while(true) {
    system("cls");
    pool.printPool();

    cout << lastMessage << endl << endl;

    cout << "<< Menu >>" << endl;
    cout << "p. Pop random amount (1~10) of bullets" << endl;
    cout << "r. Reload All" << endl;
    cout << "e. Reload random amount (1~10)" << endl;
    cout << "q. Quit" << endl;
    cout << "  Choice: ";
    char choice;
    cin >> choice;

    switch(choice) {
      case 'q': {
        return 0;
      }
      case 'p': {
        int popCount = rand() % 10 + 1;

        bool hasError = false;
        string error = "";
        for(int i = 0; i < popCount; i++) {
          try {
            tempBullets.push_back(pool.pop());
          } catch(const char* msg) {
            hasError = true;
            error = string(msg);
            break;
          }
        }

        if(hasError) {
          lastMessage = "Error: " + error;
        } else {
          lastMessage = "Popped " + to_string(popCount) + " bullets";
        }

        break;
      }
      case 'r': {
        pool.pushAll();

        lastMessage = "Reloaded all bullets";

        break;
      }
      case 'e': {
        int reloadCount = rand() % 10 + 1;

        bool hasError = false;
        string error = "";
        for(int i = 0, t = reloadCount; i < t; i++) {
          try {
            if(!tempBullets.empty()) {
              pool.push(tempBullets.back());
              tempBullets.pop_back();
            } else {
              reloadCount--;
            }
          } catch(const char* msg) {
            hasError = true;
            error = string(msg);
            break;
          }
        }

        if(hasError) {
          lastMessage = "Error: " + error;
        } else {
          lastMessage = "Reloaded " + to_string(reloadCount) + " bullets";
        }

        break;
      }
    }
  }

  return 0;
}
