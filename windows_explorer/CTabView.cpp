#include "stdafx.h"
#include "CTabView.h"

CTabView::CTabView()
{
}

CTabView::~CTabView()
{
}
void CTabView::InitTab(HWND hWnd, HINSTANCE g_hInst)
{
	TCITEM tie;
	TCHAR Titles[] = _T("Titles");
	TCHAR Icons[] = _T("Icons");
	TCHAR Lists[] = _T("Lists");
	TCHAR Details[] = _T("Details");
	INITCOMMONCONTROLSEX icex;
	icex.dwSize = sizeof(INITCOMMONCONTROLSEX);
	icex.dwICC = ICC_TAB_CLASSES;
	//INITCOMMONCONTROLSEX(icex);
	HWND hTab = CreateWindow(WC_TABCONTROL, NULL, WS_CHILD | WS_CLIPSIBLINGS | WS_VISIBLE, 500, 53, 225, 30, hWnd,
		(HMENU)IDC_MAIN_TABCTRL, g_hInst, NULL);
	tie.mask = TCIF_TEXT;
	tie.pszText = Titles;
	SendMessage(hTab, TCM_INSERTITEM, 1, (LPARAM)(LPTCITEM)&tie);
	tie.pszText = Icons;
	SendMessage(hTab, TCM_INSERTITEM, 2, (LPARAM)(LPTCITEM)&tie);
	tie.pszText = Lists;
	SendMessage(hTab, TCM_INSERTITEM, 3, (LPARAM)(LPTCITEM)&tie);
	tie.pszText = Details;
	SendMessage(hTab, TCM_INSERTITEM, 4, (LPARAM)(LPTCITEM)&tie);
}
void CTabView::size(HWND hWnd)
{
	RECT rect;
	GetClientRect(hWnd, &rect);
	HWND hTab = GetDlgItem(hWnd, IDC_MAIN_TABCTRL);
	SetWindowPos(hTab, NULL, rect.right - 500, rect.top + 60, 225, 23, SWP_NOZORDER);
}