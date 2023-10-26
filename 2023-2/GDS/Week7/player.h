#pragma once

class Player {
  private:
    int m_x;
    int m_y;
  public:
    Player(int x = 5, int y = 5): m_x(x), m_y(y) { }
    ~Player() { }

    // Getters
    int getX() const { return m_x; }
    int getY() const { return m_y; }

    // Setter
    void setXY(const int x, const int y) { m_x = x; m_y = y; }

    // Actions
    void up() { m_y--; }
    void down() { m_y++; }
    void left() { m_x--; }
    void right() { m_x++; }

    void draw();
};
