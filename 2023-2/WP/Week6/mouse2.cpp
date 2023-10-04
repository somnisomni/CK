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
  static int x, y;
  static BOOL selection;
  int mx, my;

  switch(iMessage) {
    case WM_CREATE:
      x = 50; y = 50;
      selection = FALSE;
      return 0;
    case WM_PAINT:
      hdc = BeginPaint(hWnd, &ps);

      if(selection)
        Rectangle(hdc, x - BSIZE, y - BSIZE, x + BSIZE, y + BSIZE);
      Ellipse(hdc, x - BSIZE, y - BSIZE, x + BSIZE, y + BSIZE);
      EndPaint(hWnd, &ps);

      return 0;
    case WM_LBUTTONDOWN:
      mx = LOWORD(lParam);
      my = HIWORD(lParam);
      if(InCircle(x, y, mx, my)) selection = TRUE;
      InvalidateRect(hWnd, NULL, TRUE);
      return 0;
    case WM_LBUTTONUP:
      selection = FALSE;
      InvalidateRect(hWnd, NULL, TRUE);
      return 0;
    case WM_DESTROY:
      PostQuitMessage(0);
      return 0;
  }

  return (DefWindowProc(hWnd, iMessage, wParam, lParam));
}
