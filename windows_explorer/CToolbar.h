#pragma once
#include "stdafx.h"
#define IDC_MAIN_TOOL 101
#define  ID_BACK 103
#define  ID_FORWARD 4
class CToolbar
{
public:
	CToolbar();
	~CToolbar();
	HWND CreatToolbar(HWND hWnd);
	void size(HWND);
};

