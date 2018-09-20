#include "stdafx.h"
#include "CTreeView.h"

//cac bien duong dan
extern TCHAR Path[MAX_PATH];
extern TCHAR Path1[MAX_PATH];
extern TCHAR Path2[MAX_PATH];
extern TCHAR History[100][MAX_PATH];
TV_ITEM tvi;
TV_INSERTSTRUCT tvinsert;
HTREEITEM Selected = NULL;
bool flagSelected = false;
TCHAR szName[260] = _T("");
TCHAR szTmp[260] = _T("");
CTreeView::CTreeView()
{
}
CTreeView::~CTreeView()
{
}
HWND CTreeView::CreateTV(HWND hWnd,HINSTANCE g_hInst)
{
	HWND hwndTV = CreateWindow(WC_TREEVIEW, L"Tree View", WS_CHILD | WS_VISIBLE | WS_BORDER | TVS_HASLINES | TVS_HASBUTTONS | TVS_LINESATROOT |
		ES_AUTOHSCROLL | ES_AUTOVSCROLL | WS_HSCROLL | WS_VSCROLL | TVS_SHOWSELALWAYS, 0, 85,
		300, 200, hWnd, (HMENU)IDC_MAIN_TREEVIEW, g_hInst, NULL);
	return hwndTV;
}
void CTreeView::size(HWND hWnd)
{
	RECT rect;
	GetClientRect(hWnd, &rect);
	HWND hTV = GetDlgItem(hWnd, IDC_MAIN_TREEVIEW);
	SetWindowPos(hTV, NULL, 0, rect.top + 90, rect.right - 710, rect.bottom - 110, SWP_NOZORDER);
}

		/*load o dia tu dong*/
void CTreeView::LoadDisk(HWND hWnd)
{
	DWORD uDriveMask = GetLogicalDrives(); // ham load o dia /*ham tra ve 1 bitmask voi o A la 0, b=1....*/
	TCHAR szDriver[] = _T("A");
	while (uDriveMask)
	{
		if (uDriveMask & 1)
		{
			TCHAR szS[MAX_PATH];
			swprintf_s(szS, _T("%s:"), szDriver);
			if (wcscmp(szDriver, _T("A")) != 0) // so sanh 2 chuoi mo rong wchar_t
				AddRoot(hWnd, szS);
		}
		++szDriver[0];
		uDriveMask >>=1;
	}
}
void CTreeView::LoadFolder(HWND hWnd, TCHAR *szS, HTREEITEM Parent)
{
	TCHAR szFolder[MAX_PATH];
	HANDLE hFind;
	WIN32_FIND_DATA fd;

	swprintf_s(szFolder, _T("%s/*.*"),szS);

	hFind = FindFirstFile(szFolder, &fd);
	if (hFind != INVALID_HANDLE_VALUE)
	{
		do 
		{
			if(fd.dwFileAttributes & FILE_ATTRIBUTE_HIDDEN)
				continue;
			if (wcscmp(fd.cFileName, _T(".")) == 0 || wcscmp(fd.cFileName, _T("..")) == 0)
			{
				continue;
			}
			if (fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
			{
				AddNote(hWnd, fd.cFileName, Parent);
			}
		} while (FindNextFileW(hFind, &fd));
		FindClose(hFind);
	}
}
void CTreeView::AddRoot(HWND hWnd, TCHAR *szS)
{
	tvinsert.hInsertAfter = TVI_ROOT;
	tvinsert.hParent = NULL;
	tvinsert.item.mask = TVIF_TEXT | TVIF_IMAGE | TVIF_SELECTEDIMAGE;
	tvinsert.item.pszText = szS;
	tvinsert.item.iImage = 3;
	tvinsert.item.iSelectedImage = 3;
	SendDlgItemMessage(hWnd, IDC_MAIN_TREEVIEW, TVM_INSERTITEM, 0, (LPARAM)&tvinsert);
}
void CTreeView::AddNote(HWND hWnd, TCHAR* szText, HTREEITEM Parent)
{
	tvinsert.item.mask = TVIF_TEXT | TVIF_IMAGE | TVIF_SELECTEDIMAGE;
	tvinsert.item.iImage = 0;
	tvinsert.item.iSelectedImage = 1;
	tvinsert.hParent = Parent;
	tvinsert.hInsertAfter = TVI_LAST;
	tvinsert.item.pszText = szText;
	SendDlgItemMessage(hWnd, IDC_MAIN_TREEVIEW,TVM_INSERTITEM, 0, (LPARAM)&tvinsert);
}
void CTreeView::onSelChange(HWND hWnd)
{
	int wIndex = 0;
	HTREEITEM save;
	bool check = FALSE;
	memset(&tvi, 0, sizeof(tvi));
	//lay handle cua item dang duoc chon
	Selected = (HTREEITEM)SendDlgItemMessage(hWnd, IDC_MAIN_TREEVIEW, TVM_GETNEXTITEM, TVGN_CARET, (LPARAM)Selected);
	save = Selected; // luu lai handle vua lay duoc
	//lay thong tin cua Item dang duoc chon
	tvi.mask = TVIF_TEXT | TVIF_IMAGE | TVIF_SELECTEDIMAGE;
	tvi.pszText = szTmp;
	tvi.cchTextMax = 260;
	tvi.hItem = Selected;
	SendDlgItemMessage(hWnd, IDC_MAIN_TREEVIEW, TVM_GETITEM, TVGN_CARET, (LPARAM)&tvi);
	//update path va path1
	wcscpy_s(Path, tvi.pszText);
	//wcscpy_s(Path1, tvi.pszText);
	wcscpy_s(szName, szTmp);
	Selected = (HTREEITEM)SendDlgItemMessage(hWnd, IDC_MAIN_TREEVIEW, TVM_GETNEXTITEM, TVGN_PARENT, (LPARAM)Selected);

	//lay duong dan
	while (Selected != NULL)
	{
		TCHAR szCpy[1000];
		tvi.hItem = Selected;
		SendDlgItemMessage(hWnd, IDC_MAIN_TREEVIEW, TVM_GETITEM, TVGN_CARET, (LPARAM)&tvi);
		swprintf_s(szCpy, _T("%s/%s"), tvi.pszText, Path);
		wcscpy_s(Path, szCpy);
		/*swprintf_s(szCpy, _T("%s/%s"), tvi.pszText, Path1);
		wcscpy_s(Path1, szCpy);*/
		Selected = (HTREEITEM)SendDlgItemMessage(hWnd, IDC_MAIN_TREEVIEW, TVM_GETNEXTITEM, TVGN_PARENT, (LPARAM)Selected);

	}
	//duyet folder
	LoadFolder(hWnd, Path, save);

}

