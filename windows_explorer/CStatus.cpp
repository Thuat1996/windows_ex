#include "stdafx.h"
#include "CStatus.h"


CStatus::CStatus()
{
}

CStatus::~CStatus()
{
}
HWND CStatus::CreateStatus(HWND hWnd)
{
	HWND hStatus = CreateWindowEx(0, STATUSCLASSNAME, NULL, WS_CHILD | WS_VISIBLE, 0, 0, 0, 0, hWnd,
		(HMENU)IDC_STATUS, GetModuleHandle(NULL), NULL);
	SendMessage(hStatus, SB_SETPARTS, -1, -1);
	SendMessage(hStatus, SB_SETTEXT, 0, (LPARAM)_T("Hello"));
	return hStatus;
}
void CStatus::size(HWND hWnd)
{
	HWND hStatus = GetDlgItem(hWnd, IDC_STATUS);
	SendMessage(hStatus, WM_SIZE, 0, 0);
}
