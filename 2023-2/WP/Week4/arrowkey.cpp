#include <Windows.h>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

HINSTANCE g_hInst;
LPCTSTR lpszClass = TEXT("ArrowKey");

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
	HPEN myPen, oldPen;
	HBRUSH myBrush, oldBrush;

	RECT rTop = { 150, 50, 250, 150 };
	RECT rLeft = { 50, 150, 150, 250 };
	RECT rRight = { 250, 150, 350, 250 };
	RECT rBottom = { 150, 250, 250, 350 };

	const wchar_t *tTop = TEXT("위쪽");
	const wchar_t *tLeft = TEXT("왼쪽");
	const wchar_t *tRight = TEXT("오른쪽");
	const wchar_t *tBottom = TEXT("아래쪽");

	// UP, LEFT, RIGHT, BOTTOM
	static bool keys[] = { false, false, false, false };

	switch(iMessage) {
		case WM_PAINT:
		{
			hdc = BeginPaint(hWnd, &ps);
			myBrush = CreateSolidBrush(RGB(255, 255, 255));
			oldBrush = (HBRUSH)SelectObject(hdc, myBrush);
			myPen = CreatePen(PS_SOLID, 5, RGB(0, 0, 0));
			oldPen = (HPEN)SelectObject(hdc, myPen);

			if(keys[0]) SelectObject(hdc, myBrush);
			Rectangle(hdc, rTop.left, rTop.top, rTop.right, rTop.bottom);
			TextOut(hdc, rTop.left + 30, rTop.top + 30, tTop, wcslen(tTop));
			SelectObject(hdc, oldBrush);

			Rectangle(hdc, rLeft.left, rLeft.top, rLeft.right, rLeft.bottom);
			TextOut(hdc, rLeft.left + 30, rLeft.top + 30, tLeft, wcslen(tLeft));

			Rectangle(hdc, rRight.left, rRight.top, rRight.right, rRight.bottom);
			TextOut(hdc, rRight.left + 30, rRight.top + 30, tRight, wcslen(tRight));

			Rectangle(hdc, rBottom.left, rBottom.top, rBottom.right, rBottom.bottom);
			TextOut(hdc, rBottom.left + 30, rBottom.top + 30, tBottom, wcslen(tBottom));

			EndPaint(hWnd, &ps);
			break;
		}
		case WM_KEYDOWN:
			keys[0] = wParam == VK_UP;
			keys[1] = wParam == VK_LEFT;
			keys[2] = wParam == VK_RIGHT;
			keys[3] = wParam == VK_DOWN;
			InvalidateRect(hWnd, NULL, TRUE);
			break;
		case WM_DESTROY:
			PostQuitMessage(0);
			return 0;
	}

	return (DefWindowProc(hWnd, iMessage, wParam, lParam));;
}