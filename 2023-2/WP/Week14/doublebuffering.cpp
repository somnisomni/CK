#include <Windows.h>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

HINSTANCE g_hInst;
LPCTSTR lpszClass = TEXT("Week14");

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
  HDC hdc, memdc;
  PAINTSTRUCT ps;
  HBITMAP hBitmap, hOldBitmap;

  static RECT bufferRect;

  switch(iMessage) {
    case WM_CREATE:
      break;
    case WM_PAINT:
      hdc = BeginPaint(hWnd, &ps);
      memdc = CreateCompatibleDC(hdc);

      GetClientRect(hWnd, &bufferRect);
      hBitmap = CreateCompatibleBitmap(hdc, bufferRect.right, bufferRect.bottom);
      hOldBitmap = (HBITMAP)SelectObject(memdc, hBitmap);

      PatBlt(memdc, 0, 0, bufferRect.right, bufferRect.bottom, WHITENESS);
      for(int i = 0; i < 30; i++) {
        Rectangle(memdc, rand() % bufferRect.right, rand() % bufferRect.bottom, rand() % bufferRect.right, rand() % bufferRect.bottom);
        Sleep(30);
      }
      BitBlt(hdc, 0, 0, bufferRect.right, bufferRect.bottom, memdc, 0, 0, SRCCOPY);

      SelectObject(hdc, hOldBitmap);
      DeleteObject(hBitmap);
      DeleteDC(memdc);
      EndPaint(hWnd, &ps);
      break;
    case WM_DESTROY:
      PostQuitMessage(0);
      break;
  }

  return (DefWindowProc(hWnd, iMessage, wParam, lParam));
}
