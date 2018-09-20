#pragma once
#include "stdafx.h"
#define IDC_MAIN_TABCTRL 1

class CTabView
{
public:
	CTabView();
	~CTabView();
	void InitTab(HWND,HINSTANCE);
	void size(HWND);
};

