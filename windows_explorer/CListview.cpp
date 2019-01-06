#include "stdafx.h"
#include "CListview.h"
extern TCHAR Path[MAX_PATH];
extern TCHAR Path1[MAX_PATH];
extern TCHAR Path2[MAX_PATH];
TCHAR Path4[MAX_PATH];
TCHAR cTmpPath[MAX_PATH]; // bien luu dia chi cua file/folder truoc khi duoc doi ten
int wSelected = 0; // bien dung de danh dau phan tu duoc chon
TCHAR szTextList[260] = { 0 }; //bien luu ten  cua phan tu duoc chon
LVITEM lvTmp;
bool flag = false;//ktra thu muc
bool flagList = false;//danh dau phan tu duoc chon
TCHAR* create;
CListview::CListview()
{
}

CListview::~CListview()
{
}

HWND CListview::CreatListview(HWND hWnd)
{

	HWND hlistview = CreateWindow(WC_LISTVIEW, L"List View", WS_CHILD | LVS_REPORT | WS_VISIBLE |WS_BORDER| LVS_EDITLABELS, 350, 85, 10, 20, hWnd,
		(HMENU)IDC_MAIN_LISTVIEW, GetModuleHandle(NULL), NULL);
	ListView_SetExtendedListViewStyle(hlistview,
		LVS_EX_FULLROWSELECT | LVS_EX_HEADERDRAGDROP);
	return hlistview;
}
void CListview::size(HWND hWnd, HWND hLV)
{
	RECT rect;
	GetClientRect(hWnd, &rect);
	hLV = GetDlgItem(hWnd, IDC_MAIN_LISTVIEW);
	SetWindowPos(hLV, NULL, rect.right - 705, rect.top + 90, 705, rect.bottom - 110, SWP_NOZORDER);
}
void CListview::AddColumn(HWND hWnd, TCHAR* szS, int wIndex) // tao cot cho listview
{
	LV_COLUMN LvCol;
	memset(&LvCol, 0, sizeof(LvCol));
	LvCol.mask = LVCF_FMT|LVCF_TEXT | LVCF_WIDTH | LVCF_SUBITEM;
	LvCol.pszText = szS; // TCHAR
	LvCol.cx = 180; // chinhd o rong cua column
	LvCol.fmt = LVCFMT_CENTER;
	LvCol.cchTextMax = MAX_PATH;
	SendDlgItemMessage(hWnd, IDC_MAIN_LISTVIEW, LVM_INSERTCOLUMN, wIndex, (LPARAM)&LvCol);
}
void CListview::CreateList(HWND hWnd) // tao ten cot
{

	AddColumn(hWnd,const_cast<TCHAR*> (_T("Name")), 0);
	AddColumn(hWnd,const_cast<TCHAR*> (_T("Date modified")), 1);
	AddColumn(hWnd,const_cast<TCHAR*> (_T("Size")), 2);
	AddColumn(hWnd,const_cast<TCHAR*> (_T("Type")), 3);
}
void CListview::LoadFolder(HWND hWnd, TCHAR* szS)
{
	TCHAR szFolder[MAX_PATH];// buffer de luu duong dan
	TCHAR *szFileList[1000]; //  danh sach file
	int wFile = 0; // so file
	int wIndex = 0; // chi so cua item
	HANDLE hFind;
	WIN32_FIND_DATAW fd;
	LARGE_INTEGER FileSize[1000];
	Clear(hWnd); // moi lan load lai forder la xoa tat ca cac phan tu truoc do
	swprintf_s(szFolder, _T("%s/*.*"), szS); // tao bien folder chua ten duong dan
	hFind = FindFirstFile(szFolder, &fd); // tim kien file dau tien trong duong dan
	// kiem tra xem viec tim kiem co thanh cong khoong
	if (hFind != INVALID_HANDLE_VALUE)
	{
		do {
			//loai bo 2 ki tu "." va ".."
			if (fd.dwFileAttributes & FILE_ATTRIBUTE_HIDDEN)
				continue;
			/*kiem ta xem co phai la folder hay khong*/
			if (fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
			{
				if (wcscmp(fd.cFileName, _T(".")) == 0 || wcscmp(fd.cFileName, _T("..")) == 0)
					continue;
				else
				{
					AddItemFolder(hWnd, wIndex, fd.cFileName, getDateModified(fd.ftLastWriteTime), 0, const_cast<TCHAR*> (_T("Folder")));
					wIndex++;
				}	
			}
			else // la File
			{
				//nhan thong tin File roi cho vao 1 mang
				FileSize[wFile].LowPart = fd.nFileSizeLow;
				FileSize[wFile].HighPart = fd.nFileSizeHigh;
				szFileList[wFile] = new TCHAR[260];
				// copy ten file vao mang filelist
				//wcscpy(szFileList[wFile], fd.cFileName);
				//wcscpy_s(szFileList[wFile],MAX_PATH, fd.cFileName);
				TCHAR szSize[260];
				TCHAR filex[204];
				float fsize = 0;
				fsize = FileSize[wFile].QuadPart / 1024.;
				swprintf_s(szSize, _T("%.f KB"), fsize);
				AddItemFile(hWnd, wFile, fd.cFileName , getDateModified(fd.ftLastWriteTime), szSize, const_cast<TCHAR*>(_T("File")));
				wFile++;
			}
		} while (FindNextFileW(hFind,&fd));
		FindClose(hFind);
		// cho hien thi thong tin file
		//for (int i = 0; i < wFile; i++)
		//{
		//	create = getDateModified(fd.ftCreationTime);
		//	/*TCHAR szSize[260];
		//	float fsize = 0;
		//	fsize = FileSize[i].QuadPart / 1024.;
		//	swprintf_s(szSize, _T("%.f KB"), fsize);
		//	AddItemFile(hWnd, wIndex + i, szFileList[i], NULL, szSize, const_cast<TCHAR*>(_T("File")));*/
		//}
	}
}
void CListview::AddSubItemFolder(HWND hWnd, int wItem, int wSubitem, TCHAR* szName)
{
	LV_ITEM LvItem;
	LvItem.mask = LVFIF_TEXT | LVIF_IMAGE;
	LvItem.cchTextMax = 256;
	LvItem.iImage = 1;
	LvItem.iSubItem = wSubitem;
	LvItem.iItem = wItem;
	LvItem.pszText = szName;
	if (wSubitem == 0) // neu la cot thu 1 trong listView;
		//them phan tu o cot dau tien thuoc dang folder
		SendDlgItemMessage(hWnd, IDC_MAIN_LISTVIEW, LVM_INSERTITEM, 0, (LPARAM)&LvItem);
	else
		//them phan tu o cac cot tiep theo la folder
		SendDlgItemMessage(hWnd, IDC_MAIN_LISTVIEW, LVM_SETITEM, 0, (LPARAM)&LvItem);
}
void CListview::AddSubItemFile(HWND hWnd, int wItem, int wSubitem, TCHAR* szName)
{
	LV_ITEM LvItem;
	LvItem.mask = LVIF_TEXT | LVIF_IMAGE;
	LvItem.cchTextMax = 256;
	LvItem.iImage = 2;
	LvItem.iSubItem = wSubitem;
	LvItem.iItem = wItem;
	LvItem.pszText = szName;
	if (wSubitem == 0) // neu la cot thu 1 trong listView;
		//them phan tu o cot dau tien thuoc dang File
		SendDlgItemMessage(hWnd, IDC_MAIN_LISTVIEW, LVM_INSERTITEM, 0, (LPARAM)&LvItem);
	else
		//them phan tu o cac cot tiep theo la File
		SendDlgItemMessage(hWnd, IDC_MAIN_LISTVIEW, LVM_SETITEM, 0, (LPARAM)&LvItem);
}
void CListview::AddItemFolder(HWND hWnd, int wIndex, TCHAR* szSub1, TCHAR* szSub2, TCHAR* szSub3,TCHAR* szSub4)
{
	//Them thong tin cua folder theo tung cot
	AddSubItemFolder(hWnd, wIndex, 0, szSub1);
	AddSubItemFolder(hWnd, wIndex, 1, szSub2);
	AddSubItemFolder(hWnd, wIndex, 2, szSub3);
	AddSubItemFolder(hWnd, wIndex, 3, szSub4);
}
void CListview::AddItemFile(HWND hWnd, int wIndex, TCHAR* szSub1, TCHAR* szSub2, TCHAR* szSub3,TCHAR* szSub4)
{
	AddSubItemFile(hWnd, wIndex, 0, szSub1);
	AddSubItemFile(hWnd, wIndex, 1, szSub2);
	AddSubItemFile(hWnd, wIndex, 2, szSub3);
	AddSubItemFile(hWnd, wIndex, 3, szSub4);
}
void CListview::DeleteList(HWND hWnd)
{
	SendDlgItemMessage(hWnd, IDC_MAIN_LISTVIEW,LVM_DELETEITEM, wSelected, 0);
}
void CListview::Clear(HWND hWnd)
{
	SendDlgItemMessage(hWnd, IDC_MAIN_LISTVIEW, LVM_DELETEALLITEMS, 0, 0);
}
void CListview::SetImageList(HWND hWnd)
{
		//HIMAGELIST hLarge;// image list for icon view
		HIMAGELIST hSmall; // image lilst for other views
		//HICON hIcon;
		HICON hI;
		//hLarge = ImageList_Create(32, 32, ILC_COLORDDB | ILC_MASK, 2, 2);
		hSmall = ImageList_Create(20, 20, ILC_COLORDDB | ILC_MASK, 2, 2);
		/****HIcon*****/
		/************HI**************/
		hI = (HICON)LoadImage(GetModuleHandle(0), MAKEINTRESOURCE(IDI_FOLOPEN), IMAGE_ICON,
			16, 16, LR_DEFAULTCOLOR);
		ImageList_AddIcon(hSmall, hI);

		hI = (HICON)LoadImage(GetModuleHandle(0), MAKEINTRESOURCE(IDI_FOLCLOSE), IMAGE_ICON,
			16, 16, LR_DEFAULTCOLOR);
		ImageList_AddIcon(hSmall, hI);

		hI = (HICON)LoadImage(GetModuleHandle(0), MAKEINTRESOURCE(IDI_FILE), IMAGE_ICON,
			16, 16, LR_DEFAULTCOLOR);
		ImageList_AddIcon(hSmall, hI); 
		// Macro: Attach the image, to the image list
		//SendMessage(hWnd, LVM_SETIMAGELIST, (WPARAM)LVSIL_NORMAL, (LPARAM)hLarge);
		SendMessage(hWnd, LVM_SETIMAGELIST, (WPARAM)LVSIL_SMALL, (LPARAM)hSmall);
}
void CListview::onDBClick(HWND hWnd,CCombobox *cbb)
{
	TCHAR szCpy[1000];
	int wIndex;
	TCHAR szText[260];
	wIndex = SendDlgItemMessage(hWnd, IDC_MAIN_LISTVIEW, LVM_GETNEXTITEM, -1, LVNI_FOCUSED);
	lvTmp.mask = TVIF_TEXT;
	lvTmp.iSubItem = 0;// cot thu 0 cua listview
	lvTmp.pszText = szText; // ten cua phan tu duoc chon
	lvTmp.iItem = wIndex; //chi so dong cua phan tu duoc chon
	lvTmp.cchTextMax = 260; // gioi han do dai cua text
	// lay text cua phan tu duoc chon
	SendDlgItemMessage(hWnd, IDC_MAIN_LISTVIEW, LVM_GETITEMTEXT, wIndex, (LPARAM)&lvTmp);
	/*them dau "/" vao duong dan sau do gan vao bien szcopy*/
	swprintf_s(szCpy, _T("%s\\%s"), Path, szText);

	if (GetType(szCpy) == 1) // neu thu muc khong rong
	{
		wcscpy_s(Path, szCpy);
		swprintf_s(szCpy, _T("%s/%s"), Path1, szText);
		wcscpy_s(Path1, szCpy);
		flag = true;
		LoadFolder(hWnd, Path);
		cbb->AddText(hWnd, Path);
		 // Insert number of item
	}
	else { // open file
		int i = 0;
		i = (int)ShellExecute(NULL, _T("Open"), szCpy, NULL, NULL, SW_NORMAL);
		if (i < 32)
		{
			MessageBox(hWnd, _T("ERROR: can not open selected file \n This File have no default execute program"), NULL, NULL);
		}
	}
}
void CListview::onClick(HWND hWnd, CCombobox *cbb)
{
	TCHAR chCpy[MAX_PATH];
	int wIndex;
	TCHAR szChText[260] = {0}; // luu tru ten phan tu duoc chon
	// lay chi so dong hien tai
	wIndex = SendDlgItemMessage(hWnd, IDC_MAIN_LISTVIEW, LVM_GETNEXTITEM, -1, LVNI_FOCUSED);
	lvTmp.mask = TVIF_TEXT;
	lvTmp.iSubItem = 0;//cot thu 0 cua listview
	lvTmp.pszText = szChText;
	lvTmp.iItem = wIndex;
	lvTmp.cchTextMax = 260;
	flagList = true;
	SendDlgItemMessage(hWnd, IDC_MAIN_LISTVIEW, LVM_GETITEMTEXT, wIndex, (LPARAM)&lvTmp);
	//swprintf_s(chCpy, _T("%s\\%s"), Path, szChText);// lay duoc dan
	//wcscpy_s(Path4, chCpy);
	////Rename file/folder
	//MoveFile(cTmpPath, chCpy);

}

void CListview::SortList(HWND hList, HWND hSortBy)
{
	int wIndex = 0;
	TCHAR szTmp[260];
	wIndex = SendMessage(hSortBy, CB_GETCURSEL, 0, 0);
	SendMessage(hSortBy, CB_GETLBTEXT, wIndex, (LPARAM)szTmp); // lay date ben combobox
	// bat su kien vao combobox
}

int CALLBACK ListView_CompareName(LPARAM index1, LPARAM index2, LPARAM lParam)
{
	HWND hListView = (HWND)lParam;
	TCHAR szItemText[MAX_PATH] = _T(""), szITemText1[MAX_PATH] = _T("");
	ListView_GetItemText(hListView, index1, 0, szItemText, MAX_PATH); // ham lay text cua list
	ListView_GetItemText(hListView, index2, 0, szITemText1, MAX_PATH); // ham lay text cua list
	return _tcscmp(_tcslwr(szItemText),_tcslwr(szITemText1)); // tra ve sau khi so ssanh
}

int CALLBACK ListView_CompareSize(LPARAM index1, LPARAM index2, LPARAM lParam)
{
	HWND hListView = (HWND)lParam;
	TCHAR cItemText1[MAX_PATH] = _T(""), cItemText2[MAX_PATH] = _T("");
	ListView_GetItemText(hListView, index1, 2, cItemText1, MAX_PATH);
	ListView_GetItemText(hListView, index2, 2, cItemText2, MAX_PATH);
	double n1 = _wtoi(cItemText1); //Change data type from wchar to integer
	double n2 = _wtoi(cItemText2);

	if (n1 - n2 > 0) return 1;
	else if (n1 - n2 == 0) return 0;
	else return -1;
}
int CALLBACK ListView_CompareType(LPARAM index1, LPARAM index2, LPARAM lParam)
{
	HWND hListView = (HWND)lParam;
	TCHAR szItemText[MAX_PATH] = _T("");
	TCHAR szITemText1[MAX_PATH] = _T("");
	ListView_GetItemText(hListView, index1, 3, szITemText1, MAX_PATH); // ham lay text cua list
	ListView_GetItemText(hListView, index2, 3, szItemText, MAX_PATH);
	return _tcscmp(_tcslwr(szItemText), _tcslwr(szITemText1));
}

LPWSTR getDateModified(FILETIME ftLastWrite)
{
	SYSTEMTIME stUTC, stLocal;
	char szLocalDate[255], szLocalTime[255];
	FileTimeToSystemTime(&ftLastWrite, &stUTC);
	SystemTimeToTzSpecificLocalTime(NULL, &stUTC, &stLocal);
	GetDateFormat(LOCALE_USER_DEFAULT, DATE_AUTOLAYOUT, &stLocal, NULL,
		(LPWSTR)szLocalDate, 255);
	TCHAR *buffer = new TCHAR[50];
	wsprintf(buffer,_T("%s %02d:%02d %s"),szLocalDate, (stLocal.wHour > 12) ? 
		(stLocal.wHour % 12) : (stLocal.wHour),
		stLocal.wMinute,
		(stLocal.wHour > 12) ? (_T("PM")) : (_T("AM")));
	return buffer;
}

