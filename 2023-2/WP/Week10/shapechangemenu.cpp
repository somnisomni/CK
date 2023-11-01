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

enum SHAPE {
  CIRCLE,
  RECTANGLE,
  LINE
};

enum COLOR {
  RED,
  GREEN,
  BLUE
};

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam) {
  HDC hdc;
  PAINTSTRUCT ps;

  static SHAPE shape = CIRCLE;
  static COLOR color = RED;
  static RECT area = { 100, 100, 200, 200 };

  HBRUSH currentBrush = NULL;
  HBRUSH oldBrush = NULL;
  HPEN currentPen = NULL;
  HPEN oldPen = NULL;

  switch(iMessage) {
    case WM_CREATE:
      break;
    case WM_COMMAND:
      switch(LOWORD(wParam)) {
        case ID_CIRCLERED:
          shape = CIRCLE;
          color = RED;
          break;
        case ID_CIRCLEGREEN:
          shape = CIRCLE;
          color = GREEN;
          break;
        case ID_CIRCLEBLUE:
          shape = CIRCLE;
          color = BLUE;
          break;
        case ID_RECTRED:
          shape = RECTANGLE;
          color = RED;
          break;
        case ID_RECTGREEN:
          shape = RECTANGLE;
          color = GREEN;
          break;
        case ID_RECTBLUE:
          shape = RECTANGLE;
          color = BLUE;
          break;
        case ID_LINERED:
          shape = LINE;
          color = RED;
          break;
        case ID_LINEGREEN:
          shape = LINE;
          color = GREEN;
          break;
        case ID_LINEBLUE:
          shape = LINE;
          color = BLUE;
          break;
      }

      InvalidateRect(hWnd, NULL, TRUE);
      break;
    case WM_PAINT:
      hdc = BeginPaint(hWnd, &ps);

      if(shape != LINE) {
        currentBrush = CreateSolidBrush(RGB(
          color == RED ? 255 : 0, 
          color == GREEN ? 255 : 0, 
          color == BLUE ? 255 : 0
        ));
        oldBrush = (HBRUSH) SelectObject(hdc, currentBrush);
      } else {
        currentPen = CreatePen(PS_SOLID, 2, RGB(
          color == RED ? 255 : 0,
          color == GREEN ? 255 : 0,
          color == BLUE ? 255 : 0
        ));
        oldPen = (HPEN) SelectObject(hdc, currentPen);
      }

      switch(shape) {
        case CIRCLE:
          Ellipse(hdc, area.left, area.top, area.right, area.bottom);
          break;
        case RECTANGLE:
          Rectangle(hdc, area.left, area.top, area.right, area.bottom);
          break;
        case LINE:
          MoveToEx(hdc, area.left, area.top, NULL);
          LineTo(hdc, area.right, area.bottom);
          break;
      }

      DeleteObject(currentBrush);
      DeleteObject(oldBrush);
      DeleteObject(currentPen);
      DeleteObject(oldPen);

      EndPaint(hWnd, &ps);
      break;
    case WM_DESTROY:
      PostQuitMessage(0);
      break;
  }

  return (DefWindowProc(hWnd, iMessage, wParam, lParam));
}
