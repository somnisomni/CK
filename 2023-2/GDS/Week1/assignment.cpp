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
			return "����";
			break;
		case PAPER:
			return "��";
			break;
		case SCISSORS:
			return "����";
			break;
	}

	return "�� �� ����";
}

void computerRandomPick(Computer &computer) {
	computer.choice = static_cast<Choice>(rand() % 3);

	cout << "��ǻ�� ���� �Ϸ�!" << endl;
}

void playerPick(Player &player) {
	int choice = -1;

	while(true) {
		cout << "�÷��̾� ���� (0: ����, 1: ����, 2: ��): ";
		cin >> choice;

		if(choice < 0 || choice > 2) {
			cout << "������ ������ �Է����ּ���." << endl;
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

	cout << "=== ���������� ===" << endl;
	computerRandomPick(referee.computer);
	playerPick(referee.player);

	result = process(referee);

	cout << ">> ";
	switch(result) {
		case WIN:
			cout << "�¸�!";
			break;
		case LOSE:
			cout << "�й�!";
			break;
		case DRAW:
			cout << "���º�!";
			break;
	}
	cout << " <<  ��ǻ�� ����: " << choiceToString(referee.computer.choice) << endl;
}

int main() {
	srand((unsigned) time(NULL));

	gameMain();

	return 0;
}
