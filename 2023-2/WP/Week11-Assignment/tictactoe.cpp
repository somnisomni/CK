#include <Windows.h>
#include <stdlib.h>
#include <time.h>
#include "resource.h"

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
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


enum TTTCELL {
  EMPTY,
  P1,
  P2
};

class TTTMap {
  private:
    HWND hDlgWnd;
    TTTCELL map[9];
    const static UINT ID_MAP[9];
    const static int CHECK_MAP[][4][3];
  public:
    TTTMap(HWND hDlgWnd): hDlgWnd(hDlgWnd) {
      for(int i = 0; i < 9; i++) map[i] = EMPTY;
    }

    TTTCELL get(int pos) const {
      if(pos < 0 || pos > 8) return EMPTY;
      return map[pos];
    }

    void set(int pos, TTTCELL cell) {
      if(pos < 0 || pos > 8) return;
      map[pos] = cell;
      setButtonStatus(pos, FALSE);
      setButtonText(pos, cell == P1 ? TEXT("O") : TEXT("X"));
    }

    void reset() {
      for(int i = 0; i < 9; i++) {
        map[i] = EMPTY;
        setButtonStatus(i, FALSE);
        setButtonText(i, TEXT(""));
      }
    }

    void enableAllButtons()  const { for(int i = 0; i < 9; i++) setButtonStatus(i, TRUE);  }
    void disableAllButtons() const { for(int i = 0; i < 9; i++) setButtonStatus(i, FALSE); }

    void setButtonStatus(int pos, BOOL status) const {
      if(pos < 0 || pos > 8) return;
      EnableWindow(GetDlgItem(hDlgWnd, ID_MAP[pos]), status);
    }

    void setButtonText(int pos, LPCTSTR text) const {
      if(pos < 0 || pos > 8) return;
      SetDlgItemText(hDlgWnd, ID_MAP[pos], text);
    }

    BOOL compareButtonId(int pos, UINT compareId) const {
      if(pos < 0 || pos > 8) return FALSE;
      return ID_MAP[pos] == compareId;
    }

    BOOL isFull() const {
      for(int i = 0; i < 9; i++) if(map[i] == EMPTY) return FALSE;
      return TRUE;
    }

    BOOL checkAcceptable(TTTCELL curPlayer, int curPos) const {
      if(curPos < 0 || curPos > 8) return FALSE;

      BOOL acceptable = FALSE;
      for(int i = 0; i < 4; i++) {
        if(CHECK_MAP[curPos][i][0] == -1) break;
        if(map[CHECK_MAP[curPos][i][0]] == curPlayer &&
          map[CHECK_MAP[curPos][i][1]] == curPlayer &&
          map[CHECK_MAP[curPos][i][2]] == curPlayer) {
          acceptable = TRUE;
          break;
        }
      }
      return acceptable;
    }
};

const UINT TTTMap::ID_MAP[9] = {
    IDC_TT_1, IDC_TT_2, IDC_TT_3,
    IDC_TT_4, IDC_TT_5, IDC_TT_6,
    IDC_TT_7, IDC_TT_8, IDC_TT_9
};
#define MAPNULL {-1, -1, -1}
const int TTTMap::CHECK_MAP[][4][3] = {
  /* 0 */ {{0, 3, 6}, {0, 1, 2}, {0, 4, 8},   MAPNULL},
  /* 1 */ {{1, 4, 7}, {0, 1, 2},   MAPNULL,   MAPNULL},
  /* 2 */ {{2, 5, 8}, {0, 1, 2}, {2, 4, 6},   MAPNULL},
  /* 3 */ {{0, 3, 6}, {3, 4, 5},   MAPNULL,   MAPNULL},
  /* 4 */ {{1, 4, 7}, {3, 4, 5}, {2, 4, 6}, {0, 4, 8}},
  /* 5 */ {{2, 5, 8}, {3, 4, 5},   MAPNULL,   MAPNULL},
  /* 6 */ {{0, 3, 6}, {6, 7, 8}, {2, 4, 6},   MAPNULL},
  /* 7 */ {{1, 4, 7}, {6, 7, 8},   MAPNULL,   MAPNULL},
  /* 8 */ {{2, 5, 8}, {6, 7, 8}, {0, 4, 8},   MAPNULL}
};

