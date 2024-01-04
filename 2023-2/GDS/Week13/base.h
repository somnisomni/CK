#pragma once

struct Point {
  int x;
  int y;
};

struct Direction {
  short horizontal;
  short vertical;
};

enum TileType {
  BLANK,
  OBJECT,
  WALL,
  PATH,
};

const wchar_t *TILE_ICON[] = {
  L" ",
  L"��",
  L"��",
  L"*",
};

enum VisitType {
  NOT_VISITED,
  VISITED,
};
