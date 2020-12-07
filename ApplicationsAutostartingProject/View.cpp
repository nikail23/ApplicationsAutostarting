#include "View.h"
#include <commctrl.h>
#define IDC_LISTVIEW 1111

AutostartListView::AutostartListView() {}

AutostartListView::AutostartListView(HWND hWndParent, int x, int y, int width, int height)
{
    if ((hWndLV = CreateListView(hWndParent, x, y, width, height, IDC_LISTVIEW)) == NULL)
        MessageBox(NULL, "Cant create a ListView component!", "Error!", MB_OK);
}

BOOL AutostartListView::AddListViewItems(int colNum, int textMaxLen, char** item, int rowsNum)
{
    int textIndex = 0;
    for (int itemIndex = 0; itemIndex < rowsNum; itemIndex++) {
        char* text1 = item[textIndex];
        char* text2 = item[textIndex + 1];

        LVITEM item;
        item.mask = LVIF_TEXT;
        item.cchTextMax = textMaxLen;
        item.iItem = itemIndex;
        item.pszText = text1;
        item.iSubItem = 0;

        if (ListView_InsertItem(hWndLV, &item) == -1)
            return FALSE;

        ListView_SetItemText(hWndLV, itemIndex, 1, (LPSTR)text2);
        textIndex += 2;
    }

    return TRUE;
}

int AutostartListView::SetListViewColumns(int colNum, int textMaxLen, const char** header)
{
    RECT rcl;
    GetClientRect(hWndLV, &rcl);

    int index = -1;

    LVCOLUMN lvc;
    lvc.mask = LVCF_TEXT | LVCF_WIDTH;
    lvc.cx = (rcl.right - rcl.left) / colNum;
    lvc.cchTextMax = textMaxLen;

    for (int i = 0; i < colNum; i++)
    {
        lvc.pszText = (LPSTR)header[i];
        index = ListView_InsertColumn(hWndLV, i, &lvc);
        if (index == -1) break;
    }

    return index;
}

void AutostartListView::Show()
{
    ShowWindow(hWndLV, SW_SHOWDEFAULT);
}

HWND AutostartListView::CreateListView(HWND hWndParent, int x, int y, int width, int height, UINT uId)
{
    INITCOMMONCONTROLSEX icex;
    icex.dwSize = sizeof(INITCOMMONCONTROLSEX);
    icex.dwICC = ICC_LISTVIEW_CLASSES;
    InitCommonControlsEx(&icex);

    RECT rcl;
    GetClientRect(hWndParent, &rcl);

    HWND hWndLV = CreateWindow(WC_LISTVIEW, "",
        WS_CHILD | LVS_REPORT,
        x, y, width, height,
        hWndParent, (HMENU)uId, GetModuleHandle(NULL), NULL);

    ListView_SetExtendedListViewStyleEx(hWndLV, 0, LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);

    return (hWndLV);
}

AddAppButtonView::AddAppButtonView() {}

AddAppButtonView::AddAppButtonView(HWND parent, int x, int y, int width, int height)
{
    hWndButton = CreateWindow(
        "BUTTON",  
        "Add app to autoload",      
        WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,  
        x,         
        y,        
        width,        
        height,        
        parent,     
        (HMENU)ADD_APP_BUTTON_CODE,       
        (HINSTANCE)GetWindowLongPtr(parent, GWLP_HINSTANCE),
        NULL);      
}

void AddAppButtonView::Show()
{
    ShowWindow(hWndButton, SW_SHOWDEFAULT);
}

RemoveAppButtonView::RemoveAppButtonView()
{
}

RemoveAppButtonView::RemoveAppButtonView(HWND parent, int x, int y, int width, int height)
{
    hWndButton = CreateWindow(
        "BUTTON",
        "Remove selected app from autoload",
        WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
        x,
        y,
        width,
        height,
        parent,
        (HMENU)DELETE_APP_BUTTON_CODE,
        (HINSTANCE)GetWindowLongPtr(parent, GWLP_HINSTANCE),
        NULL);
}

void RemoveAppButtonView::Show()
{
    ShowWindow(hWndButton, SW_SHOWDEFAULT);
}
