#pragma once
#include "stdafx.h"
#define  IDC_MAIN_LISTVIEW 5
class CListview
{
public:
	CListview();
	~CListview();
	HWND CreatListview(HWND);
	void size(HWND);
};

