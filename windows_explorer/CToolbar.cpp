#include "stdafx.h"
#include "CToolbar.h"

CToolbar::CToolbar()
{
}

CToolbar::~CToolbar()
{
}
void CToolbar::CreatToolbar(HWND hWnd)
{
	 HWND hTool = CreateWindowEx(0, TOOLBARCLASSNAME, NULL, WS_CHILD | WS_VISIBLE, 0, 0, 0, 0, hWnd,
		(HMENU)IDC_MAIN_TOOL, GetModuleHandle(NULL), NULL);
	SendMessage(hTool, TB_BUTTONSTRUCTSIZE, (WPARAM)sizeof(TBBUTTON), 0);
	TBBUTTON tbb[2];
	TBADDBITMAP tbad;
	tbad.hInst = HINST_COMMCTRL;
	tbad.nID = IDB_HIST_SMALL_COLOR;
	SendMessage(hTool, TB_ADDBITMAP, 0, (LPARAM)&tbad);
	ZeroMemory(tbb, sizeof(tbb));
	tbb[0].iBitmap = HIST_BACK;
	tbb[0].fsState = TBSTATE_ENABLED;
	tbb[0].fsStyle = TBSTYLE_BUTTON;
	tbb[0].idCommand = ID_BACK;

	tbb[1].iBitmap = HIST_FORWARD;
	tbb[1].fsState = TBSTATE_ENABLED;
	tbb[1].fsStyle = TBSTYLE_BUTTON;
	tbb[1].idCommand = ID_FORWARD;
	SendMessage(hTool, TB_ADDBUTTONS, sizeof(tbb) / sizeof(TBBUTTON), (LPARAM)& tbb);
}
void CToolbar::size(HWND hWnd)
{
	HWND hTool = GetDlgItem(hWnd, IDC_MAIN_TOOL);
	SendMessage(hTool, TB_AUTOSIZE, 0, 0);
}