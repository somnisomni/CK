#include <Windows.h>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

HINSTANCE g_hInst;
LPCTSTR lpszClass = TEXT("Week7");

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int nCmdShow) {
  HWND hWnd;
  MSG Message;
  WNDCLASS WndClass;
  g_hInst = hInstance;
  WndClass.cbClsExtra = 0;
  WndClass.cbWndExtra = 0;
  WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
  WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
  WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
  WndClass.hInstance = hInstance;
  WndClass.lpfnWndProc = WndProc;
  WndClass.lpszClassName = lpszClass;
  WndClass.lpszMenuName = NULL;
  WndClass.style = CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;
  RegisterClass(&WndClass);

  hWnd = CreateWindow(lpszClass, lpszClass, WS_OVERLAPPEDWINDOW,
    CW_USEDEFAULT, CW_USEDEFAULT, 800, 400,
    NULL, (HMENU)NULL, hInstance, NULL);
  ShowWindow(hWnd, nCmdShow);

  while(GetMessage(&Message, NULL, 0, 0)) {
    TranslateMessage(&Message);
    DispatchMessage(&Message);
  }

  return (int)Message.wParam;
}

#define BOARD_ROW 4
#define BOARD_COLUMN 8

enum CellType {
  PLAYER = -1,
  EMPTY = 0,
  BARRIER = 1
};

enum Direction {
  LEFT,
  UP,
  RIGHT,
  DOWN
};

void FillCell(HDC hdc, int col, int row, int size, CellType type) {
  if(type == BARRIER) {
    HBRUSH oldBrush;
    HBRUSH barrierBrush = (HBRUSH)CreateSolidBrush(RGB(255, 128, 128));

    oldBrush = (HBRUSH)SelectObject(hdc, barrierBrush);
    Ellipse(hdc, col * size, row * size, col * size + size, row * size + size);
    SelectObject(hdc, oldBrush);

    DeleteObject(barrierBrush);
    DeleteObject(oldBrush);
  }
}

BOOL Move(CellType board[BOARD_ROW][BOARD_COLUMN], int playerCurCol, int playerCurRow, Direction dir) {
  switch(dir) {
    case LEFT:
      if(playerCurCol <= 0 ||  /* WALL - PLAYER */
        (playerCurCol == 1 && board[playerCurRow][playerCurCol - 1] != EMPTY) ||  /* WALL - BARRIER - PLAYER */
        (playerCurCol >= 2 && (board[playerCurRow][playerCurCol - 1] != EMPTY && board[playerCurRow][playerCurCol - 2] != EMPTY))) {  /* WALL - BARRIER - BARRIER - PLAYER */
        return FALSE;
      } else {
        board[playerCurRow][playerCurCol - 1] = EMPTY;
        board[playerCurRow][playerCurCol - 2] = BARRIER;
      }
  }

  return TRUE;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam) {
  HDC hdc;
  PAINTSTRUCT ps;
  static CellType SOKOBAN_BOARD[BOARD_ROW][BOARD_COLUMN];
  static int CELL_SIZE = 80;

  static HBRUSH PLAYER_BRUSH = (HBRUSH)CreateSolidBrush(RGB(128, 128, 255));
  static int PLAYER_ROW = 0;
  static int PLAYER_COLUMN = 0;

  HBRUSH oldBrush;
  int x, y, xCell, yCell;

  switch(iMessage) {
    case WM_CREATE:
      SOKOBAN_BOARD[2][2] = BARRIER;
      SOKOBAN_BOARD[3][1] = BARRIER;
      SOKOBAN_BOARD[1][6] = BARRIER;
      SOKOBAN_BOARD[2][7] = BARRIER;
      break;
    case WM_PAINT:
      hdc = BeginPaint(hWnd, &ps);

      // BOARD
      for(int y = 0; y < BOARD_ROW; y++) {
        for(int x = 0; x < BOARD_COLUMN; x++) {
          Rectangle(hdc,
            x * CELL_SIZE,
            y * CELL_SIZE,
            x * CELL_SIZE + CELL_SIZE,
            y * CELL_SIZE + CELL_SIZE);
          FillCell(hdc, x, y, CELL_SIZE, SOKOBAN_BOARD[y][x]);
        }
      }

      // PLAYER
      oldBrush = (HBRUSH)SelectObject(hdc, PLAYER_BRUSH);
      Ellipse(hdc, PLAYER_COLUMN * CELL_SIZE,
        PLAYER_ROW * CELL_SIZE,
        PLAYER_COLUMN * CELL_SIZE + CELL_SIZE,
        PLAYER_ROW * CELL_SIZE + CELL_SIZE);
      SelectObject(hdc, oldBrush);

      DeleteObject(oldBrush);
      EndPaint(hWnd, &ps);
      return 0;
    case WM_KEYDOWN:
      switch(wParam) {
        case VK_UP:
          if(PLAYER_ROW > 0 && Move(SOKOBAN_BOARD, PLAYER_COLUMN, PLAYER_ROW, UP))
            PLAYER_ROW -= 1;
          break;
        case VK_DOWN:
          if(PLAYER_ROW < BOARD_ROW - 1) PLAYER_ROW += 1;
          break;
        case VK_LEFT:
          if(PLAYER_COLUMN > 0) PLAYER_COLUMN -= 1;
          break;
        case VK_RIGHT:
          if(PLAYER_COLUMN < BOARD_COLUMN - 1) PLAYER_COLUMN += 1;
          break;
        case VK_OEM_PLUS:
          CELL_SIZE += 10;
          break;
        case VK_OEM_MINUS:
          if(CELL_SIZE > 10) CELL_SIZE -= 10;
          break;
      }
      InvalidateRect(hWnd, NULL, TRUE);
      break;
    case WM_LBUTTONDOWN:
      x = LOWORD(lParam);
      y = HIWORD(lParam);
      xCell = x / CELL_SIZE;
      yCell = y / CELL_SIZE;

      if(xCell < BOARD_COLUMN && yCell < BOARD_ROW) {
        hdc = GetDC(hWnd);
        Ellipse(hdc, xCell * CELL_SIZE, yCell * CELL_SIZE, xCell * CELL_SIZE + CELL_SIZE, yCell * CELL_SIZE + CELL_SIZE);
        ReleaseDC(hWnd, hdc);
      }

      return 0;
    case WM_DESTROY:
      DeleteObject(PLAYER_BRUSH);
      PostQuitMessage(0);
      return 0;
  }

  return (DefWindowProc(hWnd, iMessage, wParam, lParam));
}
