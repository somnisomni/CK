// Provided by the lecture

#pragma once
#include "tile.h"

class gameMap
{
	tile** m_map;
	int m_width;
	int m_height;
	int m_mineNum;  // 지뢰의 갯수
	int m_openNum;  // 오픈한 타일 갯수
public:
	gameMap() {}
	gameMap(int w, int h) : m_width(w), m_height(h), m_mineNum(0), m_openNum(0) {
		m_map = new tile*[h];
		for (int i = 0; i < h; i++)
			m_map[i] = new tile[w];

		// tile 초기화
		for (int y = 0; y < h; y++) {
			for (int x = 0; x < w; x++) {
				m_map[y][x].initTile(x, y);
			}
		}
	}
	~gameMap() {
		for (int i = 0; i < m_height; i++)
			delete [] m_map[i];
		delete[] m_map;
	}  // 메모리 해제

	//getter
	int getWidth() { return m_width; }
	int getHeight() { return m_height; }
	int getMineNum() { return m_mineNum; }
	int getTileCount() { return m_width * m_height; }
	int getTileNum(int x, int y) { return m_map[y][x].getNum(); }

	//지뢰 설치
	void setMine(int mineNum);
	void updateTile(int mine_x, int mine_y);

	// tile open
	int openTile(int x, int y);
	void openAll();

	void draw();
};

