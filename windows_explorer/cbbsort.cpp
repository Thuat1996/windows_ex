#include "stdafx.h"
#include "cbbsort.h"


HWND cbbsort::createcbbsort(HWND hWnd)
{
	HWND hCbb1 = CreateWindow(_T("COMBOBOX"), _T(""), WS_BORDER | WS_CHILD | WS_VISIBLE | CBS_DROPDOWN | LBS_STANDARD,
		640, 54, 150, 100, hWnd, (HMENU)IDC_MAIN_COMBOBOX_SORT, NULL, NULL);
	/*HWND hCbb1 = CreateWindowEx(0, _T("ComboBox"), _T(""), WS_CHILD | WS_VISIBLE | CBS_DROPDOWN| LBS_STANDARD, 870, 60, 100, 23, hWnd,
		(HMENU)IDC_MAIN_COMBOBOX_SORT, GetModuleHandle(NULL), NULL);*/
	SendMessage(hCbb1, CB_ADDSTRING, 0, (LPARAM)TEXT("Name"));//sort theo "Name"       
	SendMessage(hCbb1, CB_ADDSTRING, 1, (LPARAM)TEXT("Size"));//sort theo "Size"
	SendMessage(hCbb1, CB_ADDSTRING, 2, (LPARAM)TEXT("Type"));//sort theo "Type"
	return hCbb1;
}

cbbsort::cbbsort()
{
}

cbbsort::~cbbsort()
{
}
