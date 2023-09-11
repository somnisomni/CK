#pragma once

#include <iostream>
#include <string>
using namespace std;

struct Player {
  int value;
  string name;

  Player(string n): name(n), value(-1) { /* name = n; */ }

  void play() {
    cout << "0 - 가위 / 1 - 바위 / 2 - 보 (0 ~ 2): ";
    cin >> value;
  }

  void draw() {
    string valueNames[3] = {"가위", "바위", "보"};

    cout << "플레이어 이름: " << name << endl;
    cout << "값: " << valueNames[value] << endl;
  }
};
