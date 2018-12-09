#include "stdafx.h"
#include "CMenu.h"

CMenu::CMenu()
{
}
CMenu::~CMenu()
{
}
void CMenu::CreateMenuTree(HWND hWnd)
{
	static POINT m_rclick;
	GetCursorPos(&m_rclick); // lay toa do chuot
	HMENU hMenu = CreatePopupMenu();
	AppendMenu(hMenu, MF_STRING, IDM_FILE_CUT, TEXT("Cut"));
	AppendMenu(hMenu, MF_STRING, IDM_FILE_COPY, TEXT("Copy"));
	AppendMenu(hMenu, MF_STRING, IDM_FILE_DELETE, TEXT("Delete"));
	AppendMenu(hMenu, MF_STRING, IDM_FILE_RENAME, TEXT("Rename"));
	AppendMenu(hMenu, MF_STRING, IDM_FILE_PROPERTIES, TEXT("Properties"));
	// hien thi popup menu tai vi tri click chuot
	//SetForegroundWindow(hWnd);
	TrackPopupMenu(hMenu, TPM_LEFTALIGN |TPM_LEFTBUTTON, m_rclick.x, m_rclick.y, 0, hWnd, NULL);
	DestroyMenu(hMenu);
}
void CMenu::CreateMenuList(HWND hWnd)
{
	HMENU hMenu = CreatePopupMenu();
	POINT m_rclick;
	GetCursorPos(&m_rclick);
	AppendMenu(hMenu, MF_STRING, IDM_FILE_NEW, TEXT("New Folder\t\t\t>"));
	AppendMenu(hMenu, MF_STRING, IDM_FILE_OPEN1, TEXT("Open"));
	AppendMenu(hMenu, MF_STRING, IDM_FILE_REFRESH, TEXT("Refresh"));
	AppendMenu(hMenu, MF_STRING, IDM_FILE_CUT1, TEXT("Cut"));
	AppendMenu(hMenu, MF_STRING, IDM_FILE_COPY1, TEXT("Copy"));
	AppendMenu(hMenu, MF_STRING, IDM_FILE_PASTE1, TEXT("Paste"));
	AppendMenu(hMenu, MF_STRING, IDM_FILE_DELETE1, TEXT("Delete"));
	AppendMenu(hMenu, MF_STRING, IDM_FILE_RENAME1, TEXT("Rename"));
	AppendMenu(hMenu, MF_STRING, IDM_FILE_PROPERTIES1, TEXT("Properties"));
	// hien thi popup menu tai vi tri click chuot
	TrackPopupMenu(hMenu, TPM_LEFTALIGN, m_rclick.x, m_rclick.y, 0, hWnd, NULL);
	DestroyMenu(hMenu);
}