INT_PTR CALLBACK TTTDlgProc(HWND hDlgWnd, UINT iMessage, WPARAM wParam, LPARAM lParam) {
  static TTTMap map          = TTTMap(hDlgWnd);
  static BOOL   currentTurn  = FALSE;  // false: P1, true: P2
  static WCHAR  P1_NAME[128] = L"Player 1";
  static WCHAR  P2_NAME[128] = L"Player 2";

  switch(iMessage) {
    case WM_INITDIALOG:
      /* RESET ALL */
      SetWindowText(hDlgWnd, TEXT("Æ½ÅÃÅä!")); 

      SetDlgItemText(hDlgWnd, IDC_TTT_EDIT_P1, P1_NAME);
      SetDlgItemText(hDlgWnd, IDC_TTT_EDIT_P2, P2_NAME);
      EnableWindow(GetDlgItem(hDlgWnd, IDC_TTT_EDIT_P1), TRUE);
      EnableWindow(GetDlgItem(hDlgWnd, IDC_TTT_EDIT_P2), TRUE);
      EnableWindow(GetDlgItem(hDlgWnd, IDC_TTT_START), TRUE);
      EnableWindow(GetDlgItem(hDlgWnd, IDC_TTT_RESET), FALSE);
      currentTurn = FALSE;
      ShowWindow(GetDlgItem(hDlgWnd, IDC_TTT_P1_CURTURNTEXT), currentTurn ? SW_HIDE : SW_SHOW);
      ShowWindow(GetDlgItem(hDlgWnd, IDC_TTT_P2_CURTURNTEXT), currentTurn ? SW_SHOW : SW_HIDE);
      map.reset();

      return (INT_PTR)TRUE;
    case WM_COMMAND:
      switch(LOWORD(wParam)) {
        case IDCANCEL:
          EndDialog(hDlgWnd, 0);
          break;
        case IDC_TTT_RESET:
          SendMessage(hDlgWnd, WM_INITDIALOG, NULL, NULL);
          break;
        case IDC_TTT_START:
          GetDlgItemText(hDlgWnd, IDC_TTT_EDIT_P1, P1_NAME, 128);
          GetDlgItemText(hDlgWnd, IDC_TTT_EDIT_P2, P2_NAME, 128);
          EnableWindow(GetDlgItem(hDlgWnd, IDC_TTT_EDIT_P1), FALSE);
          EnableWindow(GetDlgItem(hDlgWnd, IDC_TTT_EDIT_P2), FALSE);
          EnableWindow(GetDlgItem(hDlgWnd, IDC_TTT_START), FALSE);
          EnableWindow(GetDlgItem(hDlgWnd, IDC_TTT_RESET), TRUE);
          map.enableAllButtons();
          break;
      }

      int curPos = -1;
      for(int i = 0; i < 9; i++) if(map.compareButtonId(i, LOWORD(wParam))) curPos = i;
      if(curPos < 0) break;

      map.set(curPos, currentTurn ? P2 : P1);

      if(map.checkAcceptable(currentTurn ? P2 : P1, curPos)) {
        MessageBox(hDlgWnd, currentTurn ? P2_NAME : P1_NAME, TEXT("Win!"), MB_OK);
        map.disableAllButtons();
        break;
      } else {
        if(map.isFull()) {
          MessageBox(hDlgWnd, TEXT("Draw!"), TEXT("GAME OVER"), MB_OK);
        }
      }

      currentTurn = !currentTurn;
      ShowWindow(GetDlgItem(hDlgWnd, IDC_TTT_P1_CURTURNTEXT), currentTurn ? SW_HIDE : SW_SHOW);
      ShowWindow(GetDlgItem(hDlgWnd, IDC_TTT_P2_CURTURNTEXT), currentTurn ? SW_SHOW : SW_HIDE);

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