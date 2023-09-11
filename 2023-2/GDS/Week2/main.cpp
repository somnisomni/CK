#include <iostream>
#include <string>
#include "./player.h"
#include "./computer.h"
#include "./referee.h"

int main() {
  Player player("금쪽이");
  Computer computer("컴퓨터");
  Referee referee(&player, &computer);

  player.play();
  computer.play();
  referee.checkWinner();
  referee.draw();

  return 0;
}
