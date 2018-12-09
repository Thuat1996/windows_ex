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
#define IDM_FILE_BACK 20
#define IDM_FILE_Document 21
//list
#define IDM_FILE_OPEN1 22
#define IDM_FILE_CUT1 23
#define IDM_FILE_COPY1 24
#define IDM_FILE_PASTE1 25
#define IDM_FILE_DELETE1 26
#define IDM_FILE_RENAME1 27
#define IDM_FILE_PROPERTIES1 28


class CMenu
{
public:
	CMenu();
	~CMenu();
	void CreateMenuTree(HWND);
	void CreateMenuList(HWND);
};

