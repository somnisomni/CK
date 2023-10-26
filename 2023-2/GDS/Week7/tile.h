// Provided by the lecture

#pragma once

enum TileType { ZERO, ONE, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, MINE};

class tile {
	int m_num;   // ¼¿ °ª  -1 : Áö·Ú , 0 ~ 8
	bool m_bOpen;
	int m_x;
	int m_y;
public:
	tile() {}
	tile(int x, int y) : m_x(x), m_y(y), m_num(0), m_bOpen(false) {}
	~tile() {}

	void initTile(int x, int y) {
		m_x = x;
		m_y = y;
		m_num = 0;
		m_bOpen = false;
	}

	//getter
	int getNum() { return m_num; }
	int getX() { return m_x; }
	int getY() { return m_y;	}
	bool isOpened() { return m_bOpen; }

	//setter
	void setNum(int n) { m_num = n; }
	void setOpen(bool o) { m_bOpen = o; }
	void setXY(int x, int y) { m_x = x; m_y = y; }

	void draw();
};

