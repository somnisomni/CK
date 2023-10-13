#include <Windows.h>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

HINSTANCE g_hInst;
LPCTSTR lpszClass = TEXT("Week7");

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
  
  // 좌표값을 실수 타입으로 쓰는 것만으로도 정확도 향상 가능
  // (좌표 계산은 정확히 하고, 화면에 그려질 때는 정수로 변환하여 소수점 이하를 버리면서 그림)

  static LPCWSTR CAT_TEXT = TEXT("고양이");
  static double CAT_X = 100.0f;
  static double CAT_Y = 100.0f;
  static RECT CAT_RECT;
  static double CAT_STEPX = 0.0f;
  static double CAT_STEPY = 0.0f;
  static int CAT_TIMER_ID = 1;
  static int CAT_TIMER_DELAY = (1000 / 60);  // 60fps
  static int CAT_STEPCOUNT = 10;
  static int CAT_CURSTEP = 0;

  static LPCWSTR MOUSE_TEXT = TEXT(" 쥐 ");
  static BOOL MOUSE_ACTIVE = FALSE;
  static double MOUSE_X;
  static double MOUSE_Y;
  static RECT MOUSE_RECT;

  static LPCWSTR CAUGHT_TEXT = TEXT("잡았다!!!");
  static BOOL CAUGHT = FALSE;
  static RECT CAUGHT_RECT = { 50, 50, 150, 70 };

  switch(iMessage) {
    case WM_PAINT:
      CAT_RECT = { (int)CAT_X - 30, (int)CAT_Y - 20, (int)CAT_X + 30, (int)CAT_Y + 20 };
      hdc = BeginPaint(hWnd, &ps);
      SetBkMode(hdc, TRANSPARENT);

      // CAT
      DrawText(hdc, CAT_TEXT, lstrlen(CAT_TEXT), &CAT_RECT, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

      // MOUSE
      if(MOUSE_ACTIVE) {
        MOUSE_RECT = { (int)MOUSE_X - 30, (int)MOUSE_Y - 20, (int)MOUSE_X + 30, (int)MOUSE_Y + 20 };
        DrawText(hdc, MOUSE_TEXT, lstrlen(MOUSE_TEXT), &MOUSE_RECT, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
      }

      // CAUGHT
      if(CAUGHT) {
        DrawText(hdc, CAUGHT_TEXT, lstrlen(CAUGHT_TEXT), &CAUGHT_RECT, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
      }

      EndPaint(hWnd, &ps);
      return 0;
    case WM_LBUTTONDOWN:
      MOUSE_ACTIVE = TRUE;
      MOUSE_X = LOWORD(lParam);
      MOUSE_Y = HIWORD(lParam);
      SetTimer(hWnd, CAT_TIMER_ID, CAT_TIMER_DELAY, NULL);
      InvalidateRect(hWnd, NULL, TRUE);
      // return 0;   // case문을 빠져나가지 않게 함 (마우스 버튼을 누를 시에도 마우스를 움직인 것으로 간주하고 처리)
    case WM_MOUSEMOVE:
      if(MOUSE_ACTIVE) {
        CAUGHT = FALSE;
        MOUSE_X = LOWORD(lParam);
        MOUSE_Y = HIWORD(lParam);

        CAT_CURSTEP = 0;
        CAT_STEPX = (MOUSE_X - CAT_X) / CAT_STEPCOUNT;
        CAT_STEPY = (MOUSE_Y - CAT_Y) / CAT_STEPCOUNT;

        InvalidateRect(hWnd, NULL, TRUE);
      }
      return 0;
    case WM_LBUTTONUP:
      MOUSE_ACTIVE = FALSE;
      CAUGHT = FALSE;
      CAT_CURSTEP = 0;
      KillTimer(hWnd, CAT_TIMER_ID);
      InvalidateRect(hWnd, NULL, TRUE);
      return 0;
    case WM_TIMER:
      CAT_CURSTEP++;

      if(CAT_CURSTEP < CAT_STEPCOUNT) {
        CAT_X += CAT_STEPX;
        CAT_Y += CAT_STEPY;
      } else {
        // 최대 스텝 수 도달 시 잡은 것으로 간주
        CAUGHT = TRUE;
      }

      InvalidateRect(hWnd, NULL, TRUE);
      return 0;
    case WM_DESTROY:
      PostQuitMessage(0);
      return 0;
  }

  return (DefWindowProc(hWnd, iMessage, wParam, lParam));
}
