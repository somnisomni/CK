#include "tile.h"
#include "util.h"

void tile::draw() {
  static const wchar_t *tileImg[] = {
    L"○", L"①", L"②", L"③", L"④", L"⑤", L"⑥", L"⑦", L"⑧",
    L"★", L"□"
  };

  if(m_bOpen) {
    ScreenPrint(m_x, m_y, tileImg[m_num]);
  } else {
    ScreenPrint(m_x, m_y, tileImg[10]);
  }
}
