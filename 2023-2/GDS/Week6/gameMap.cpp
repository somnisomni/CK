// Provided by the lecture

#include "gameMap.h"
#include <iostream>
using namespace std;

void gameMap::setMine(int mineNum)
{
	m_mineNum = mineNum;
	
	for (int i = 0; i < mineNum; i++) {
		int x, y;
		do {
			x = rand() % m_width;
			y = rand() % m_height;
		} while (m_map[y][x].getNum() == MINE);
		updateTile(x, y);
	}
}

void gameMap::updateTile(int mine_x, int mine_y)
{
	// 지뢰위치(mine_x, mine_y)를 기준으로 8방향 타일의 값을 수정
	for (int curY = mine_y - 1; curY <= mine_y + 1; curY++) {
		for (int curX = mine_x - 1; curX <= mine_x + 1; curX++) {
			// 맵의 범위 검사
			if (curX < 0 || curX > m_width - 1 || curY < 0 || curY > m_height - 1)
				continue;
			if(curX == mine_x && curY == mine_y)
				m_map[curY][curX].setNum(MINE);
			else {
				int num = m_map[curY][curX].getNum();
				if(num != MINE)
					m_map[curY][curX].setNum(num + 1);
			}
		}
	}

}

int gameMap::openTile(int x, int y) {
	m_map[y][x].setOpen(true);
	return m_map[y][x].getNum();
}

void gameMap::openAll() {
	for(int y = 0; y < m_height; y++) {
		for(int x = 0; x < m_width; x++) {
			m_map[y][x].setOpen(true);
		}
	}
}

void gameMap::draw()
{
	for (int y = 0; y < m_height; y++) {
		for (int x = 0; x < m_width; x++) {
			m_map[y][x].draw();
		}
		cout << endl;
	}
}
