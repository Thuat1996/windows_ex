#pragma once
#include "stdafx.h"
#define  IDC_MAIN_LISTVIEW 5
class CListview
{
public:
	CListview();
	~CListview();
	HWND CreatListview(HWND);
	void size(HWND,HWND);
	void AddColumn(HWND, TCHAR*, int);
	void CreateList(HWND);
	void LoadFolder(HWND, TCHAR*);
	void AddSubItemFolder(HWND, int, int, TCHAR*);// them phan tu con thuoc folder
	void AddSubItemFile(HWND, int, int, TCHAR*); // them phan tu con thuoc file
	void AddItemFile(HWND, int, TCHAR*, TCHAR*, TCHAR*,TCHAR*);
	void AddItemFolder(HWND, int, TCHAR*, TCHAR*, TCHAR*, TCHAR*);
	void DeleteList(HWND);
	void Clear(HWND);
	void SetImageList(HWND);
	void onDBClick(HWND,CCombobox*); // bat su kien double click de mo file va folder
	void onClick(HWND, CCombobox*);//bat su kien khi click vao listview
	void SortList(HWND hList, HWND hSortBy);
};
int CALLBACK ListView_CompareName(LPARAM index1, LPARAM index2, LPARAM lParam);

int CALLBACK ListView_CompareSize(LPARAM index1, LPARAM index2, LPARAM lParam);

int CALLBACK ListView_CompareType(LPARAM index1, LPARAM index2, LPARAM lParam);
LPWSTR getDateModified(FILETIME ftLastWrite);