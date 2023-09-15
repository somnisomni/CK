#include <iostream>
#include <string>
#include "./player.h"
#include "./referee.h"
using namespace std;

void gameMain() {
	HumanPlayer *player = new HumanPlayer("플레이어");
	ComputerPlayer *computer = new ComputerPlayer("컴퓨터");
	Referee referee(player, computer);

	referee.play();
	Player *winner = referee.getWinner();

	cout << endl;
	if(winner == NULL) {
		cout << "  ## 무승부! ##" << endl;
	} else {
		cout << "  ## '" << winner->getName() << "' 승리! ##" << endl;
	}

	cout << endl;
	cout << "  * 플레이어 선택: " << choiceToString(player->getChoice()) << endl;
	cout << "  * 컴퓨터 선택: " << choiceToString(computer->getChoice()) << endl;

	delete player;
	delete computer;
}

int main() {
	srand((unsigned) time(NULL));

	gameMain();

	return 0;
}
