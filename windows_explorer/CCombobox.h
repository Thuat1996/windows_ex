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
	void AddText(HWND, TCHAR*); // lay text tu treeview, list view gui len

};

