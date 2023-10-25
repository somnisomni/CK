#include <Windows.h>
#include <math.h>
#include <vector>
#include "resource.h"

#define BSIZE 40

double LengthPts(int x1, int y1, int x2, int y2) {
  return (sqrt((float)((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1))));
}

BOOL InCircle(int x, int y, int mx, int my) {
  if(LengthPts(x, y, mx, my) < BSIZE) return TRUE;
  else return FALSE;
}

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

HINSTANCE g_hInst;
LPCTSTR lpszClass = TEXT("Week9");

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int nCmdShow) {
  HWND hWnd;
  MSG Message;
  WNDCLASS WndClass;
  g_hInst = hInstance;
  WndClass.cbClsExtra = 0;
  WndClass.cbWndExtra = 0;
  WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
  WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
  WndClass.hIcon = LoadIcon(NULL, IDI_INFORMATION);
  WndClass.hInstance = hInstance;
  WndClass.lpfnWndProc = WndProc;
  WndClass.lpszClassName = lpszClass;
  WndClass.lpszMenuName = MAKEINTRESOURCE(IDR_MENU1);
  WndClass.style = CS_HREDRAW | CS_VREDRAW;
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

struct POS {
  int x;
  int y;
};

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam) {
  HDC hdc;
  PAINTSTRUCT ps;

  static HMENU hMenu, hSubMenu;
  static RECT rectView;
  static int curX, curY;
  static std::vector<POS> copies;
  static int targetX, targetY;
  static BOOL selection;
  static int selectionIdx = 0;
  static BOOL copy, copied;
  int mx, my;

  switch(iMessage) {
    case WM_CREATE:
      hMenu = GetMenu(hWnd);
      hSubMenu = GetSubMenu(hMenu, 1);

      selection = FALSE;
      copy = FALSE;

      copies.push_back({ 50, 50 });
      targetX = 50;
      targetY = 50;
      break;
    case WM_LBUTTONDOWN:
      mx = LOWORD(lParam);
      my = HIWORD(lParam);

      for(int i = copies.size() - 1; i >= 0; i--) {
        if(InCircle(copies[i].x, copies[i].y, mx, my)) {
          selection = TRUE;
          selectionIdx = i;
          targetX = copies[i].x;
          targetY = copies[i].y;

          InvalidateRect(hWnd, NULL, TRUE);
          return 0;
        }
      }

      selection = FALSE;
      copy = FALSE;
      InvalidateRect(hWnd, NULL, TRUE);
      break;
    case WM_RBUTTONDOWN:
      if(copy == TRUE) {
        targetX = LOWORD(lParam);
        targetY = HIWORD(lParam);
        InvalidateRect(hWnd, NULL, TRUE);
      }
      break;
    case WM_PAINT:
      EnableMenuItem(hSubMenu, ID_EDITCOPY, selection ? MF_ENABLED : MF_GRAYED);
      EnableMenuItem(hSubMenu, ID_EDITPASTE, copy ? MF_ENABLED : MF_GRAYED);

      hdc = BeginPaint(hWnd, &ps);

      for(int i = 0; i < copies.size(); i++) {
        if(selection && selectionIdx == i) Rectangle(hdc, copies[i].x - BSIZE, copies[i].y - BSIZE, copies[i].x + BSIZE, copies[i].y + BSIZE);
        Ellipse(hdc, copies[i].x - BSIZE, copies[i].y - BSIZE, copies[i].x + BSIZE, copies[i].y + BSIZE);
      }
      if(copy) Rectangle(hdc, targetX - 5, targetY - 5, targetX + 5, targetY + 5);

      EndPaint(hWnd, &ps);

      break;
    case WM_COMMAND:
      switch(LOWORD(wParam)) {
        case ID_EDITCOPY:
          copy = TRUE;
          InvalidateRect(hWnd, NULL, TRUE);
          break;
        case ID_EDITPASTE:
          copies.push_back({ targetX, targetY });
          selection = FALSE;
          copy = FALSE;
          InvalidateRect(hWnd, NULL, TRUE);
          break;
      }
      break;
    case WM_DESTROY:
      PostQuitMessage(0);
      break;
  }

  return (DefWindowProc(hWnd, iMessage, wParam, lParam));
}
