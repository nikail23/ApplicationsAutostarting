#include "View.h"
#include <commctrl.h>
#define IDC_LISTVIEW 1111

AutostartListView::AutostartListView() {}

AutostartListView::AutostartListView(HWND hWndParent, int x, int y, int width, int height)
{
    if ((hWndLV = CreateListView(hWndParent, x, y, width, height, IDC_LISTVIEW)) == NULL)
        MessageBox(NULL, "Cant create a ListView component!", "Error!", MB_OK);
}

BOOL AutostartListView::AddListViewItems(int colNum, int textMaxLen, const char** item)
{
    int iLastIndex = ListView_GetItemCount(hWndLV);

    LVITEM lvi;
    lvi.mask = LVIF_TEXT;
    lvi.cchTextMax = textMaxLen;
    lvi.iItem = iLastIndex;
    lvi.pszText = (LPSTR)item[0];
    lvi.iSubItem = 0;

    if (ListView_InsertItem(hWndLV, &lvi) == -1)
        return FALSE;
    for (int i = 1; i < colNum; i++)
        ListView_SetItemText(hWndLV, iLastIndex, i, (LPSTR)item[i]);

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
        NULL,       
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
        NULL,
        (HINSTANCE)GetWindowLongPtr(parent, GWLP_HINSTANCE),
        NULL);
}

void RemoveAppButtonView::Show()
{
    ShowWindow(hWndButton, SW_SHOWDEFAULT);
}
