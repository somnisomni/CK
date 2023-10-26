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

		std::wstring strMines = L"지뢰 갯수 : ";
		strMines.append(std::to_wstring(map.getMineNum()));
		ScreenPrint(2, map.getHeight() + 3, strMines.data());

		std::wstring strOpened = L"열린 타일 수 : ";
		strOpened.append(std::to_wstring(openTileNum));
		ScreenPrint(2, map.getHeight() + 4, strOpened.data());

		std::wstring strRemaining = L"남은 타일 수 : ";
		strRemaining.append(std::to_wstring(map.getTileCount() - map.getMineNum() - openTileNum));
		ScreenPrint(2, map.getHeight() + 5, strRemaining.data());


		if(openTileNum == -1) {
			// 지뢰
			ScreenPrint(2, map.getHeight() + 1, L"게임 오버!");
			bContinue = false;
		} else if(openTileNum == (map.getTileCount() - map.getMineNum())) {
			// 클리어
			ScreenPrint(2, map.getHeight() + 1, L"클리어!");
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