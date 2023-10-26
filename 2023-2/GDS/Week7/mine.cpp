#include "gameMap.h"
#include "player.h"
#include "util.h"
#include <cstdlib>
#include <ctime>
#include <string>
#include <conio.h>

int main()
{
	srand((unsigned)time(NULL));

	gameMap map(20, 20);
	map.setMine(20);

	Player player;

	ScreenInit();

	int openTileNum = 0;
	bool bContinue = true;
	while(bContinue) {
		ScreenClear();

		map.draw();
		player.draw();

		std::wstring strMines = L"���� ���� : ";
		strMines.append(std::to_wstring(map.getMineNum()));
		ScreenPrint(2, map.getHeight() + 3, strMines.data());

		std::wstring strOpened = L"���� Ÿ�� �� : ";
		strOpened.append(std::to_wstring(openTileNum));
		ScreenPrint(2, map.getHeight() + 4, strOpened.data());

		std::wstring strRemaining = L"���� Ÿ�� �� : ";
		strRemaining.append(std::to_wstring(map.getTileCount() - map.getMineNum() - openTileNum));
		ScreenPrint(2, map.getHeight() + 5, strRemaining.data());


		if(openTileNum == -1) {
			// ����
			ScreenPrint(2, map.getHeight() + 1, L"���� ����!");
			bContinue = false;
		} else if(openTileNum == (map.getTileCount() - map.getMineNum())) {
			// Ŭ����
			ScreenPrint(2, map.getHeight() + 1, L"Ŭ����!");
			bContinue = false;
		}

		ScreenFlipping();

		int curX;
		int curY;
		if(_kbhit()) {
			int key = _getch();
			curX = player.getX();
			curY = player.getY();
			
			switch(key) {
				case UP:
					if(curY - 1 >= 0) player.up();
					break;
				case DOWN:
					if(curY + 1 < map.getHeight()) player.down();
					break;
				case LEFT:
					if(curX - 1 >= 0) player.left();
					break;
				case RIGHT:
					if(curX + 1 < map.getWidth()) player.right();
					break;
				case SPACE:
					openTileNum = map.openTile(curX, curY);
					break;
			}
		}
	}

	_getch();
	ScreenRelease();
	return 0;
}