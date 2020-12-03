#include <windows.h>
#include "ListView.h";

const int START_WINDOW_HEIGHT = 450;
const int START_WINDOW_WIDTH = 640;
const char* WINDOW_CAPTION = "ApplicationAutostarting";

const int LIST_VIEW_X = 20;
const int LIST_VIEW_Y = 20;
const int LIST_VIEW_WIDTH = START_WINDOW_WIDTH - 3 * LIST_VIEW_X;
const int LIST_VIEW_HEIGHT = 200;

LRESULT CALLBACK WndProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam) {
	ListView listView;

	int const colNum = 2;
	int const itemNum = 3;
	int const textMaxLen = 10;
	const char* header[colNum] = { "�������� ����������", "���� � .exe �����" };
	const char* item[itemNum][colNum] = { "00", "01", "02", "10", "11", "12" };

	switch (Message)
	{
	case WM_CREATE: {
		listView = ListView(hwnd, LIST_VIEW_X, LIST_VIEW_Y, LIST_VIEW_WIDTH, LIST_VIEW_HEIGHT);
		listView.SetListViewColumns(colNum, textMaxLen, header);
		listView.AddListViewItems(colNum, textMaxLen, item[0]);
		listView.AddListViewItems(colNum, textMaxLen, item[1]);
		listView.AddListViewItems(colNum, textMaxLen, item[2]);
		listView.Show();
		break;
	}
	case WM_DESTROY: {
		PostQuitMessage(0);
		break;
	}
	default:
		return DefWindowProc(hwnd, Message, wParam, lParam);
	}
	return 0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	WNDCLASSEX wc;
	HWND hMainWnd;
	MSG msg;

	memset(&wc, 0, sizeof(wc));
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.lpfnWndProc = WndProc;
	wc.hInstance = hInstance;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.cbWndExtra = NULL;
	wc.cbClsExtra = NULL;
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wc.lpszClassName = "ApplicationAutostart";
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

	if (!RegisterClassEx(&wc)) {
		MessageBox(NULL, "Window Registration Failed!", "Error!", MB_ICONEXCLAMATION | MB_OK);
		return 0;
	}

	hMainWnd = CreateWindowEx(WS_EX_CLIENTEDGE, "ApplicationAutostart", WINDOW_CAPTION, WS_VISIBLE | WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		START_WINDOW_WIDTH,
		START_WINDOW_HEIGHT,
		NULL, NULL, HINSTANCE(hInstance), NULL);

	if (hMainWnd == NULL) {
		MessageBox(NULL, "Window Creation Failed!", "Error!", MB_ICONEXCLAMATION | MB_OK);
		return 0;
	}

	ShowWindow(hMainWnd, nCmdShow);
	UpdateWindow(hMainWnd);

	while (GetMessage(&msg, NULL, 0, 0) > 0)
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return msg.wParam;
}

