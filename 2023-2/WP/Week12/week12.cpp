#include <Windows.h>
#include "resource.h"

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK DlgProc(HWND, UINT, WPARAM, LPARAM);

HINSTANCE g_hInst;
LPCTSTR lpszClass = TEXT("Week12");

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

  switch(iMessage) {
    case WM_CREATE:
      break;
    case WM_LBUTTONDOWN:
      DialogBox(g_hInst, MAKEINTRESOURCE(IDD_DIALOG1), hWnd, DlgProc);
      break;
    case WM_PAINT:
      hdc = BeginPaint(hWnd, &ps);
      TextOut(hdc, 10, 10, TEXT("창 클릭"), lstrlen(TEXT("창 클릭")));
      EndPaint(hWnd, &ps);
      break;
    case WM_DESTROY:
      PostQuitMessage(0);
      break;
  }

  return (DefWindowProc(hWnd, iMessage, wParam, lParam));
}

enum GENDER {
  MALE,
  FEMALE,
  UNKNOWN
};

INT_PTR CALLBACK DlgProc(HWND hDlgWnd, UINT iMessage, WPARAM wParam, LPARAM lParam) {
  HDC hdc;
  PAINTSTRUCT ps;

  static RECT box = { 20, 20, 80, 80 };
  static BOOL shape = TRUE; // TRUE: rect, FALSE: ellipse

  static HWND hCombo;
  static HWND hList;
  static int  comboSelection;
  static int  listSelection;
  TCHAR       name[20];

  static const int BIRTH_YEAR_START = 1970;
  static const int BIRTH_YEAR_END   = 2020;
  static HWND hListMembers;
  static int  listMemberSelection;
  static HWND hBirthYearCombo;
  static int  birthYearSelection;
  static GENDER selectedGender = UNKNOWN;
  LPCWSTR     genderString;
  TCHAR       birthYearString[10];
  TCHAR       memberName[20];
  TCHAR       phoneNumber[20];
  TCHAR       memberEntry[100];

  switch(iMessage) {
    case WM_INITDIALOG:
      hCombo = GetDlgItem(hDlgWnd, IDC_COMBO_LIST);
      hList  = GetDlgItem(hDlgWnd, IDC_LIST_NAME);
      hBirthYearCombo = GetDlgItem(hDlgWnd, IDC_COMBO_BIRTHYEAR);
      hListMembers = GetDlgItem(hDlgWnd, IDC_LIST_MEMBERS);
      CheckRadioButton(hDlgWnd, IDC_RECT, IDC_ELLIPSE, IDC_RECT);
      CheckRadioButton(hDlgWnd, IDC_R_GENDER_MALE, IDC_R_GENDER_UNKNOWN, IDC_R_GENDER_UNKNOWN);
      for(int i = BIRTH_YEAR_START; i < BIRTH_YEAR_END; i++) {
        TCHAR birthY[5];
        wsprintf(birthY, TEXT("%d"), i);
        SendMessage(hBirthYearCombo, CB_ADDSTRING, 0, (LPARAM)birthY);
      }
      shape = TRUE;
      return (INT_PTR)TRUE;
    case WM_COMMAND:
      switch(LOWORD(wParam)) {
        case IDC_INSERT:
          /* GetDlgItemText(hDlgWnd, IDC_NAME, name, 20);
          if(lstrcmp(name, TEXT(""))) {
            SendMessage(hCombo, CB_ADDSTRING, 0, (LPARAM) name);
            SendMessage(hList,  LB_ADDSTRING, 0, (LPARAM) name);
            SetDlgItemText(hDlgWnd, IDC_NAME, TEXT(""));
          } */

          GetDlgItemText(hDlgWnd, IDC_NAME, memberName, 20);
          GetDlgItemText(hDlgWnd, IDC_PHONENUMBER, phoneNumber, 20);
          if(lstrcmp(memberName, TEXT("")) && lstrcmp(phoneNumber, TEXT(""))) {
            if(selectedGender == MALE) genderString = TEXT("남성");
            else if(selectedGender == FEMALE) genderString = TEXT("여성");
            else genderString = TEXT("무응답");

            wsprintf(birthYearString, TEXT("%d년생"), BIRTH_YEAR_START + birthYearSelection);
            wsprintf(memberEntry, TEXT("%s   %s   %s   %s"), memberName, birthYearString, genderString, phoneNumber);
            SendMessage(hListMembers, LB_ADDSTRING, 0, (LPARAM)memberEntry);

            SetDlgItemText(hDlgWnd, IDC_NAME, TEXT(""));
            SetDlgItemText(hDlgWnd, IDC_PHONENUMBER, TEXT(""));
          }
          break;
        case IDC_DELETE:
          SendMessage(hCombo, CB_DELETESTRING, comboSelection, 0);
          SendMessage(hList,  LB_DELETESTRING, listSelection, 0);
          SendMessage(hListMembers, LB_DELETESTRING, listMemberSelection, 0);
          break;
        case IDC_COMBO_LIST:
          if(HIWORD(wParam) == CBN_SELCHANGE) {
            comboSelection = SendMessage(hCombo, CB_GETCURSEL, 0, 0);
          }
          break;
        case IDC_LIST_NAME:
          if(HIWORD(wParam) == LBN_SELCHANGE) {
            listSelection = SendMessage(hList, LB_GETCURSEL, 0, 0);
          }
          break;
        case IDC_LIST_MEMBERS:
          if(HIWORD(wParam) == LBN_SELCHANGE) {
            listMemberSelection = SendMessage(hListMembers, LB_GETCURSEL, 0, 0);
          }
        case IDC_COMBO_BIRTHYEAR:
          if(HIWORD(wParam) == CBN_SELCHANGE) {
            birthYearSelection = SendMessage(hBirthYearCombo, CB_GETCURSEL, 0, 0);
          }
          break;
        case IDC_RECT:
          shape = TRUE;
          break;
        case IDC_ELLIPSE:
          shape = FALSE;
          break;
        case IDC_R_GENDER_MALE: selectedGender = MALE; break;
        case IDC_R_GENDER_FEMALE: selectedGender = FEMALE; break;
        case IDC_R_GENDER_UNKNOWN: selectedGender = UNKNOWN; break;
        case IDOK:
          break;
        case IDCANCEL:
          EndDialog(hDlgWnd, 0);
          break;
      }
      InvalidateRect(hDlgWnd, NULL, TRUE);
      break;
    case WM_PAINT:
      hdc = BeginPaint(hDlgWnd, &ps);
      if(shape) {
        Rectangle(hdc, box.left, box.top, box.right, box.bottom);
      } else {
        Ellipse(hdc, box.left, box.top, box.right, box.bottom);
      }
      EndPaint(hDlgWnd, &ps);
      break;
  }

  return (INT_PTR)FALSE;
}