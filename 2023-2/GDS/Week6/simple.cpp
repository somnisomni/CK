#include <iostream>
#include <conio.h>
#include <cstdlib>
#include <ctime>
#include <thread>
#include "util.h"
using namespace std;

void printFunc() {
  ScreenPrint(10, 10, L"TESTPRINTTEST");
}

int main() {
  srand((unsigned)time(NULL));

  ScreenInit();

  while(true) {
    ScreenClear();

    this_thread::sleep_for(500ms);

    if(_kbhit()) {
      int nKey = _getch();
      switch(nKey) {
        case 'a':
          SetColor(rand() % 16);
          ScreenPrint(rand() % 80, rand() % 30, L"Hello");
          SetColor(rand() % 16);
          ScreenPrint(rand() % 80, rand() % 30, L"World");
          break;
      }
    }
    SetColor(rand() % 16);
    printFunc();

    ScreenFlipping();
  }

  ScreenRelease();
  return 0;
}
