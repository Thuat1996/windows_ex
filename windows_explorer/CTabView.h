#pragma once
#include "stdafx.h"
#define IDC_MAIN_TABCTRL 1

class CTabView
{
public:
	CTabView();
	~CTabView();
	HWND InitTab(HWND,HINSTANCE);
	void size(HWND);
};
void OnSelchangeTabCtrlMode(HWND, HWND hWnd2);
