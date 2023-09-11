#pragma once

#include <iostream>
#include <string>
#include "./player.h"
#include "./computer.h"
using namespace std;

struct Referee {
  string winner;
  Player *player;
  Computer *computer;

  Referee(Player *p, Computer *c): player(p), computer(c) { /* player = p; computer = c; */ }

  void checkWinner();
  void draw() {
    player->draw();
    computer->draw();
    cout << "결과: " << winner << endl;
  }
};

void Referee::checkWinner() {
  switch(player->value) {
    case 0:
      switch(computer->value) {
        case 0:
          winner = "무승부";
          break;
        case 1:
          winner = "컴퓨터 승";
          break;
        case 2:
          winner = "플레이어 승";
          break;
      }
      break;
    case 1:
      switch(computer->value) {
        case 0:
          winner = "플레이어 승";
          break;
        case 1:
          winner = "무승부";
          break;
        case 2:
          winner = "컴퓨터 승";
          break;
      }
      break;
    case 2:
      switch(computer->value) {
        case 0:
          winner = "컴퓨터 승";
          break;
        case 1:
          winner = "플레이어 승";
          break;
        case 2:
          winner = "무승부";
          break;
      }
      break;
  }
}
