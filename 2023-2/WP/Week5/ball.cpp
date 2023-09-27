#include <Windows.h>
#include <cstdlib>
#include <ctime>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

HINSTANCE g_hInst;
LPCTSTR lpszClass = TEXT("Week5");

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
  static bool dir = true; // true: right, false: left

  switch(iMessage) {
    case WM_CREATE:
      GetClientRect(hWnd, &clientRect);
      ypos = clientRect.bottom - radius;
      xpos = radius;
      break;
    case WM_TIMER:
      GetClientRect(hWnd, &clientRect);
      ypos = clientRect.bottom - radius;
      xpos += dir ? step : -step;

      if(xpos + radius >= clientRect.right) dir = false;
      if(xpos - radius <= clientRect.left) dir = true;

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
      break;
    case WM_DESTROY:
      KillTimer(hWnd, 1);
      PostQuitMessage(0);
      return 0;
  }

  return (DefWindowProc(hWnd, iMessage, wParam, lParam));
}
