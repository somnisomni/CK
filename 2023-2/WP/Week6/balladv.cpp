#include <Windows.h>
#include <cstdlib>
#include <ctime>

enum Direction {
  LEFT, RIGHT, UP, DOWN
};

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

HINSTANCE g_hInst;
LPCTSTR lpszClass = TEXT("Week6");

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int nCmdShow) {
  srand((unsigned)time(NULL));

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
  RECT clientRect;
  HBRUSH randColorBrush;
  HBRUSH oldBrush;

  static int randR = rand() % 256;
  static int randG = rand() % 256;
  static int randB = rand() % 256;

  static int xpos = 50;
  static int ypos = 100;
  static int radius = 50;
  static int step = 5;

  static bool start = false;
  static Direction dir = RIGHT;

  switch(iMessage) {
    case WM_CREATE:
      GetClientRect(hWnd, &clientRect);
      ypos = clientRect.bottom - radius;
      xpos = radius;
      break;
    case WM_TIMER:
      GetClientRect(hWnd, &clientRect);

      switch(dir) {
        case LEFT: xpos -= step; break;
        case RIGHT: xpos += step; break;
        case UP: ypos -= step; break;
        case DOWN: ypos += step; break;
      }

      if((xpos - radius) < 0) xpos = radius;
      else if((xpos + radius) > clientRect.right) xpos = clientRect.right - radius;
      else if((ypos - radius) < 0) ypos = radius;
      else if((ypos + radius) > clientRect.bottom) ypos = clientRect.bottom - radius;

      InvalidateRgn(hWnd, NULL, TRUE);
      break;
    case WM_PAINT:
      hdc = BeginPaint(hWnd, &ps);
      randColorBrush = CreateSolidBrush(RGB(randR, randG, randB));
      oldBrush = (HBRUSH)SelectObject(hdc, randColorBrush);

      Ellipse(hdc, xpos - radius, ypos - radius, xpos + radius, ypos + radius);
      SelectObject(hdc, oldBrush);

      DeleteObject(randColorBrush);
      DeleteObject(oldBrush);
      EndPaint(hWnd, &ps);
      break;
    case WM_KEYDOWN:
      if(wParam == VK_RETURN && !start) {
        SetTimer(hWnd, 1, (1000 / 60), NULL);
        start = true;
      }

      switch(wParam) {
        case VK_LEFT: dir = LEFT; break;
        case VK_RIGHT: dir = RIGHT; break;
        case VK_UP: dir = UP; break;
        case VK_DOWN: dir = DOWN; break;
      }

      break;
    case WM_DESTROY:
      KillTimer(hWnd, 1);
      PostQuitMessage(0);
      return 0;
  }

  return (DefWindowProc(hWnd, iMessage, wParam, lParam));
}
