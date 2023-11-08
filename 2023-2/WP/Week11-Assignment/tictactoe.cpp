#include <Windows.h>
#include <stdlib.h>
#include <time.h>
#include "resource.h"

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK DlgProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK CalcDlgProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK TTTDlgProc(HWND, UINT, WPARAM, LPARAM);

HINSTANCE g_hInst;
LPCTSTR lpszClass = TEXT("Week11");

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
  WndClass.lpszMenuName = MAKEINTRESOURCE(IDR_MENU2);
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

static TCHAR str[128] = TEXT("");
static int x, y;

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam) {
  HDC hdc;
  PAINTSTRUCT ps;

  switch(iMessage) {
    case WM_CREATE:
      break;
    case WM_PAINT:
      hdc = BeginPaint(hWnd, &ps);
      TextOut(hdc, x, y, str, lstrlen(str));
      EndPaint(hWnd, &ps);
      break;
    case WM_COMMAND:
      switch(LOWORD(wParam)) {
        case ID_MENU_OPENDIALOG:
          DialogBox(g_hInst, MAKEINTRESOURCE(IDD_DIALOG1), hWnd, DlgProc);
          break;
        case ID_MENU_CALC:
          DialogBox(g_hInst, MAKEINTRESOURCE(IDD_DIALOG2), hWnd, CalcDlgProc);
          break;
        case ID_MENU_TTT:
          DialogBox(g_hInst, MAKEINTRESOURCE(IDD_DIALOG_TTT), hWnd, TTTDlgProc);
          break;
      }
      break;
    case WM_DESTROY:
      PostQuitMessage(0);
      break;
  }

  return (DefWindowProc(hWnd, iMessage, wParam, lParam));
}

INT_PTR CALLBACK DlgProc(HWND hDlgWnd, UINT iMessage, WPARAM wParam, LPARAM lParam) {
  HDC hdc;
  HWND button = NULL;

  switch(iMessage) {
    case WM_INITDIALOG:
      SetDlgItemText(hDlgWnd, IDC_EDIT_STR, str);
      SetDlgItemInt(hDlgWnd, IDC_EDIT_X, x, FALSE);
      SetDlgItemInt(hDlgWnd, IDC_EDIT_Y, y, FALSE);

      button = GetDlgItem(hDlgWnd, ID_PAUSE);
      EnableWindow(button, FALSE);

      return (INT_PTR)TRUE;
    case WM_COMMAND:
      switch(LOWORD(wParam)) {
        case IDC_BTN_COPYTEXT:
          TCHAR strCopied[128];
          GetDlgItemText(hDlgWnd, IDC_EDIT_STR, str, 128);
          lstrcpy(strCopied, str);
          SetDlgItemText(hDlgWnd, IDC_EDIT_COPIED, strCopied);
          break;
        case IDC_BTN_DELETETEXT:
          SetDlgItemText(hDlgWnd, IDC_EDIT_COPIED, TEXT(""));
          break;
        case ID_START:
          button = GetDlgItem(hDlgWnd, ID_START);
          EnableWindow(button, FALSE);
          button = GetDlgItem(hDlgWnd, ID_PAUSE);
          EnableWindow(button, TRUE);

          GetDlgItemText(hDlgWnd, IDC_EDIT_STR, str, 128);
          x = GetDlgItemInt(hDlgWnd, IDC_EDIT_X, NULL, FALSE);
          y = GetDlgItemInt(hDlgWnd, IDC_EDIT_Y, NULL, FALSE);

          InvalidateRect(GetParent(hDlgWnd), NULL, TRUE);
          EndDialog(hDlgWnd, 0);
          break;
        case ID_PAUSE:
          button = GetDlgItem(hDlgWnd, ID_START);
          EnableWindow(button, TRUE);
          button = GetDlgItem(hDlgWnd, ID_PAUSE);
          EnableWindow(button, FALSE);

          break;
        case ID_CLOSE:
          EndDialog(hDlgWnd, 0);
          break;
      }
      break;
  }

  return (INT_PTR)FALSE;
}

