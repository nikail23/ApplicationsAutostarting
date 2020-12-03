#pragma once
#include <windows.h>

class AutostartListView
{
	private:
		HWND hWndLV;
		HWND CreateListView(HWND hWndParent, int x, int y, int width, int height, UINT uId);
	public:
		AutostartListView();
		AutostartListView(HWND hWndParent, int x, int y, int width, int height);
		BOOL AddListViewItems(int colNum, int textMaxLen, const char** item);
		int SetListViewColumns(int colNum, int textMaxLen, const char** header);
		void Show();
};

class AddAppButtonView 
{
	private:
		HWND hWndButton;
	public:
		AddAppButtonView();
		AddAppButtonView(HWND parent, int x, int y, int width, int height);
		void Show();
};

class RemoveAppButtonView
{
private:
	HWND hWndButton;
public:
	RemoveAppButtonView();
	RemoveAppButtonView(HWND parent, int x, int y, int width, int height);
	void Show();
};

