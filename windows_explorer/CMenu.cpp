#include "stdafx.h"
#include "CMenu.h"

CMenu::CMenu()
{
}
CMenu::~CMenu()
{
}
void CMenu::CreateMenuTree(HWND hWnd, LPARAM lParam)
{
	HMENU hMenu;
	POINT m_rclick;
	m_rclick.x = LOWORD(lParam);
	m_rclick.y = HIWORD(lParam);
	hMenu = CreatePopupMenu();
	ClientToScreen(hWnd, &m_rclick);
	AppendMenu(hMenu, MF_STRING, IDM_FILE_OPEN, TEXT("Open"));
	AppendMenu(hMenu, MF_STRING, IDM_FILE_CUT, TEXT("Cut"));
	AppendMenu(hMenu, MF_STRING, IDM_FILE_COPY, TEXT("Copy"));
	AppendMenu(hMenu, MF_STRING, IDM_FILE_PASTE, TEXT("Paste"));
	AppendMenu(hMenu, MF_STRING, IDM_FILE_DELETE, TEXT("Delete"));
	AppendMenu(hMenu, MF_STRING, IDM_FILE_RENAME, TEXT("Rename"));
	AppendMenu(hMenu, MF_STRING, IDM_FILE_PROPERTIES, TEXT("Properties"));
	// hien thi popup menu tai vi tri click chuot
	TrackPopupMenu(hMenu, TPM_RIGHTBUTTON, m_rclick.x, m_rclick.y, 0, hWnd, NULL);
	DestroyMenu(hMenu);
}
void CMenu::CreateMenuList(HWND hWnd, LPARAM lParam)
{
	HMENU hMenu;
	POINT m_rclick;
	m_rclick.x = LOWORD(lParam);
	m_rclick.y = HIWORD(lParam);
	hMenu = CreatePopupMenu();
	ClientToScreen(hWnd, &m_rclick);
	AppendMenu(hMenu, MF_STRING, IDM_FILE_VIEW, TEXT("View"));
	AppendMenu(hMenu, MF_STRING, IDM_FILE_OPEN, TEXT("Open"));
	AppendMenu(hMenu, MF_STRING, IDM_FILE_REFRESH, TEXT("Refresh"));
	AppendMenu(hMenu, MF_STRING, IDM_FILE_CUT, TEXT("Cut"));
	AppendMenu(hMenu, MF_STRING, IDM_FILE_COPY, TEXT("Copy"));
	AppendMenu(hMenu, MF_STRING, IDM_FILE_PASTE, TEXT("Paste"));
	AppendMenu(hMenu, MF_STRING, IDM_FILE_DELETE, TEXT("Delete"));
	AppendMenu(hMenu, MF_STRING, IDM_FILE_RENAME, TEXT("Rename"));
	AppendMenu(hMenu, MF_STRING, IDM_FILE_NEW, TEXT("New"));
	AppendMenu(hMenu, MF_STRING, IDM_FILE_PROPERTIES, TEXT("Properties"));
	// hien thi popup menu tai vi tri click chuot
	TrackPopupMenu(hMenu, TPM_RIGHTBUTTON, m_rclick.x, m_rclick.y, 0, hWnd, NULL);
	DestroyMenu(hMenu);
}
