#include <Windows.h>
#include <math.h>
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
LPCTSTR lpszClass = TEXT("Week6");

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
  static RECT rectView;
  static int initX = 50, initY = 50;
  static int x = 50, y = 50;
  static int centerX = 50, centerY = 50;
  static BOOL sizing = FALSE;

  switch(iMessage) {
    case WM_MOUSEMOVE:
      if(sizing) {
        x = LOWORD(lParam);
        y = HIWORD(lParam);
        InvalidateRect(hWnd, NULL, TRUE);
      }
      return 0;
    case WM_PAINT:
      hdc = BeginPaint(hWnd, &ps);
      Ellipse(hdc, initX - BSIZE, initY - BSIZE, x + BSIZE, y + BSIZE);
      EndPaint(hWnd, &ps);

      return 0;
    case WM_LBUTTONDOWN:
      x = LOWORD(lParam);
      y = HIWORD(lParam);
      centerX = (x - initX) / 2;
      centerY = (y - initY) / 2;
      if(InCircle(initX, initY, x, y)) sizing = TRUE;
      return 0;
    case WM_LBUTTONUP:
      sizing = FALSE;
      return 0;
    case WM_DESTROY:
      PostQuitMessage(0);
      return 0;
  }

  return (DefWindowProc(hWnd, iMessage, wParam, lParam));
}
