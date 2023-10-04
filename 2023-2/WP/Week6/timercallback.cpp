#include <Windows.h>
#include <cstdlib>
#include <ctime>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

HINSTANCE g_hInst;
LPCTSTR lpszClass = TEXT("Week6");

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

VOID CALLBACK TimerProc(HWND hWnd, UINT uMsg, UINT idEvent, DWORD dwTime) {
  HDC hdc;
  hdc = GetDC(hWnd);
  for(int i = 0; i < 1000; i++) {
    SetPixel(hdc, rand() % 500, rand() % 400, RGB(rand() % 256, rand() % 256, rand() % 256));
  }
  ReleaseDC(hWnd, hdc);
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam) {
  HDC hdc;
  PAINTSTRUCT ps;
  static TCHAR str[50];

  switch(iMessage) {
    case WM_LBUTTONDOWN:
      lstrcpy(str, TEXT("왼쪽 버튼"));
      InvalidateRect(hWnd, NULL, TRUE);
      SetTimer(hWnd, 1, 3000, NULL);
      break;
    case WM_TIMER:
      KillTimer(hWnd, 1);
      lstrcpy(str, TEXT(""));
      InvalidateRect(hWnd, NULL, TRUE);
    case WM_PAINT:
      hdc = BeginPaint(hWnd, &ps);
      TextOut(hdc, 100, 100, str, lstrlen(str));
      EndPaint(hWnd, &ps);
      break;
    case WM_DESTROY:
      KillTimer(hWnd, 1);
      PostQuitMessage(0);
      return 0;
  }

  return (DefWindowProc(hWnd, iMessage, wParam, lParam));
}
