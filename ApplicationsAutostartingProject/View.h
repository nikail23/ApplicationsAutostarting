#pragma once
#include <windows.h>
#include <string>
#define ADD_APP_BUTTON_CODE  10000
#define DELETE_APP_BUTTON_CODE  10001
#define ONCE_AUTOSTART_CHECKBOX_CODE  10002

class AutostartListView
{
	private:
		HWND hWnd;
		HWND CreateListView(HWND hWndParent, int x, int y, int width, int height, UINT uId);
	public:
		AutostartListView();
		AutostartListView(HWND hWndParent, int x, int y, int width, int height);
		BOOL AddListViewItems(int colNum, int textMaxLen, char** item, int rows);
		int SetListViewColumns(int colNum, int textMaxLen, const char** header);
		int* GetSelectedIndecies();
		void Show();
		void Clear();
};

class AddAppButtonView 
{
	private:
		HWND hWnd;
	public:
		AddAppButtonView();
		AddAppButtonView(HWND parent, int x, int y, int width, int height);
		void Show();
};

class RemoveAppButtonView
{
private:
	HWND hWnd;
public:
	RemoveAppButtonView();
	RemoveAppButtonView(HWND parent, int x, int y, int width, int height);
	void Show();
};

class OnceAutostartCheckbox 
{
	private:
		HWND hWnd;
	public:
		OnceAutostartCheckbox();
		OnceAutostartCheckbox(HWND parent, int x, int y, int width, int height);
		void Show();
};

