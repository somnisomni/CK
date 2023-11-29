#include <Windows.h>
#include <cstdlib>
#include <ctime>
#include "resource.h"

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

HINSTANCE g_hInst;
LPCTSTR lpszClass = TEXT("Week14");

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

class Butterfly {
  private:
  int x, y, w, h;
  bool xDir = true, yDir = true;
  public:
  Butterfly(int width = 0, int height = 0, int x = 0, int y = 0): w(width), h(height), x(x), y(y) {}

  int getX() const { return x; }
  int getY() const { return y; }

  void update(int boundX, int boundY, int maxStep = 1) {
    int xStep = rand() % maxStep;
    int yStep = rand() & maxStep;

    x += xDir ? xStep : -xStep;
    y += yDir ? yStep : -yStep;

    if(x < 0) xDir = true;
    else if(x + w > boundX) xDir = false;

    if(y < 0) yDir = true;
    else if(y + h > boundY) yDir = false;
  }
};

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam) {
  HDC hdc, memdc, memdc2;
  PAINTSTRUCT ps;

  static HBITMAP hBufferBitmap, hBgBitmap, hBflyBitmap, hBflyMaskBitmap;
  static BITMAP bgBitmap, bflyBitmap;
  HBITMAP hOldBitmap1, hOldBitmap2;
  static RECT windowRect;

#define BFLYS_MAX 50
  static Butterfly bflys[BFLYS_MAX];
  static int bflysIdx = 0;

  switch(iMessage) {
    case WM_CREATE:
      SetTimer(hWnd, 1, 100, NULL);

      hBgBitmap = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP2));
      hBflyBitmap = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP4));
      hBflyMaskBitmap = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP5));

      GetObject(hBgBitmap, sizeof(BITMAP), &bgBitmap);
      GetObject(hBflyBitmap, sizeof(BITMAP), &bflyBitmap);
    case WM_SIZE:
      GetClientRect(hWnd, &windowRect);
      break;
    case WM_TIMER:
      for(int i = 0; i < bflysIdx; i++) {
        bflys[i].update(windowRect.right, windowRect.bottom, 20);
      }
      InvalidateRect(hWnd, NULL, TRUE);
      break;
    case WM_LBUTTONDOWN:
      if(bflysIdx < BFLYS_MAX) {
        int x = LOWORD(lParam);
        int y = HIWORD(lParam);

        bflys[bflysIdx++] = Butterfly(
          bflyBitmap.bmWidth,
          bflyBitmap.bmHeight,
          x - (bflyBitmap.bmWidth / 2),
          y - (bflyBitmap.bmHeight / 2));
      }
      InvalidateRect(hWnd, NULL, TRUE);
      break;
    case WM_PAINT:
      hdc = BeginPaint(hWnd, &ps);
      memdc = CreateCompatibleDC(hdc);
      memdc2 = CreateCompatibleDC(memdc);
      //if(hBufferBitmap == NULL)
        hBufferBitmap = CreateCompatibleBitmap(hdc, windowRect.right, windowRect.bottom);
      
      hOldBitmap1 = (HBITMAP)SelectObject(memdc, hBufferBitmap);
      hOldBitmap2 = (HBITMAP)SelectObject(memdc2, hBgBitmap);
      // BG
      StretchBlt(memdc, 0, 0, windowRect.right, windowRect.bottom, memdc2, 0, 0, bgBitmap.bmWidth, bgBitmap.bmHeight, SRCCOPY);
      // Butterfly
      for(int i = 0; i < bflysIdx; i++) {
        SelectObject(memdc2, hBflyMaskBitmap);
        BitBlt(memdc, bflys[i].getX(), bflys[i].getY(), bflyBitmap.bmWidth, bflyBitmap.bmHeight, memdc2, 0, 0, SRCAND);
        SelectObject(memdc2, hBflyBitmap);
        BitBlt(memdc, bflys[i].getX(), bflys[i].getY(), bflyBitmap.bmWidth, bflyBitmap.bmHeight, memdc2, 0, 0, SRCPAINT);
      }
      SelectObject(memdc2, hOldBitmap2);

      BitBlt(hdc, 0, 0, windowRect.right, windowRect.bottom, memdc, 0, 0, SRCCOPY);
      SelectObject(memdc2, hOldBitmap2);
      SelectObject(memdc, hOldBitmap1);
      DeleteDC(memdc2);
      DeleteDC(memdc);
      EndPaint(hWnd, &ps);
      break;
    case WM_DESTROY:
      DeleteObject(hBufferBitmap);
      DeleteObject(hBgBitmap);
      DeleteObject(hBflyBitmap);
      DeleteObject(hBflyMaskBitmap);
      PostQuitMessage(0);
      break;
  }

  return (DefWindowProc(hWnd, iMessage, wParam, lParam));
}
