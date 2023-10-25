#include <Windows.h>
#include "resource.h"

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

HINSTANCE g_hInst;
LPCTSTR lpszClass = TEXT("Week9");

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

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam) {
  HDC hdc;
  PAINTSTRUCT ps;

  int answer;
  OPENFILENAME ofn;
  TCHAR str[300] = TEXT("");
  TCHAR lpstrFile[MAX_PATH] = TEXT("");
  TCHAR test[10] = TEXT("test");
  TCHAR lpstrFileTitle[MAX_PATH] = TEXT("");
  TCHAR filter[] = TEXT("모든 파일(*.*)\0*.*\0텍스트 파일(*.txt, *.doc)\0*.txt;*.doc\0");

  static HMENU hMenu, hSubmenu;

  switch(iMessage) {
    case WM_CREATE:
      hMenu = GetMenu(hWnd);
      hSubmenu = GetSubMenu(hMenu, 1);
      EnableMenuItem(hSubmenu, ID_EDITCOPY, MF_GRAYED);
      EnableMenuItem(hSubmenu, ID_EDITPASTE, MF_GRAYED);
      break;
    case WM_COMMAND:
      switch(LOWORD(wParam)) {
        case ID_FILENEW:
          MessageBox(hWnd, TEXT("새 파일을 여시겠습니까?"), TEXT("새 파일 선택"), MB_OKCANCEL);
          break;
        case ID_FILEOPEN:
          memset(&ofn, 0, sizeof(OPENFILENAME));
          ofn.lStructSize = sizeof(OPENFILENAME);
          ofn.hwndOwner = hWnd;
          ofn.lpstrFilter = filter;
          ofn.lpstrFile = lpstrFile;
          ofn.nMaxFile = MAX_PATH;
          ofn.lpstrFileTitle = lpstrFileTitle;
          ofn.nMaxFileTitle = MAX_PATH;
          ofn.lpstrInitialDir = TEXT(".");

          if(GetOpenFileName(&ofn) != 0) {
            wsprintf(str, TEXT("%s\n파일을 열겠습니까?"), ofn.lpstrFile);
            MessageBox(hWnd, str, TEXT("열기 선택"), MB_OK);
          }
          
          break;
        case ID_FILESAVE:
          MessageBox(hWnd, TEXT("파일 저장됨"), TEXT("파일 저장"), MB_OK);
          break;
        case ID_EXIT:
          answer = MessageBox(hWnd, TEXT("파일을 저장하고 끝내겠습니까?"), TEXT("끝내기 선택"), MB_YESNOCANCEL);
          if(answer == IDYES || answer == IDNO) SendMessage(hWnd, WM_DESTROY, NULL, NULL);
          break;
      }
      break;
    case WM_PAINT:
      hdc = BeginPaint(hWnd, &ps);
      EndPaint(hWnd, &ps);
      break;
    case WM_DESTROY:
      PostQuitMessage(0);
      break;
  }

  return (DefWindowProc(hWnd, iMessage, wParam, lParam));
}
