#include "stdafx.h"
#include "CTabView.h"

CTabView::CTabView()
{
}

CTabView::~CTabView()
{
}
HWND CTabView::InitTab(HWND hWnd, HINSTANCE g_hInst)
{
	HWND hTab = CreateWindowExW(0, WC_TABCONTROL, _T(""), WS_CHILD | WS_VISIBLE,
		500, 53, 225, 30,
		hWnd, (HMENU)IDC_MAIN_TABCTRL, NULL, NULL);
	/*HWND hTab = CreateWindow(WC_TABCONTROL, NULL, WS_CHILD | WS_CLIPSIBLINGS | WS_VISIBLE, 500, 53, 225, 30, hWnd,
		(HMENU)IDC_MAIN_TABCTRL, g_hInst, NULL);*/
	//TCHAR *tabString[4] = { const_cast<TCHAR*> (TEXT("Details")),  const_cast<TCHAR*> (TEXT("List")),
	//	 const_cast<TCHAR*> (TEXT("Icons")),  const_cast<TCHAR*> (TEXT("Tiles")) };
	//TCITEM tie;
	//tie.mask = TCIF_TEXT | TCIF_IMAGE;
	//tie.iImage = -1;
	//for (int i = 0; i < 4; i++)
	//{
	//	tie.pszText = tabString[i];
	//	SendMessage(hWnd, TCM_INSERTITEM, 0, (LPARAM)&tie);
	//}
	TCITEM tie;
	TCHAR Titles[] = _T("Titles");
	TCHAR Icons[] = _T("Icons");
	TCHAR Lists[] = _T("Lists");
	TCHAR Details[] = _T("Details");
	INITCOMMONCONTROLSEX icex;
	icex.dwSize = sizeof(INITCOMMONCONTROLSEX);
	icex.dwICC = ICC_TAB_CLASSES;
	//INITCOMMONCONTROLSEX(icex);
	
	tie.mask = TCIF_TEXT;
	tie.pszText = Titles;
	SendMessage(hTab, TCM_INSERTITEM, 0, (LPARAM)&tie);
	tie.pszText = Icons;
	SendMessage(hTab, TCM_INSERTITEM, 1, (LPARAM)&tie);
	tie.pszText = Lists;
	SendMessage(hTab, TCM_INSERTITEM, 2, (LPARAM)&tie);
	tie.pszText = Details;
	SendMessage(hTab, TCM_INSERTITEM, 3, (LPARAM)&tie);
	return hTab;
}
void OnSelchangeTabCtrlMode(HWND hWnd1, HWND hWnd2)
{
	LONG lStyle;
	int iIndex = -1;
	lStyle = GetWindowLong(hWnd1, GWL_STYLE);
	lStyle &= ~LVS_TYPEMASK;	// delete the old style
	iIndex = SendMessage(hWnd2, TCM_GETCURSEL, 0, 0);
	switch (iIndex)
	{
	case 0:
		lStyle |= LVS_EDITLABELS;		// icon style
		break;
	case 1:
		lStyle |= LVS_SMALLICON;	// detail style
		break;
	case 2:
		lStyle |= LVS_LIST;	 // detail style
		break;
	case 3:
		lStyle |= LVS_REPORT;	// detail style
		break;
	}
	SetWindowLong(hWnd1, GWL_STYLE, lStyle);	// set the new style
}
void CTabView::size(HWND hWnd)
{
	RECT rect;
	GetClientRect(hWnd, &rect);
	HWND hTab = GetDlgItem(hWnd, IDC_MAIN_TABCTRL);
	SetWindowPos(hTab, NULL, rect.right - 500, rect.top + 60, 225, 23, SWP_NOZORDER);
}