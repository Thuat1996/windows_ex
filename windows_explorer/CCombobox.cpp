#include "stdafx.h"
#include "CCombobox.h"

//extern int g_wLinkNumber;
//extern int g_wLinkPos;
CCombobox::CCombobox()
{
}

CCombobox::~CCombobox()
{
}
HWND CCombobox::CreateCombobox(HWND hWnd)
{
	HWND hCbb = CreateWindowEx(0, _T("ComboBox"), _T(""), WS_CHILD | WS_VISIBLE | CBS_DROPDOWN| LBS_STANDARD, 60, 27, 800, 20, hWnd,
		(HMENU)IDC_MAIN_COMBOBOX_ADD, GetModuleHandle(NULL), NULL);
	return hCbb;
}
void CCombobox::size(HWND hWnd)
{
	RECT rect;
	GetClientRect(hWnd, &rect);
	HWND hcbo_add = GetDlgItem(hWnd, IDC_MAIN_COMBOBOX_ADD);
	SetWindowPos(hcbo_add, NULL, 60, rect.top + 27, rect.right - 210, 20, SWP_NOZORDER);
}
void CCombobox::AddText(HWND hWnd, TCHAR* szText)
{
	int wIndex = 0;
	//gi 1 message de add text tu treeview,list view len combobox
	SendDlgItemMessage(hWnd, IDC_MAIN_COMBOBOX_ADD, CB_ADDSTRING, 0, (LPARAM)szText);
	//gan bien wIndex bang ham getcount
	wIndex = SendDlgItemMessage(hWnd, IDC_MAIN_COMBOBOX_ADD, CB_GETCOUNT, 0, wIndex);
	//dat gia tri default cho combobox
	SendDlgItemMessage(hWnd, IDC_MAIN_COMBOBOX_ADD, CB_SETCURSEL, wIndex - 1 , 0);
	//g_wLinkNumber++;
}