INT_PTR CALLBACK CalcDlgProc(HWND hDlgWnd, UINT iMessage, WPARAM wParam, LPARAM lParam) {
  int num1 = 0, num2 = 0, result = 0;

  switch(iMessage) {
    case WM_INITDIALOG:
      return (INT_PTR)TRUE;
    case WM_COMMAND:
      if(LOWORD(wParam) == IDCANCEL) {
        EndDialog(hDlgWnd, 0);
        break;
      }
      
      num1 = GetDlgItemInt(hDlgWnd, IDC_NUM1, NULL, TRUE);
      num2 = GetDlgItemInt(hDlgWnd, IDC_NUM2, NULL, TRUE);
      result = 0;

      switch(LOWORD(wParam)) {
        case IDC_PLUS:
          SetDlgItemInt(hDlgWnd, IDC_RESULT, num1 + num2, TRUE);
          break;
        case IDC_MINUS:
          SetDlgItemInt(hDlgWnd, IDC_RESULT, num1 - num2, TRUE);
          break;
        case IDC_MULTIPLY:
          SetDlgItemInt(hDlgWnd, IDC_RESULT, num1 * num2, TRUE);
          break;
        case IDC_DIVIDE:
          if(num2 != 0) {
            SetDlgItemInt(hDlgWnd, IDC_RESULT, num1 / num2, TRUE);
          } else {
            SetDlgItemText(hDlgWnd, IDC_RESULT, TEXT("0으로 나눌 수 없음"));
          }
          break;
      }

      // SetDlgItemInt(hDlgWnd, IDC_RESULT, result, TRUE);    // Stack overflow???
      break;
  }

  return (INT_PTR)FALSE;
}

enum TTTCELL {
  EMPTY,
  P1,
  P2
};

INT_PTR CALLBACK TTTDlgProc(HWND hDlgWnd, UINT iMessage, WPARAM wParam, LPARAM lParam) {
  static unsigned int idMap[9] = {
    IDC_TT_1, IDC_TT_2, IDC_TT_3,
    IDC_TT_4, IDC_TT_5, IDC_TT_6,
    IDC_TT_7, IDC_TT_8, IDC_TT_9
  };
  static TTTCELL checkMap[9] = {
    EMPTY, EMPTY, EMPTY,
    EMPTY, EMPTY, EMPTY,
    EMPTY, EMPTY, EMPTY
  };
  static bool currentTurn = false;  // false: P1, true: P2
  static LPCTSTR P1_TEXT = TEXT("O");
  static LPCTSTR P2_TEXT = TEXT("X");

  switch(iMessage) {
    case WM_INITDIALOG:
      return (INT_PTR)TRUE;
    case WM_COMMAND:
      switch(LOWORD(wParam)) {
        case IDCANCEL:
          EndDialog(hDlgWnd, 0);
          break;
        case IDC_TTT_RESTART:
          break;
        case IDC_TTT_START:
          break;
      }

      int curPos = -1;
      for(int i = 0; i < 9; i++) if(LOWORD(wParam) == idMap[i]) curPos = i;
      if(curPos < 0) break;

      checkMap[curPos] = currentTurn ? P2 : P1;
      EnableWindow(GetDlgItem(hDlgWnd, idMap[curPos]), FALSE);
      SetDlgItemText(hDlgWnd, idMap[curPos], currentTurn ? P2_TEXT : P1_TEXT);

      currentTurn = !currentTurn;

      /* // computer random
      while(true) {
        int randPos = rand() % 9;
        if(checkMap[randPos] == 0) {
          checkMap[randPos] = P2;
          EnableWindow(GetDlgItem(hDlgWnd, idMap[randPos]), FALSE);
          SetDlgItemText(hDlgWnd, idMap[randPos], TEXT("X"));
          break;
        }
      } */
      break;
  }

  return (INT_PTR)FALSE;
}