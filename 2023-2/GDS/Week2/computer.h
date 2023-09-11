#pragma once

#include <iostream>
#include <string>
#include <stdlib.h>
#include <time.h>
using namespace std;

struct Computer {
  int value;
  string name;

  Computer(string n): name(n), value(-1) { /* name = n; */ }

  void play() {
    srand((unsigned) time(NULL));

    value = rand() % 3;
  }

  void draw() {
    string valueNames[3] = {"가위", "바위", "보"};

    cout << "플레이어 이름: " << name << endl;
    cout << "값: " << valueNames[value] << endl;
  }
};
