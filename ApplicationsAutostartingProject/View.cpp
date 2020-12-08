#include "View.h"
#include <commctrl.h>
#include "InputBox.h"
#include <string>
#define IDC_LISTVIEW 1111

AutostartListView::AutostartListView() {}

AutostartListView::AutostartListView(HWND hWndParent, int x, int y, int width, int height)
{
    if ((hWnd = CreateListView(hWndParent, x, y, width, height, IDC_LISTVIEW)) == NULL)
        MessageBox(NULL, "Cant create a ListView component!", "Error!", MB_OK);
}

BOOL AutostartListView::AddListViewItems(int colNum, int textMaxLen, char** item, int rowsNum)
{
    SendMessage(hWnd, WM_SETREDRAW, FALSE, 0);

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

        if (ListView_InsertItem(hWnd, &item) == -1)
            return FALSE;

        ListView_SetItemText(hWnd, itemIndex, 1, (LPSTR)text2);
        textIndex += 2;
    }

    SendMessage(hWnd, WM_SETREDRAW, TRUE, 0);

    return TRUE;
}

int AutostartListView::SetListViewColumns(int colNum, int textMaxLen, const char** header)
{
    RECT rcl;
    GetClientRect(hWnd, &rcl);

    int index = -1;

    LVCOLUMN lvc;
    lvc.mask = LVCF_TEXT | LVCF_WIDTH;
    lvc.cx = (rcl.right - rcl.left) / colNum;
    lvc.cchTextMax = textMaxLen;

    for (int i = 0; i < colNum; i++)
    {
        lvc.pszText = (LPSTR)header[i];
        index = ListView_InsertColumn(hWnd, i, &lvc);
        if (index == -1) break;
    }

    return index;
}

int* AutostartListView::GetSelectedIndecies()
{
    int iPos = ListView_GetNextItem(hWnd, -1, LVNI_SELECTED);
    int size = 0;
    while (iPos != -1) {
        size++;
        iPos = ListView_GetNextItem(hWnd, iPos, LVNI_SELECTED);
    }

    int i = 0;
    int* selectedIndecies = new int[size + 1];
    iPos = ListView_GetNextItem(hWnd, -1, LVNI_SELECTED);
    while (iPos != -1) {
        selectedIndecies[i] = iPos;
        i++;
        iPos = ListView_GetNextItem(hWnd, iPos, LVNI_SELECTED);
    }
    selectedIndecies[i] = -1;

    return selectedIndecies;
}

void AutostartListView::Show()
{
    ShowWindow(hWnd, SW_SHOWDEFAULT);
}

void AutostartListView::Clear()
{
    SendMessage(hWnd, LVM_DELETEALLITEMS, 0, 0);
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
    hWnd = CreateWindow(
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
    ShowWindow(hWnd, SW_SHOWDEFAULT);
}

RemoveAppButtonView::RemoveAppButtonView()
{
}

RemoveAppButtonView::RemoveAppButtonView(HWND parent, int x, int y, int width, int height)
{
    hWnd = CreateWindow(
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
    ShowWindow(hWnd, SW_SHOWDEFAULT);
}

OnceAutostartCheckbox::OnceAutostartCheckbox()
{
}

OnceAutostartCheckbox::OnceAutostartCheckbox(HWND parent, int x, int y, int width, int height)
{
    hWnd = CreateWindowEx(NULL, "BUTTON", "Once autostart", WS_VISIBLE | WS_CHILD | BS_CHECKBOX, x, y, width, height, parent, (HMENU)ONCE_AUTOSTART_CHECKBOX_CODE, NULL, NULL);
}

void OnceAutostartCheckbox::Show()
{
    ShowWindow(hWnd, SW_SHOWDEFAULT);
}
