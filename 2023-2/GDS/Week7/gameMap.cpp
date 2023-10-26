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
	if(x < 0 || x > m_width - 1 || y < 0 || y > m_height - 1) return -2;

	tile &curTile = m_map[y][x];

	if(curTile.isOpened()) return -2;

	// Mine
	if(curTile.getNum() == MINE) {
		openAll();
		return -1;
	}

	if(curTile.isOpened() == false) curTile.setOpen(true);

	if(curTile.getNum() != ZERO) {
		m_openNum++;
		return m_openNum;
	} else {
		m_openNum++;
		for(int ty = y - 1; ty <= y + 1; ty++) {
			for(int tx = x - 1; tx <= x + 1; tx++) {
				openTile(tx, ty);
			}
		}
	}

	return m_openNum;
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
