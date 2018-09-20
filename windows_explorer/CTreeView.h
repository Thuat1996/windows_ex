#pragma once
#include "stdafx.h"
#include "windows_explorer.h"
#include "commctrl.h"
#define IDC_MAIN_TREEVIEW 4
class CTreeView
{
//protected:
//	int IDC_MAIN_TREEVIEW;
public:
	/*int getID()
	{
		return IDC_MAIN_TREEVIEW;
	}*/
	CTreeView();
	~CTreeView();
	HWND CreateTV(HWND,HINSTANCE);
	void size(HWND);
	void onSelChange(HWND); //khi click lua chon vao tree
	void OnClick(HWND);
	void LoadFolder(HWND, TCHAR*, HTREEITEM);
	void LoadDisk(HWND);
	void AddRoot(HWND, TCHAR*); // them nut cha
	void AddNote(HWND, TCHAR*, HTREEITEM);// them nut con
	void getPath(HWND, HTREEITEM, TCHAR); // ham lay duong da
};

