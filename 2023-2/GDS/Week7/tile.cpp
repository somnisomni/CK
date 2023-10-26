#include "tile.h"
#include "util.h"

void tile::draw() {
  static const wchar_t *tileImg[] = {
    L"·", L"1", L"2", L"3", L"4", L"5", L"6", L"7", L"8",
    L"★", L"■"
  };

  if(m_bOpen) {
    ScreenPrint(m_x, m_y, tileImg[m_num]);
  } else {
    ScreenPrint(m_x, m_y, tileImg[10]);
  }
}
