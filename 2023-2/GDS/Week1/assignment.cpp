#include <iostream>
#include <string>
#include <stdlib.h>
#include <time.h>
using namespace std;

enum Choice {
	ROCK = 1,
	PAPER = 2,
	SCISSORS = 0
};

enum Result {
	WIN,
	LOSE,
	DRAW,
	UNKNOWN
};

struct Player {
	Choice choice;
};

struct Computer {
	Choice choice;
};

struct Referee {
	Player player;
	Computer computer;
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

void computerRandomPick(Computer &computer) {
	computer.choice = static_cast<Choice>(rand() % 3);

	cout << "컴퓨터 선택 완료!" << endl;
}

void playerPick(Player &player) {
	int choice = -1;

	while(true) {
		cout << "플레이어 선택 (0: 가위, 1: 바위, 2: 보): ";
		cin >> choice;

		if(choice < 0 || choice > 2) {
			cout << "선택지 내에서 입력해주세요." << endl;
			continue;
		}

		break;
	}

	player.choice = static_cast<Choice>(choice);
}

Result process(const Referee referee) {
	if(referee.player.choice == referee.computer.choice)
		return DRAW;

	switch(referee.player.choice) {
		case ROCK:
			switch(referee.computer.choice) {
				case PAPER:
					return LOSE;
					break;
				case SCISSORS:
					return WIN;
					break;
			}
			break;

		case PAPER:
			switch(referee.computer.choice) {
				case ROCK:
					return WIN;
					break;
				case SCISSORS:
					return LOSE;
					break;
			}
			break;

		case SCISSORS:
			switch(referee.computer.choice) {
				case ROCK:
					return LOSE;
					break;
				case PAPER:
					return WIN;
					break;
			}
			break;
	}

	return UNKNOWN;
}

void gameMain() {
	Referee referee;
	Result result;

	cout << "=== 가위바위보 ===" << endl;
	computerRandomPick(referee.computer);
	playerPick(referee.player);

	result = process(referee);

	cout << ">> ";
	switch(result) {
		case WIN:
			cout << "승리!";
			break;
		case LOSE:
			cout << "패배!";
			break;
		case DRAW:
			cout << "무승부!";
			break;
	}
	cout << " <<  컴퓨터 선택: " << choiceToString(referee.computer.choice) << endl;
}

int main() {
	srand((unsigned) time(NULL));

	gameMain();

	return 0;
}
