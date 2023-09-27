#include <Windows.h>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

HINSTANCE g_hInst;
LPCTSTR lpszClass = TEXT("Week5");

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
  HBRUSH colorBrush, oldBrush;

  static int radius = 20;
  static int x, y;
  static RECT clientRect;
  static bool wall = false;

  switch(iMessage) {
    case WM_CREATE:
      x = radius * 3;
      y = radius * 3;
      GetClientRect(hWnd, &clientRect);
      break;
    case WM_SIZE:
      GetClientRect(hWnd, &clientRect);
      break;
    case WM_PAINT:
    {
      /* SETUP */
      hdc = BeginPaint(hWnd, &ps);
      colorBrush = CreateSolidBrush(RGB(255, 32, 48));
      oldBrush = (HBRUSH)SelectObject(hdc, colorBrush);
      SelectObject(hdc, oldBrush);

      /* DRAW */
      if(wall) SelectObject(hdc, colorBrush);
      Ellipse(hdc, x - radius, y - radius, x + radius, y + radius);
      SelectObject(hdc, oldBrush);

      /* CLEANUP */
      DeleteObject(colorBrush);
      EndPaint(hWnd, &ps);
      break;
    }
    case WM_KEYDOWN:
      wall = false;

      switch(wParam) {
        case VK_RIGHT:
          x += radius * 2;
          if(x + radius > clientRect.right) x -= radius * 2;
          break;
        case VK_LEFT:
          x -= radius * 2;
          if(x - radius < clientRect.left) x += radius * 2;
          break;
        case VK_UP:
          y -= radius * 2;
          if(y - radius < clientRect.top) y += radius * 2;
          break;
        case VK_DOWN:
          y += radius * 2;
          if(y + radius > clientRect.bottom) y -= radius * 2;
          break;
      }

      // step is radius * 2
      if(x + radius * 3 > clientRect.right      // circle right(x + radius) + step  > window right
        || x - radius * 3 < clientRect.left     // circle left(x - radius) - step   < window left
        || y + radius * 3 > clientRect.bottom   // circle bottom(y + radius) + step > window bottom
        || y - radius * 3 < clientRect.top) {   // circle top(y - radius) - step    < window top
        wall = true;
      }

      InvalidateRgn(hWnd, NULL, TRUE);
      break;
    case WM_DESTROY:
      PostQuitMessage(0);
      return 0;
  }

  return (DefWindowProc(hWnd, iMessage, wParam, lParam));
}
