#include <Windows.h>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

HINSTANCE g_hInst;
LPCTSTR lpszClass = TEXT("WM_CHAR");

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
	HDC hdc;
	PAINTSTRUCT ps;
	static char ch[] = "A";
	static int x = 100;
	static int y = 100;

	switch(iMessage) {
		case WM_DESTROY:
			PostQuitMessage(0);
			return 0;
		case WM_KEYDOWN:
			switch(wParam) {
				case VK_SPACE:
					// ch[0] += 1;
					// if(ch[0] > 'Z') ch[0] = 'A';
					if(ch[0] == 'A') ch[0] = 'Z';
					else ch[0] = 'A';
					break;
				case VK_LEFT:
					x -= 8;
					break;
				case VK_RIGHT:
					x += 8;
					break;
				case VK_UP:
					y -= 8;
					break;
				case VK_DOWN:
					y += 8;
					break;
			}
			InvalidateRect(hWnd, NULL, FALSE);
			return 0;
		case WM_PAINT:
			hdc = BeginPaint(hWnd, &ps);
			TextOut(hdc, x, y, LPCWSTR(ch), 1);
			EndPaint(hWnd, &ps);
			return 0;
	}

	return (DefWindowProc(hWnd, iMessage, wParam, lParam));
}