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
	void AddColumn(HWND, TCHAR*, int);
	void CreateList(HWND);
	void LoadFolder(HWND, TCHAR*);
	void AddSubItemFolder(HWND, int, int, TCHAR*);// them phan tu con thuoc folder
	void AddSubItemFile(HWND, int, int, TCHAR*); // them phan tu con thuoc file
	void AddItemFile(HWND, int, TCHAR*, TCHAR*, TCHAR*);
	void AddItemFolder(HWND, int, TCHAR*, TCHAR*, TCHAR*);
	void DeleteList(HWND);
	void Clear(HWND);
	void SetImageList(HWND);
	void onDBClick(HWND,CCombobox*); // bat su kien double click de mo file va folder
	void onClick(HWND, CCombobox*);//bat su kien khi click vao listview
};

