// Provided by the lecture

#include "util.h"

#include <Windows.h>
#include <assert.h>
#include <wincon.h>

#pragma warning(disable:4996)

static int g_nScreenIndex;
static HANDLE g_hScreen[2];


wchar_t *CharToWChar(const char *pstrSrc) {
  assert(pstrSrc);
  int nLen = strlen(pstrSrc) + 1;

  wchar_t *pwstr = (LPWSTR)malloc(sizeof(wchar_t) * nLen);
  mbstowcs(pwstr, pstrSrc, nLen);

  return pwstr;
}


//wchar_t ���� char ���� ����ȯ �Լ�

char *ConvertWCtoC(const wchar_t *str) {
  //��ȯ�� char* ���� ����
  char *pStr;

  //�Է¹��� wchar_t ������ ���̸� ����
  int strSize = WideCharToMultiByte(CP_ACP, 0, str, -1, NULL, 0, NULL, NULL);
  //char* �޸� �Ҵ�
  pStr = new char[strSize];

  //�� ��ȯ 
  WideCharToMultiByte(CP_ACP, 0, str, -1, pStr, strSize, 0, 0);
  return pStr;
}



void gotoxy(int x, int y) {
  SHORT tx = static_cast<SHORT>(x);
  SHORT ty = static_cast<SHORT>(y);
  COORD CursorPosition = { tx, ty };
  SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), CursorPosition);
}



void ScreenInit() {
  CONSOLE_CURSOR_INFO cci;

  // ȭ�� ���� 2���� �����.
  g_hScreen[0] = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0,
    NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
  g_hScreen[1] = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0,
    NULL, CONSOLE_TEXTMODE_BUFFER, NULL);

  // Ŀ�� �����
  cci.dwSize = 1;
  cci.bVisible = FALSE;
  SetConsoleCursorInfo(g_hScreen[0], &cci);
  SetConsoleCursorInfo(g_hScreen[1], &cci);

}

void ScreenFlipping() {
  SetConsoleActiveScreenBuffer(g_hScreen[g_nScreenIndex]);
  g_nScreenIndex = !g_nScreenIndex;
}

void ScreenClear(int width, int height) {
  COORD Coord = { 0, 0 };
  DWORD dw;
  width *= 2;
  height *= 2;
  FillConsoleOutputCharacterW(g_hScreen[g_nScreenIndex], L' ', width * height, Coord, &dw);
  //     FillConsoleOutputCharacter( g_hScreen[g_nScreenIndex], ' ', 80*25, Coord, &dw );
}

void ScreenRelease() {
  CloseHandle(g_hScreen[0]);
  CloseHandle(g_hScreen[1]);
}

//void ScreenPrint(int x, int y, const char* string)
void ScreenPrint(int x, int y, const wchar_t *string) {
  DWORD dw;
  SHORT tx = static_cast<SHORT>(x);
  SHORT ty = static_cast<SHORT>(y);
  COORD CursorPosition = { tx * 2, ty };

  //DWORD dw2;
  //if (!WriteConsoleOutputCharacterW(g_hScreen[g_nScreenIndex], string, wcslen(string), CursorPosition, &dw))
  //{
  //    dw2 = GetLastError();
  //}
  SetConsoleCursorPosition(g_hScreen[g_nScreenIndex], CursorPosition);
  char *str = ConvertWCtoC(string);
  WriteFile(g_hScreen[g_nScreenIndex], str, strlen(str), &dw, NULL);
  //     WriteFile(g_hScreen[g_nScreenIndex], string, wcslen(string), &dw, NULL);


 //     SetConsoleCursorPosition(g_hScreen[g_nScreenIndex], CursorPosition);
 //     WriteFile( g_hScreen[g_nScreenIndex], string, wcslen( string ), &dw, NULL );
}

// 0 ~ 15 ���� ���� ���� ����
void SetColor(unsigned short color) {
  SetConsoleTextAttribute(g_hScreen[g_nScreenIndex], color);
}
