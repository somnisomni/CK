#include <iostream>
using namespace std;

class PlayGame {
  public:
    int gameMode;

    virtual ~PlayGame() { }
    virtual void setGameMode(const int gameMode) { this->gameMode = gameMode; }
    virtual void startGame() = 0;
    virtual void endGame() = 0;
};

class FPSPlayGame: public PlayGame {
  public:
    virtual void startGame() override {
      cout << "FPS startGame()" << endl;
    }
};

class RPGPlayGame: public PlayGame {
  public:
    virtual void startGame() override {
      cout << "RPG startGame()" << endl;
    }

    virtual void endGame() override {
      cout << "RPG endGame()" << endl;
    }
};

int main() {
  PlayGame *rpg = new RPGPlayGame();
  rpg->setGameMode(1);
  rpg->startGame();
  rpg->endGame();
  delete rpg;

  /* PlayGame *fps = new FPSPlayGame();   // compile error
  fps->setGameMode(2);
  fps->startGame();
  delete fps; */

  return 0;
}
