#include "stdafx.h"
#include "CListview.h"

extern TCHAR Path[MAX_PATH];
extern TCHAR Path1[MAX_PATH];
extern TCHAR Path2[MAX_PATH];
int wSelected = 0; // bien dung de danh dau phan tu duoc chon
TCHAR szTextList[260] = { 0 }; //bien luu ten  cua phan tu duoc chon
LVITEM lvTmp;
bool flag = false;//ktra thu muc
bool flagList = false;//danh dau phan tu duoc chon
CListview::CListview()
{
}

CListview::~CListview()
{
}

HWND CListview::CreatListview(HWND hWnd)
{
	HWND hlistview = CreateWindow(WC_LISTVIEW, NULL, WS_CHILD |LVS_REPORT| WS_VISIBLE |WS_BORDER| LVS_EDITLABELS, 350, 85, 10, 20, hWnd,
		(HMENU)IDC_MAIN_LISTVIEW, GetModuleHandle(NULL), NULL);
	return hlistview;
}
void CListview::size(HWND hWnd)
{
	RECT rect;
	GetClientRect(hWnd, &rect);
	HWND hLV = GetDlgItem(hWnd, IDC_MAIN_LISTVIEW);
	SetWindowPos(hLV, NULL, rect.right - 705, rect.top + 90, rect.right, rect.bottom - 110, SWP_NOZORDER);
}
void CListview::AddColumn(HWND hWnd, TCHAR* szS, int wIndex) // tao cot cho listview
{
	LV_COLUMN LvCol;
	memset(&LvCol, 0, sizeof(LvCol));
	LvCol.mask = LVCF_FMT|LVCF_TEXT | LVCF_WIDTH | LVCF_SUBITEM;
	LvCol.pszText = szS; // TCHAR
	LvCol.cx = 0x100;
	LvCol.fmt = LVCFMT_CENTER;
	LvCol.cchTextMax = MAX_PATH;
	SendDlgItemMessage(hWnd, IDC_MAIN_LISTVIEW, LVM_INSERTCOLUMN, wIndex, (LPARAM)&LvCol);
}
void CListview::CreateList(HWND hWnd) // tao ten cot
{

	AddColumn(hWnd,const_cast<TCHAR*> (_T("Name")), 0);
	AddColumn(hWnd,const_cast<TCHAR*> (_T("Size")), 1);
	AddColumn(hWnd,const_cast<TCHAR*> (_T("Type")), 2);
}
void CListview::LoadFolder(HWND hWnd, TCHAR* szS)
{
	TCHAR szFolder[MAX_PATH];// buffer de luu duong dan
	TCHAR *szFileList[1000]; //  danh sach file
	int wFile = 0; // so file
	int wIndex = 0; // chi so cua item
	HANDLE hFind;
	WIN32_FIND_DATAW fd;
	HTREEITEM Parent;
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
					AddItemFolder(hWnd, wIndex, fd.cFileName, 0, const_cast<TCHAR*> (_T("Folder")));
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
				wcscpy_s(szFileList[wFile],MAX_PATH, fd.cFileName);
				wFile++;
			}
		} while (FindNextFileW(hFind,&fd));
		FindClose(hFind);
		// cho hien thi thong tin file
		for (int i = 0; i < wFile; i++)
		{
			TCHAR szSize[260];
			float fsize = 0;
			//KB
			if (FileSize[i].QuadPart > 1024 && FileSize[i].QuadPart < 1048576)
			{
				fsize = FileSize[i].QuadPart / 1024.;
				swprintf_s(szSize, _T("%0.2f KB"), fsize);
			}
			//MB
			else if (FileSize[i].QuadPart > 1048576 && FileSize[i].QuadPart < 1024 * 1048576)
			{
				fsize = FileSize[i].QuadPart / 1048576.;
				swprintf_s(szSize, _T("%0.2f MB"), fsize);
			}
			//GB
			else if (FileSize[i].QuadPart > 1024 * 1048576)
			{
				fsize = FileSize[i].QuadPart / (float)(1024 * 1048576);
				swprintf_s(szSize, _T("%0.2f GB"), fsize);
			}
			else
				swprintf_s(szSize, _T("1 KB"));
			AddItemFile(hWnd, wIndex + i, szFileList[i], szSize, const_cast<TCHAR*>(_T("File")));
		}

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
void CListview::AddItemFolder(HWND hWnd, int wIndex, TCHAR* szSub1, TCHAR* szSub2, TCHAR* szSub3)
{
	//Them thong tin cua folder theo tung cot
	AddSubItemFolder(hWnd, wIndex, 0, szSub1);
	AddSubItemFolder(hWnd, wIndex, 1, szSub2);
	AddSubItemFolder(hWnd, wIndex, 2, szSub3);
}
void CListview::AddItemFile(HWND hWnd, int wIndex, TCHAR* szSub1, TCHAR* szSub2, TCHAR* szSub3)
{
	AddSubItemFile(hWnd, wIndex, 0, szSub1);
	AddSubItemFile(hWnd, wIndex, 1, szSub2);
	AddSubItemFile(hWnd, wIndex, 2, szSub3);
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
		//hIcon = (HICON)LoadImage(GetModuleHandle(0), MAKEINTRESOURCE(IDI_DISK), IMAGE_ICON,
		//	16, 16, LR_DEFAULTCOLOR);
		//ImageList_AddIcon(hLarge, hIcon);   // Macro: Attach the image, to the image list

		//hIcon = (HICON)LoadImage(GetModuleHandle(0), MAKEINTRESOURCE(IDI_FOLOPEN), IMAGE_ICON,
		//	16, 16, LR_DEFAULTCOLOR);
		//ImageList_AddIcon(hLarge, hIcon);

		//hIcon = (HICON)LoadImage(GetModuleHandle(0), MAKEINTRESOURCE(IDI_FOLCLOSE), IMAGE_ICON,
		//	16, 16, LR_DEFAULTCOLOR);
		//ImageList_AddIcon(hLarge, hIcon);

		//hIcon = (HICON)LoadImage(GetModuleHandle(0), MAKEINTRESOURCE(IDI_FILE), IMAGE_ICON,
		//	16, 16, LR_DEFAULTCOLOR);
		//ImageList_AddIcon(hLarge, hIcon);
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
	swprintf_s(szCpy, _T("%s/%s"), Path, szText);

	if (GetType(szCpy) == 1) // neu thu muc khong rong
	{
		wcscpy_s(Path, szCpy);
		swprintf_s(szCpy, _T("%s/%s"), Path1, szText);
		wcscpy_s(Path1, szCpy);
		flag = true;
		LoadFolder(hWnd, Path);
		cbb->AddText(hWnd, Path);
	}
	else {
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
	TCHAR chCpy[1000];
	int wIndex = 0;
	TCHAR szChText[260]; // luu tru ten phan tu duoc chon
	// lay chi so dong hien tai
	wIndex = SendDlgItemMessage(hWnd, IDC_MAIN_LISTVIEW, LVM_GETNEXTITEM, -1, LVNI_FOCUSED);
	lvTmp.mask = TVIF_TEXT;
	lvTmp.iSubItem = 0;//cot thu 0 cua listview
	lvTmp.pszText = szChText;
	lvTmp.iItem = wIndex;
	lvTmp.cchTextMax = 260;
	flagList = true;
	SendDlgItemMessage(hWnd, IDC_MAIN_LISTVIEW, LVM_GETITEMTEXT, wIndex, (LPARAM)&lvTmp);
	swprintf_s(chCpy, L"%s//%s", Path1, szChText);// lay duoc dan
	wcscpy_s(Path2, chCpy);

}