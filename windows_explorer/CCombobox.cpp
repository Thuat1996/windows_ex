#include "stdafx.h"
#include "CCombobox.h"
CCombobox::CCombobox()
{
}

CCombobox::~CCombobox()
{
}
HWND CCombobox::CreateCombobox(HWND hWnd)
{
	HWND hCbb = CreateWindowEx(0, _T("ComboBox"), _T(""), WS_CHILD | WS_VISIBLE | CBS_DROPDOWN, 60, 27, 800, 20, hWnd,
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
