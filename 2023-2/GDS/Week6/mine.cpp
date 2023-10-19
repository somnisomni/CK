#include "gameMap.h"
#include "player.h"
#include "util.h"
#include <conio.h>

int main()
{
	gameMap map(20, 20);
	map.setMine(20);

	Player player;

	ScreenInit();

	bool bContinue = true;
	while(bContinue) {
		ScreenClear();

		map.draw();
		player.draw();

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
					map.openAll();
					break;
			}
		}
	}

	ScreenRelease();
	return 0;
}