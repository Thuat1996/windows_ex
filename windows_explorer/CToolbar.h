#pragma once
#include "stdafx.h"
#define IDC_MAIN_TOOL 101
#define  ID_BACK 103
#define  ID_FORWARD 100004
class CToolbar
{
public:
	CToolbar();
	~CToolbar();
	void CreatToolbar(HWND hWnd);
	void size(HWND);
};

