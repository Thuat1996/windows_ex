#pragma once
#include "stdafx.h"
#define IDM_FILE_OPEN 10
#define IDM_FILE_CUT 11
#define IDM_FILE_COPY 12
#define IDM_FILE_PASTE 13
#define IDM_FILE_DELETE 14
#define IDM_FILE_RENAME 15
#define IDM_FILE_PROPERTIES 16
#define IDM_FILE_REFRESH 17
#define IDM_FILE_NEW 18
#define IDM_FILE_VIEW 19

class CMenu
{
public:
	CMenu();
	~CMenu();
	void CreateMenuTree(HWND,LPARAM);
	void CreateMenuList(HWND,LPARAM);
};

