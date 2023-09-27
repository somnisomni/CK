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
  SYSTEMTIME st;
  static TCHAR sTime[128];

  switch(iMessage) {
    case WM_CREATE:
      SetTimer(hWnd, 1, 1000, NULL);
      SetTimer(hWnd, 2, 5000, NULL);
      SendMessage(hWnd, WM_TIMER, 1, NULL);
      break;
    case WM_TIMER:
      switch(wParam) {
        case 1:
          GetLocalTime(&st);
          wsprintf(sTime, TEXT("현재 시간: %02d:%02d:%02d"), st.wHour, st.wMinute, st.wSecond);
          InvalidateRect(hWnd, NULL, TRUE);
          break;
        case 2:
          MessageBeep(0);
          break;
      }
      break;
    case WM_PAINT:
      hdc = BeginPaint(hWnd, &ps);
      TextOut(hdc, 100, 100, sTime, lstrlen(sTime));
      EndPaint(hWnd, &ps);
      break;
    case WM_DESTROY:
      KillTimer(hWnd, 1);
      KillTimer(hWnd, 2);
      PostQuitMessage(0);
      return 0;
  }

  return (DefWindowProc(hWnd, iMessage, wParam, lParam));
}
