#pragma once
#include <windows.h>

class ListView
{
	private:
		HWND hWndLV;
		HWND CreateListView(HWND hWndParent, int x, int y, int width, int height, UINT uId);
	public:
		ListView();
		ListView(HWND hWndParent, int x, int y, int width, int height);
		BOOL AddListViewItems(int colNum, int textMaxLen, const char** item);
		int SetListViewColumns(int colNum, int textMaxLen, const char** header);
		void Show();
};

