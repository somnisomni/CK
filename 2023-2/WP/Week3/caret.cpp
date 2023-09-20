#include <Windows.h>
#include <tchar.h>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

HINSTANCE g_hInst;
LPCTSTR lpszClass = TEXT("Caret");

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
		CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
		NULL, (HMENU)NULL, hInstance, NULL);
	ShowWindow(hWnd, nCmdShow);

	while(GetMessage(&Message, NULL, 0, 0)) {
		TranslateMessage(&Message);
		DispatchMessage(&Message);
	}

	return (int)Message.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam) {
#define STR_LEN 100

	HDC hdc;
	PAINTSTRUCT ps;
	static TCHAR str[STR_LEN];
	static int count;
	static SIZE size;

	RECT rt = { 0, 0, 1000, 1000 };

	switch(iMessage) {
		case WM_CREATE:
			CreateCaret(hWnd, NULL, 5, 15);
			ShowCaret(hWnd);
			count = 0;
			break;
		case WM_PAINT:
			hdc = BeginPaint(hWnd, &ps);
			SetBkMode(hdc, TRANSPARENT);
			GetTextExtentPoint(hdc, str, _tcslen(str), &size);
			TextOut(hdc, 0, 0, str, _tcslen(str));
			SetCaretPos(size.cx, 0);
			EndPaint(hWnd, &ps);
			break;
		case WM_CHAR:
			if(wParam == VK_BACK && count > 0) count--;
			else {
				if(count > STR_LEN - 2) break;

				str[count++] = wParam;
			}

			str[count] = NULL;
			InvalidateRgn(hWnd, NULL, TRUE);
			break;
		case WM_DESTROY:
			HideCaret(hWnd);
			DestroyCaret();
			PostQuitMessage(0);
			return 0;
		default:
			return (DefWindowProc(hWnd, iMessage, wParam, lParam));
	}

	return 0;
}