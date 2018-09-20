#include "stdafx.h"
#include "CListview.h"
#include <commctrl.h>

CListview::CListview()
{
}

CListview::~CListview()
{
}
HWND CListview::CreatListview(HWND hWnd)
{
	HWND hlistview = CreateWindow(WC_LISTBOX, NULL, WS_CHILD | WS_VISIBLE | LBS_NOTIFY, 350, 85, 10, 20, hWnd,
		(HMENU)IDC_MAIN_LISTVIEW, GetModuleHandle(NULL), NULL);
	return hlistview;
}
void CListview::size(HWND hWnd)
{
	RECT rect;
	GetClientRect(hWnd, &rect);
	HWND hLV = GetDlgItem(hWnd, IDC_MAIN_LISTVIEW);
	SetWindowPos(hLV, NULL, rect.right - 705, rect.top + 90, rect.right, rect.bottom - 110, SWP_NOZORDER);
}