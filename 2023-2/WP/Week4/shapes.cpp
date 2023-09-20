#include <Windows.h>
#include <stdlib.h>
#include <time.h>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

HINSTANCE g_hInst;
LPCTSTR lpszClass = TEXT("Caret");

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

	RECT rt = { 50, 50, 400, 400 };

	switch(iMessage) {
		case WM_PAINT:
		{
			hdc = BeginPaint(hWnd, &ps);

			Rectangle(hdc, rt.left, rt.top, rt.right, rt.bottom);
			Ellipse(hdc, rt.left, rt.top, rt.right, rt.bottom);

			int center = (rt.right - rt.left) / 2 + rt.left;
			MoveToEx(hdc, center, rt.bottom, NULL);
			LineTo(hdc, center, rt.bottom + 100);
			Rectangle(hdc, rt.left, rt.bottom + 100, rt.right, rt.bottom + 150);

			int triTopX = rt.right + 300;
			int triLeftX = triTopX - 250;
			int triRightX = triTopX + 250;
			MoveToEx(hdc, triTopX, rt.top, NULL);
			LineTo(hdc, triLeftX, rt.bottom);
			LineTo(hdc, triRightX, rt.bottom);
			LineTo(hdc, triTopX, rt.top);

			const POINT tri[] = { { 500, 500 }, { 450, 550 }, { 550, 550 } };
			const POINT sqr[] = { { 600, 500 }, { 650, 500 }, { 650, 550 }, { 600, 550 } };
			const POINT pnt[] = { { 700, 500 }, { 720, 520 }, { 720, 550 }, { 680, 550 }, { 680, 520 } };
			const POINT hxa[] = { { 800, 500 }, { 820, 520 }, { 820, 540 }, { 800, 560 }, { 780, 540 }, { 780, 520 } };
			Polygon(hdc, tri, 3);
			Polygon(hdc, sqr, 4);
			Polygon(hdc, pnt, 5);
			Polygon(hdc, hxa, 6);

			EndPaint(hWnd, &ps);
			break;
		}
		case WM_DESTROY:
			PostQuitMessage(0);
			return 0;
	}

	return (DefWindowProc(hWnd, iMessage, wParam, lParam));;
}