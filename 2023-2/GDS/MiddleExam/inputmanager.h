#pragma once
#include <conio.h>
#include "util.h"

class InputManager {
  private:
    static InputManager *_instance;
    char lastInput;

    InputManager(): lastInput(NULL) { }
    ~InputManager() { if(_instance) delete _instance; }
  public:
    static InputManager *getInstance() {
      if(_instance == nullptr) {
        _instance = new InputManager();
      }

      return _instance;
    }

    char popLastInput() {
      char tmp = lastInput;
      lastInput = NULL;
      return tmp;
    }

    void update() {
      if(_kbhit()) {
        lastInput = _getch();
      }
    }
};
