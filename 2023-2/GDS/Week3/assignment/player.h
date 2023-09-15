#pragma once
#include <iostream>
#include <string>
#include <cstdlib>
using namespace std;

enum Choice {
  ROCK = 1,
  PAPER = 2,
  SCISSORS = 0
};

string choiceToString(Choice choice) {
  switch(choice) {
    case ROCK:
      return "바위";
      break;
    case PAPER:
      return "보";
      break;
    case SCISSORS:
      return "가위";
      break;
  }

  return "알 수 없음";
}

class Player {
  protected:
    string name;
    Choice choice;
  public:
    Player(string n): name(n) { };
    Player(string n, Choice c): name(n), choice(c) { }

    string getName() { return name; }
    Choice getChoice() { return choice; }

    virtual void pick() { };
};

class HumanPlayer: public Player {
  public:
    HumanPlayer(string n): Player(n) { }
    void pick() override {
      int c = -1;

      while(!(c >= 0 && c <= 2)) {
        cout << "선택 (0: 가위, 1: 바위, 2: 보): ";
        cin >> c;

        if(!(c >= 0 && c <= 2)) {
          cout << "잘못된 입력입니다." << endl;
          continue;
        }
      }

      choice = static_cast<Choice>(c);
    }
};

class ComputerPlayer: public Player {
  public:
    ComputerPlayer(string n): Player(n) {
      srand((unsigned) time(NULL));
      pick();
    }

    void pick() override {
      choice = static_cast<Choice>(rand() % 3);
    }
};
