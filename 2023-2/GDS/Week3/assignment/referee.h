#pragma once
#include "./player.h"

class Referee {
  private:
    Player *players[2];
  public:
    Referee(Player *p1, Player *p2) {
      players[0] = p1;
      players[1] = p2;
    }

    void play() {
      cout << "=== 가위바위보 ===" << endl;
      players[0]->pick();
      players[1]->pick();
    }
    Player* getWinner() {
      Choice p1Choice = players[0]->getChoice();
      Choice p2Choice = players[1]->getChoice();

      switch(p1Choice) {
        case ROCK:
          switch(p2Choice) {
            case PAPER:
              return players[1];
              break;
            case SCISSORS:
              return players[0];
              break;
          }
          break;

        case PAPER:
          switch(p2Choice) {
            case ROCK:
              return players[0];
              break;
            case SCISSORS:
              return players[1];
              break;
          }
          break;

        case SCISSORS:
          switch(p2Choice) {
            case ROCK:
              return players[1];
              break;
            case PAPER:
              return players[0];
              break;
          }
          break;
      }

      return NULL;  // p1Choice == p2Choice
    }
};
