#include <Windows.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

HINSTANCE g_hInst;
LPCTSTR lpszClass = TEXT("Week7");

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
  WndClass.style = CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;
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
  static int CIRC1_RADIUS = 40;
  static int CIRC1_X = 100;
  static int CIRC1_Y = 100;
  static HBRUSH CIRC1_BRUSH = (HBRUSH)GetStockObject(WHITE_BRUSH);
  static int CIRC2_RADIUS = 20;
  static int CIRC2_X;
  static int CIRC2_Y;
  static int CIRC2_STEPCOUNT = 60;
  static int CIRC2_CURSTEP = 0;
  static int CIRC2_STEPDELAY = 10;
  static int CIRC2_STEPTIMERID = 1;
  static int CIRC2_XSTEP;
  static int CIRC2_YSTEP;
  static BOOL CIRC2_ACTIVE = FALSE;
  HBRUSH oldBrush;

  switch(iMessage) {
    case WM_PAINT:
      hdc = BeginPaint(hWnd, &ps);

      // CIRC1
      oldBrush = (HBRUSH)SelectObject(hdc, CIRC1_BRUSH);
      Ellipse(hdc, CIRC1_X - CIRC1_RADIUS / 2,
        CIRC1_Y - CIRC1_RADIUS / 2,
        CIRC1_X + CIRC1_RADIUS / 2,
        CIRC1_Y + CIRC1_RADIUS / 2);
      SelectObject(hdc, oldBrush);

      // CIRC2
      if(CIRC2_ACTIVE == TRUE) {
        Ellipse(hdc, CIRC2_X - CIRC2_RADIUS / 2,
          CIRC2_Y - CIRC2_RADIUS / 2,
          CIRC2_X + CIRC2_RADIUS / 2,
          CIRC2_Y + CIRC2_RADIUS / 2);
      }

      DeleteObject(oldBrush);
      EndPaint(hWnd, &ps);
      return 0;
    case WM_LBUTTONDOWN:
      if(CIRC2_ACTIVE == FALSE) {
        CIRC2_X = LOWORD(lParam);
        CIRC2_XSTEP = (CIRC2_X - CIRC1_X) / CIRC2_STEPCOUNT;
        CIRC2_Y = HIWORD(lParam);
        CIRC2_YSTEP = (CIRC2_Y - CIRC1_Y) / CIRC2_STEPCOUNT;
        CIRC2_CURSTEP = 0;
        CIRC2_ACTIVE = TRUE;
        SetTimer(hWnd, CIRC2_STEPTIMERID, CIRC2_STEPDELAY, NULL);
        InvalidateRect(hWnd, NULL, TRUE);
      }
      return 0;
    case WM_TIMER:
      CIRC2_CURSTEP++;

      if(CIRC2_CURSTEP < CIRC2_STEPCOUNT) {
        // CIRC1_X/Y += CIRC2_X/YSTEP  -> 원1 이동
        // CIRC2_X/Y -= CIRC2_X/YSTEP  -> 원2 이동
        CIRC2_X -= CIRC2_XSTEP;
        CIRC2_Y -= CIRC2_YSTEP;

        // Collide check (rectangular)
        if((((CIRC2_X + CIRC2_RADIUS / 2) > (CIRC1_X - CIRC1_RADIUS / 2)) && ((CIRC2_X - CIRC2_RADIUS / 2) < (CIRC1_X + CIRC1_RADIUS / 2))) &&
          (((CIRC2_Y + CIRC2_RADIUS / 2) > (CIRC1_Y - CIRC1_RADIUS / 2)) && ((CIRC2_Y - CIRC2_RADIUS / 2) < (CIRC1_Y + CIRC1_RADIUS / 2)))) {
          CIRC2_CURSTEP = CIRC2_STEPCOUNT;
        }
      }
      
      if(CIRC2_CURSTEP >= CIRC2_STEPCOUNT) {
        CIRC1_RADIUS += CIRC2_RADIUS;
        DeleteObject(CIRC1_BRUSH);
        CIRC1_BRUSH = CreateSolidBrush(RGB(rand() % 256, rand() % 256, rand() % 256));
        CIRC2_ACTIVE = FALSE;
        KillTimer(hWnd, CIRC2_STEPTIMERID);
      }

      InvalidateRect(hWnd, NULL, TRUE);
      return 0;
    case WM_DESTROY:
      PostQuitMessage(0);
      return 0;
  }

  return (DefWindowProc(hWnd, iMessage, wParam, lParam));
}
