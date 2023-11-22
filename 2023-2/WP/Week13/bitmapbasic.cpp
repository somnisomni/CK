#include <Windows.h>
#include "resource.h"

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

HINSTANCE g_hInst;
LPCTSTR lpszClass = TEXT("Week13");

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
  HBITMAP curBitmapH, oldBitmapH;
  BITMAP curBitmap;

  switch(iMessage) {
    case WM_CREATE:
      break;
    case WM_LBUTTONDOWN:
      break;
    case WM_PAINT:
      hdc = BeginPaint(hWnd, &ps);
      memdc = CreateCompatibleDC(hdc);
      curBitmapH = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP1));
      GetObject(curBitmapH, sizeof(BITMAP), &curBitmap);
      oldBitmapH = (HBITMAP)SelectObject(memdc, curBitmapH);
      //BitBlt(hdc, 0, 0, curBitmap.bmWidth, curBitmap.bmHeight, memdc, 0, 0, SRCCOPY);
      StretchBlt(hdc, 0, 0, curBitmap.bmWidth, curBitmap.bmHeight / 3, memdc, 0, 0, curBitmap.bmWidth, curBitmap.bmHeight, SRCCOPY);
      SelectObject(memdc, oldBitmapH);
      DeleteObject(curBitmapH);
      DeleteDC(memdc);
      EndPaint(hWnd, &ps);
      break;
    case WM_DESTROY:
      PostQuitMessage(0);
      break;
  }

  return (DefWindowProc(hWnd, iMessage, wParam, lParam));
}
