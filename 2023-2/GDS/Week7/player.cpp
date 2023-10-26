#include "player.h"
#include "util.h"

void Player::draw() {
  const wchar_t *playerImg = L"¢¾";

  SetColor(4);
  ScreenPrint(m_x, m_y, playerImg);
  SetColor(15);
}
