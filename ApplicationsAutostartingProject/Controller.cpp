#include <windows.h>
#include "View.h";
#include "Model.h"
#include <string>
#include "CStringArray.h"
#include "InputBox.h"

const int START_WINDOW_HEIGHT = 450;
const int START_WINDOW_WIDTH = 640;
const char* WINDOW_CAPTION = "ApplicationAutostarting";

const int LIST_VIEW_X = 20;
const int LIST_VIEW_Y = 20;
const int LIST_VIEW_WIDTH = 580;
const int LIST_VIEW_HEIGHT = 200;

char** GetTextFromAppsList(std::list<AutostartedAppInfo> appsList, int* length) {
	CStringArray stringArray = CStringArray();
	for (auto iter = appsList.begin(); iter != appsList.end(); iter++)
	{
		stringArray.Add(iter->appName);
		stringArray.Add(iter->appExePath);
	}
	*length = stringArray.count/2;
	return stringArray.Get();
}

void RefreshAppsView(AutostartListView listView, AutostartListModel listModel) {
	int const colNum = 2;
	int const itemNum = 3;
	int const textMaxLen = 30;
	const char* header[colNum] = { "APPLICATION NAME", "APPLICATION PATH" };

	listView.SetListViewColumns(colNum, textMaxLen, header);
	int rows = 0;
	char** text = GetTextFromAppsList(listModel.Get(), &rows);
	listView.AddListViewItems(colNum, textMaxLen, text, rows);
	listView.Show();
}



LRESULT CALLBACK WndProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam) {
	AutostartListView listView;
	AddAppButtonView addAppButtonView;
	RemoveAppButtonView removeAppButtonView;

	AutostartListModel listModel;

	switch (Message)
	{
	case WM_COMMAND: {
		if (LOWORD(wParam) == ADD_APP_BUTTON_CODE)
		{
			OPENFILENAME openFileName;
			char szFile[1024];
			HANDLE fileHandle;

			ZeroMemory(&openFileName, sizeof(openFileName));
			openFileName.lStructSize = sizeof(openFileName);
			openFileName.hwndOwner = NULL;
			openFileName.lpstrFile = szFile;
			openFileName.lpstrFile[0] = '\0';
			openFileName.nMaxFile = sizeof(szFile);
			openFileName.lpstrFilter = "Exe files!\0*.exe\0";
			openFileName.nFilterIndex = 1;
			openFileName.lpstrFileTitle = NULL;
			openFileName.nMaxFileTitle = 0;
			openFileName.lpstrInitialDir = NULL;
			openFileName.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

			if (GetOpenFileName(&openFileName) == TRUE)
			{
				CInputBox appNameBox = CInputBox(hwnd);
				if (appNameBox.DoModal("Input your app name", "App name")) {

					char* appName = appNameBox.Text;
					char* appPath = openFileName.lpstrFile;

					AutostartedAppInfo newAppInfo = { appName, appPath };
					listModel.Add(newAppInfo);
				}
			}
		}

		if (LOWORD(wParam) == DELETE_APP_BUTTON_CODE)
		{
			// обработка удаления приложения из автозапуска
		}
		break;
	}
	case WM_CREATE: {
		listView = AutostartListView(hwnd, LIST_VIEW_X, LIST_VIEW_Y, LIST_VIEW_WIDTH, LIST_VIEW_HEIGHT);

		addAppButtonView = AddAppButtonView(hwnd, 20, 250, 280, 30);
		addAppButtonView.Show();

		removeAppButtonView = RemoveAppButtonView(hwnd, 310, 250, 280, 30);
		removeAppButtonView.Show();

		RefreshAppsView(listView, listModel);
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

