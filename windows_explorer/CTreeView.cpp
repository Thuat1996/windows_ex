#include "stdafx.h"
#include "CTreeView.h"
//set image
//int imageList[4];

//cac bien duong dan
extern TCHAR Path[MAX_PATH];
extern TCHAR Path1[MAX_PATH];
extern TCHAR Path2[MAX_PATH];
extern TCHAR History[100][MAX_PATH];
extern HINSTANCE hInst;
TV_ITEM tvi;
TV_INSERTSTRUCT tvinsert;
HTREEITEM Selected = NULL;
bool flagSelected = false;
TCHAR szName[260] = _T("");
TCHAR szTmp[260] = _T("");
HWND hwndTV;
CTreeView::CTreeView()
{
}
CTreeView::~CTreeView()
{
}
//HWND CTreeView::CreateTV(HWND hWnd,HINSTANCE g_hInst)
//{
//	hwndTV = CreateWindow(WC_TREEVIEW, L"Tree View", WS_CHILD | WS_VISIBLE | WS_BORDER | TVS_HASLINES | TVS_HASBUTTONS
//		| TVS_SINGLEEXPAND, 0, 85,
//		300, 200, hWnd, (HMENU)IDC_MAIN_TREEVIEW, g_hInst, NULL);
//	return hwndTV;
//}
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
//add this PC
//void CTreeView::LoadPC(HWND hWnd, TCHAR *lpszItem)
//{
//	tvinsert.item.mask = TVIF_TEXT | TVIF_IMAGE | TVIF_SELECTEDIMAGE | TVIF_PARAM;
//	tvinsert.hParent = NULL;
//	tvinsert.hInsertAfter = TVI_ROOT;
//	tvinsert.item.iImage = imageList[IDB_PC];
//	tvinsert.item.iSelectedImage = imageList[IDB_PC];
//	tvinsert.item.pszText = lpszItem;
//	tvinsert.item.lParam = (LPARAM)_T("This PC");
//	HTREEITEM hThisPC = TreeView_InsertItem(hwndTV, &tvinsert);
//}
void CTreeView::AddRoot(HWND hWnd, TCHAR *szS)
{
	tvinsert.hInsertAfter = TVI_LAST;
	tvinsert.hParent = NULL;
	tvinsert.item.mask = TVIF_TEXT | TVIF_IMAGE | TVIF_SELECTEDIMAGE;
	tvinsert.item.pszText = szS;
	tvinsert.item.iImage = 0;
	tvinsert.item.iSelectedImage = 0;
	SendDlgItemMessage(hWnd, IDC_MAIN_TREEVIEW, TVM_INSERTITEM, 0, (LPARAM)&tvinsert);
}
void CTreeView::AddNote(HWND hWnd, TCHAR* szText, HTREEITEM Parent)
{
	tvinsert.item.mask = TVIF_TEXT | TVIF_IMAGE | TVIF_SELECTEDIMAGE;
	tvinsert.item.iImage = 2;
	tvinsert.item.iSelectedImage = 1;
	tvinsert.hParent = Parent;
	tvinsert.hInsertAfter = TVI_LAST;
	tvinsert.item.pszText = szText;
	SendDlgItemMessage(hWnd, IDC_MAIN_TREEVIEW,TVM_INSERTITEM, 0, (LPARAM)&tvinsert);
}
void CTreeView::onSelChange(HWND hWnd)
{
	//setImage(hwndTV);
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
		TCHAR szCpy[MAX_PATH];
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
//set image cho treeview
void CTreeView::setImage(HWND hWnd)
{
	HIMAGELIST hImageList;
	HICON hIcon;
	hImageList = ImageList_Create(16, 16, ILC_COLORDDB | ILC_MASK, 2, 2);
	hIcon = (HICON)LoadImage(GetModuleHandle(0), MAKEINTRESOURCE(IDI_DISK), IMAGE_ICON,
		16, 16, LR_DEFAULTCOLOR);
	ImageList_AddIcon(hImageList, hIcon);   // Macro: Attach the image, to the image list

	hIcon = (HICON)LoadImage(GetModuleHandle(0), MAKEINTRESOURCE(IDI_FOLOPEN), IMAGE_ICON, 
		16, 16, LR_DEFAULTCOLOR);
	ImageList_AddIcon(hImageList, hIcon);

	hIcon = (HICON)LoadImage(GetModuleHandle(0), MAKEINTRESOURCE(IDI_FOLCLOSE), IMAGE_ICON,
		16, 16, LR_DEFAULTCOLOR);
	ImageList_AddIcon(hImageList, hIcon);

	hIcon = (HICON)LoadImage(GetModuleHandle(0), MAKEINTRESOURCE(IDI_FILE), IMAGE_ICON,
		16, 16, LR_DEFAULTCOLOR);
	ImageList_AddIcon(hImageList, hIcon);   // Macro: Attach the image, to the image list
	SendMessage(hWnd, TVM_SETIMAGELIST, (WPARAM)TVSIL_NORMAL, (LPARAM)hImageList);
	
	//TreeView_SetImageList(hwndTV, himl, TVSIL_NORMAL);
}

