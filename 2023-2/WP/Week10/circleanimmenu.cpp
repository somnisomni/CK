#include <Windows.h>
#include "resource.h"

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

HINSTANCE g_hInst;
LPCTSTR lpszClass = TEXT("Week10");

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
  WndClass.lpszMenuName = MAKEINTRESOURCE(IDR_MENU2);
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

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam) {
  HDC hdc;
  PAINTSTRUCT ps;

  static int centerX, centerY, radius = 50, step = 5;
  static HMENU menu = GetMenu(hWnd);
  static HMENU submenu = GetSubMenu(menu, 0);
  static BOOL started = FALSE;
  static BOOL startedOnce = FALSE;
  static int animTimerId = 0;

  RECT windowRect;

  switch(iMessage) {
    case WM_CREATE:
      GetClientRect(hWnd, &windowRect);
      centerX = radius;
      centerY = windowRect.bottom - radius;

      break;
    case WM_COMMAND:
      switch(LOWORD(wParam)) {
        case ID_CIRCLEANIM_START:
          SetTimer(hWnd, animTimerId, 1000 / 60, NULL);
          started = TRUE;
          startedOnce = TRUE;
          break;
        case ID_CIRCLEANIM_STOP:
          KillTimer(hWnd, animTimerId);
          started = FALSE;
          break;
        case ID_CIRCLEANIM_RESET:
          KillTimer(hWnd, animTimerId);
          GetClientRect(hWnd, &windowRect);
          centerX = radius;
          centerY = windowRect.bottom - radius;
          started = FALSE;
          startedOnce = FALSE;
          break;
      }

      InvalidateRect(hWnd, NULL, TRUE);
      break;
    case WM_PAINT:
      EnableMenuItem(submenu, ID_CIRCLEANIM_START, started ? MF_GRAYED : MF_ENABLED);
      EnableMenuItem(submenu, ID_CIRCLEANIM_STOP, started ? MF_ENABLED : MF_GRAYED);
      EnableMenuItem(submenu, ID_CIRCLEANIM_RESET, startedOnce ? MF_ENABLED : MF_GRAYED);

      hdc = BeginPaint(hWnd, &ps);

      Ellipse(hdc, centerX - radius, centerY - radius, centerX + radius, centerY + radius);

      EndPaint(hWnd, &ps);
      break;
    case WM_TIMER:
      if(started) {
        GetClientRect(hWnd, &windowRect);

        centerX += step;

        if(centerX + radius > windowRect.right || centerX - radius < windowRect.left) {
          centerX -= step;
          step = -step;
        }
      }

      InvalidateRect(hWnd, NULL, TRUE);
      break;
    case WM_DESTROY:
      PostQuitMessage(0);
      break;
  }

  return (DefWindowProc(hWnd, iMessage, wParam, lParam));
}
