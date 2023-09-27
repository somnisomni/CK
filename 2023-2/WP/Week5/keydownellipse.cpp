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

  static int x, y;
  static RECT clientRect;
  static bool pressed = false;

  switch(iMessage) {
    case WM_CREATE:
      x = 20;
      y = 20;
      GetClientRect(hWnd, &clientRect);
      break;
    case WM_SIZE:
      GetClientRect(hWnd, &clientRect);
      break;
    case WM_PAINT:
    {
      /* SETUP */
      hdc = BeginPaint(hWnd, &ps);
      colorBrush = CreateSolidBrush(RGB(128, 128, 128));
      oldBrush = (HBRUSH)SelectObject(hdc, colorBrush);
      SelectObject(hdc, oldBrush);

      /* DRAW */
      if(pressed) SelectObject(hdc, colorBrush);
      Ellipse(hdc, x - 20, y - 20, x + 20, y + 20);
      SelectObject(hdc, oldBrush);

      /* CLEANUP */
      DeleteObject(colorBrush);
      EndPaint(hWnd, &ps);
      break;
    }
    case WM_KEYDOWN:
      pressed = true;
      switch(wParam) {
        case VK_RIGHT:
          x += 40;
          if(x + 20 > clientRect.right) x -= 40;
          break;
        case VK_LEFT:
          x -= 40;
          if(x - 20 < clientRect.left) x += 40;
          break;
        case VK_UP:
          y -= 40;
          if(y - 20 < clientRect.top) y += 40;
          break;
        case VK_DOWN:
          y += 40;
          if(y + 20 > clientRect.bottom) y -= 40;
          break;
      }

      InvalidateRgn(hWnd, NULL, TRUE);
      break;
    case WM_KEYUP:
      pressed = false;
      InvalidateRgn(hWnd, NULL, TRUE);
      break;
    case WM_DESTROY:
      PostQuitMessage(0);
      return 0;
  }

  return (DefWindowProc(hWnd, iMessage, wParam, lParam));
}
