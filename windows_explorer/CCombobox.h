#pragma once
#include "stdafx.h"
#define  IDC_MAIN_COMBOBOX_ADD 1002
class CCombobox
{
public:
	CCombobox();
	~CCombobox();
	HWND CreateCombobox(HWND);
	void size(HWND);
};

