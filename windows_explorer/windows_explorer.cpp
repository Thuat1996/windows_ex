// windows_explorer.cpp : Defines the entry point for the application.
//
#include "stdafx.h"
#include "windows_explorer.h"
/************************DEFINE***************/
#define MAX_LOADSTRING 100
#define IDC_MAIN_EDIT 102
#define IDC_MAIN_STATIC_ADD 1001
#define IDC_MAIN_STATIC_SORT 2
#define IDC_MAIN_COMBOBOX_SORT 3


#define IDS_TIP_BACK 10001
#define IDS_TIP_FORWARD 10002
#define  IDC_MAIN_COMBOBOX_ADD 1002
#define IDC_MAIN_BUTTON_GO 1003
#define IDC_MAIN_TABCTRL 1
#define IDC_MAIN_BUTTON_SEARCH 1004

//Global variable declartion
TCHAR Path[MAX_PATH];
TCHAR CPath[MAX_PATH];
TCHAR Path1[MAX_PATH];
TCHAR Path2[MAX_PATH];
TCHAR Path3[MAX_PATH];
extern TCHAR Path4[MAX_PATH];
TCHAR Cpaste[MAX_PATH];
TCHAR History[100][MAX_PATH];
TCHAR szTextFile[260];
TCHAR cCut[260];
TCHAR cCopy[260];
int hTreeView_Width;
int gMainWindow_Width;
int gNewTreeViewWidth;
int gMainWindow_Height;
TCHAR g_ListHistory[200][260];
TCHAR chSize[100] = _T("");
TCHAR chTmpPath[MAX_PATH];
TCHAR chNameTmp[256];
TCHAR chNameType[MAX_PATH] = L"Folder";
TCHAR chTmpName[MAX_PATH];
TCHAR chCreate[MAX_PATH];
 TCHAR chInfo[MAX_PATH];
 TCHAR chdateMoti[MAX_PATH];
static TCHAR szChText[260];
extern TCHAR cTmpPath[MAX_PATH];// Bien luu dia chi File/Folder truoc khi doi ten
int g_wLinkNumber;
int g_wLinkPos;
int nHistory;
extern TV_INSERTSTRUCT tvinsert;
HTREEITEM Parent;
extern bool flagList; // bien dung de danh dau phan tu duoc chon
extern bool flag ;
extern bool flagSelected;
extern TCHAR szTextList[260];
bool cut = false;

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name
// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

/****************************************************/
int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Place code here.
    // Initialize global strings
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_WINDOWSEXPLORER, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WINDOWSEXPLORER));

    MSG msg;

    // Main message loop:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_EXPLORER));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_MENU +1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_WINDOWSEXPLORER);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_EXPLORER));
	
    return RegisterClassExW(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Store instance handle in our global variable

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE: Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	static POINTS m_ptBegin, m_ptEnd;
	//static POINTS click[2];
	static CMenu *Cmenu;
	static CListview *CLV;
	static CToolbar *CTool;
	static CCombobox *cbb;
	static CStatus *CStt;
	static CTabView *Ctab;
	static CTreeView *CTV;
	static cbbsort *cbb_sort;
	static HWND h_Tree;
	static HWND h_List;
	static HWND h_stt;
	static HWND h_tab;
	static HWND h_cbb;
	static HWND h_cbbsort;
	static HWND h_toolbar;
	static HWND h_serachedit;
	static HTREEITEM Selected;
	static int nCopy = 1;
	switch (message)
	{
	case WM_CREATE:
	{
		g_wLinkNumber = 0;
		g_wLinkPos = 0;
		nHistory = 0;
		// khoi tao doi tuong cua class
		h_toolbar = CTool->CreatToolbar(hWnd);
		//khoi tao doi tuong cua class status
		h_stt = CStt->CreateStatus(hWnd);
		//khoi tao doi tuong cua class cbb
		h_cbb = cbb->CreateCombobox(hWnd);
		HWND hstatic_add = CreateWindowEx(0, _T("Static"), _T("Address"), WS_CHILD | WS_VISIBLE, 0, 30, 60, 23, hWnd,
			(HMENU)IDC_MAIN_STATIC_ADD, GetModuleHandle(NULL), NULL);

		HWND hBtnGo = CreateWindowEx(0, _T("Button"), _T("GO"), WS_CHILD | WS_VISIBLE, 900, 27, 100, 20, hWnd,
			(HMENU)IDC_MAIN_BUTTON_GO, GetModuleHandle(NULL), NULL);

		/**********creat edit**********/
		h_serachedit = CreateWindowEx(0, _T("EDIT"), _T(""), WS_CHILD | WS_VISIBLE,
			0, 53, 300, 20, hWnd, (HMENU)IDC_MAIN_EDIT, GetModuleHandle(NULL), NULL);
		HWND hBtnSearch = CreateWindowEx(0, _T("Button"), _T("Search"), WS_CHILD | WS_VISIBLE, 320, 53, 70, 20, hWnd,
			(HMENU)IDC_MAIN_BUTTON_SEARCH, GetModuleHandle(NULL), NULL);
		// create tab control
		h_tab = Ctab->InitTab(hWnd, hInst);
		SendMessage(h_tab, TCM_SETCURSEL, 0, 0);

		// create static "sort by"
		HWND hStatic_sort = CreateWindowEx(0, _T("Static"), _T("Sort by :"), WS_CHILD | WS_VISIBLE, 800, 60, 60, 23, hWnd,
			(HMENU)IDC_MAIN_STATIC_SORT, GetModuleHandle(NULL), NULL);
		// create combobox sort
		h_cbbsort = cbb_sort->createcbbsort(hWnd);
		//create treeview
		InitCommonControls();
		//CTV.CreateTV(hWnd, hInst);
		h_Tree = CTV->CreateTV(hWnd, hInst);
		SetFocus(h_Tree);;
		CTV->LoadDisk(hWnd);
		CTV->setImage(h_Tree);
		// create ListView
		h_List = CLV->CreatListview(hWnd);
		CLV->CreateList(hWnd);
		wcscpy_s(Path, _T("C:"));
		CLV->SetImageList(h_List);
		CLV->LoadFolder(hWnd, Path);
		cbb->AddText(hWnd, Path);
		/*********HOTKEY*********/
		RegisterHotKey(hWnd, IDM_FILE_COPY1, MOD_CONTROL, 0x43); // ctrl C, mod_control : nt ctrl duoc giu
		RegisterHotKey(hWnd, IDM_FILE_PASTE1, MOD_CONTROL, 0x56); // ctrl V
		RegisterHotKey(hWnd, IDM_FILE_CUT1, MOD_CONTROL, 0x58); // ctrl X
		RegisterHotKey(hWnd, IDM_FILE_DELETE,NULL, 0x2E); // Delete
		RegisterHotKey(hWnd, IDM_FILE_RENAME,NULL, 0x71); // F2
		RegisterHotKey(hWnd, IDM_FILE_BACK, NULL, 0x08); // back space
		RegisterHotKey(hWnd, IDM_FILE_REFRESH, NULL, 0x74); // refresh

	}
	break;
	case WM_LBUTTONDOWN:
	{
		int xPos;
		int yPos;
		//	m_ptBegin = MAKEPOINTS(lParam);
			//m_ptEnd = MAKEPOINTS(lParam);
		HCURSOR hcSizeEW;

		hcSizeEW = LoadCursor(NULL, IDC_SIZEWE);
		// Get the x and y co-ordinates of the mouse
		xPos = (int)LOWORD(lParam);
		yPos = (int)HIWORD(lParam);

		if (xPos > (hTreeView_Width) && xPos < (hTreeView_Width + 5))
		{
			SetCapture(hWnd);
			if (xPos > (hTreeView_Width) && xPos < (hTreeView_Width + 5)) {
				SetCursor(hcSizeEW);
			}
		}
		break;
	}
	case WM_MOUSEMOVE:
	{
		int xPos;
		int yPos;
		//	m_ptBegin = MAKEPOINTS(lParam);
		//	m_ptEnd = MAKEPOINTS(lParam);
		HCURSOR hcSizeEW;
		RECT rect;
		GetWindowRect(hWnd, &rect);
		gMainWindow_Width = rect.right - rect.left;
		hcSizeEW = LoadCursor(NULL, IDC_SIZEWE);
		// Get the x and y co-ordinates of the mouse
		xPos = (int)LOWORD(lParam);
		yPos = (int)HIWORD(lParam);
		if (wParam == MK_LBUTTON) {
			//if (xPos > gMainWindow_Width*0.080 && xPos < gMainWindow_Width*0.90) {
				//gNewTreeViewWidth = xPos - (gMainWindow_Width*0.3);
			SendMessage(hWnd, WM_SIZE, 0, 0);
			UpdateWindow(h_Tree);// update TreeView window
			UpdateWindow(h_List);// update ListView window

		//}
		}
		if (xPos > (rect.right - 710 - 40) && xPos < (rect.right - 705 - 40))
		{
			SetCursor(hcSizeEW);
		}
		break;
	}
	case WM_LBUTTONUP:
	{
		ReleaseCapture();
		break;
	}
	case WM_NOTIFY:
	{

		if (LOWORD(wParam) == IDC_MAIN_TREEVIEW && ((LPNMHDR)lParam)->code == TVN_SELCHANGED)
		{
			g_wLinkNumber = g_wLinkPos; // loai bo history trong khoang [LinkNumber; LinkPos];
			CTV->onSelChange(hWnd, CLV, cbb);
			CTV->OnClick(hWnd, CLV, cbb);
			//Insert number of item into status bar
			CStt->count_item(h_List, h_stt);
			SendMessage(h_cbbsort, CB_SETCURSEL, -1, 0);
		}
		if (LOWORD(wParam) == IDC_MAIN_LISTVIEW && ((LPNMHDR)lParam)->code == NM_DBLCLK)
		{
			g_wLinkNumber = g_wLinkPos;// loai bo history trong khoang []
			CLV->onDBClick(hWnd, cbb);
			CStt->count_item(h_List, h_stt);
			//CStt->SetFileInfoToStatusBar(h_List, h_stt);
			SendMessage(h_cbbsort, CB_SETCURSEL, -1, 0);
		}
		if (LOWORD(wParam) == IDC_MAIN_LISTVIEW && ((LPNMHDR)lParam)->code == NM_CLICK || NM_RCLICK)
		{
			CLV->onClick(hWnd, cbb);
			CStt->count_item(h_List, h_stt);
		}
		if (LOWORD(wParam) == IDC_MAIN_TREEVIEW && ((LPNMHDR)lParam)->code == NM_RCLICK)
		{
			Cmenu->CreateMenuTree(hWnd);
		}
		if (LOWORD(wParam) == IDC_MAIN_LISTVIEW && ((LPNMHDR)lParam)->code == NM_RCLICK)
		{
			Cmenu->CreateMenuList(hWnd);
			/*HMENU hMenu = CreatePopupMenu();
			GetCursorPos(&m_clkmouse);
			AppendMenu(hMenu, MF_STRING, IDM_FILE_Document, TEXT("Docment"));
			TrackPopupMenu(hMenu, TPM_RIGHTBUTTON, m_clkmouse.x - 160, m_clkmouse.y, 0, hWnd, NULL);
			if (LOWORD(wParam) == IDM_FILE_VIEW && ((LPNMHDR)lParam)->code == NM_CLICK)
			{
				MessageBox(NULL, L"abc", L"asdfads", MB_ICONERROR);
			}

			DestroyMenu(hMenu);*/
		}
		if ((LOWORD(wParam) == IDC_MAIN_TABCTRL) && (((LPNMHDR)lParam)->code == TCN_SELCHANGE))
		{
			OnSelchangeTabCtrlMode(h_List, h_tab);
		}
		break;
		
	}

	case WM_COMMAND:
	{
		int wmId = LOWORD(wParam);
		// Parse the menu selections:
		switch (wmId)
		{
		case IDM_FILE_NEW:
		{
			//if (flagList == true && flag == false)
			//{
			//	wcscat_s(Path2, 260, L"\\New Folder");
			//	CreateDirectory(Path2, NULL);
			//	if (flagSelected == true && flag == false)
			//	{
			//		tvinsert.hParent = Selected;
			//		tvinsert.hInsertAfter = TVI_LAST; //work as root level
			//		tvinsert.item.pszText = const_cast<TCHAR*> (_T("New Folder"));
			//		Parent = (HTREEITEM)SendDlgItemMessage(hWnd, IDC_MAIN_TREEVIEW, TVM_INSERTITEM, 0, (LPARAM)&tvinsert);
			//		flagSelected = true;
			//	}
			//	CLV->LoadFolder(hWnd, Path1);
			//	flagList = false;
			//}
			//else if (flag == true)
			//{
			//	wcscpy_s(Path3, Path1);
			//	wcscat_s(Path3, 260, L"\\New Folder");
			//	CreateDirectory(Path3, NULL);
			//	if (flagSelected == true && flag == false)
			//	{
			//		tvinsert.hParent = Selected;
			//		tvinsert.hInsertAfter = TVI_LAST; //work as root level
			//		tvinsert.item.pszText = const_cast<TCHAR*> (_T("New Folder"));
			//		Parent = (HTREEITEM)SendDlgItemMessage(hWnd, IDC_MAIN_TREEVIEW, TVM_INSERTITEM, 0, (LPARAM)&tvinsert);
			//		flagSelected = false;
			//	}
			//	CLV->LoadFolder(hWnd, Path);
			//flag = false;
			//}
			LVITEM tmp1;
			int index1;
			TCHAR text1[MAX_PATH] = { 0 };
			index1 = SendMessage(h_List, LVM_GETNEXTITEM, -1, LVNI_FOCUSED);

			tmp1.mask = TVIF_TEXT;
			tmp1.iSubItem = 0;
			tmp1.pszText = text1;
			tmp1.iItem = index1;
			tmp1.cchTextMax = MAX_PATH;

			TCHAR itemText1[MAX_PATH] = _T("");
			ListView_GetItemText(h_List, index1, 1, itemText1, MAX_PATH);

			SendMessage(h_List, LVM_GETITEMTEXT, index1, (LPARAM)&tmp1);
			swprintf_s(Path3, _T("%s\\%s"), Path, text1);

			CreateDirectory(wcscat(Path3,_T("\\New folder")), NULL);
			CLV->LoadFolder(hWnd, Path);
			break;
		}
		case IDM_FILE_DELETE1:
		{
			//if (MessageBox(hWnd, _T("Are you sure you want to remove all its content to Recycle Bin?"), _T("Delete Folder"), MB_YESNO | MB_ICONWARNING) == IDYES)
			//{
				//if (flagList == true)
			//	{
			//		if (DeleteDirectory(Path, false) == true) // khi chon vao thu muc nao do
			//		{
			//			CLV->DeleteList(hWnd);
			//			CLV->LoadFolder(hWnd, Path);
			//			flagList = false;
			//		}
			//		else MessageBox(hWnd, _T("Cannot delete: Access is denied.\n Make sure the disk is not full or write-protected\n and that the file is not currently is use."), _T("Error Deleting File or Folder"), 0);
			//	}
			//	else MessageBox(hWnd, _T("Click on Item to Delete"), _T("ERROR"), NULL);
			//}
			TCHAR cpy1[MAX_PATH];
			LVITEM tmp1;
			int index1;
			TCHAR text1[MAX_PATH] = { 0 };
			index1 = SendMessage(h_List, LVM_GETNEXTITEM, -1, LVNI_FOCUSED);

			tmp1.mask = TVIF_TEXT;
			tmp1.iSubItem = 0;
			tmp1.pszText = text1;
			tmp1.iItem = index1;
			tmp1.cchTextMax = MAX_PATH;

			TCHAR itemText1[256] = _T("");
			ListView_GetItemText(h_List, index1, 1, itemText1, MAX_PATH);

			SendMessage(h_List, LVM_GETITEMTEXT, index1, (LPARAM)&tmp1);
			swprintf_s(cpy1, _T("%s\\%s"), Path, text1);

			if (GetFileAttributes(cpy1) &FILE_ATTRIBUTE_DIRECTORY)
			{
				if (MessageBox(hWnd, _T("Ban co muon xoa thu muc khong?"), _T("Confirm Folder Delete"), MB_YESNO | MB_ICONWARNING) == IDYES)
				{
					if (DeleteDirectory(cpy1, false))
					{
						//	CLV->DeleteList(hWnd);
						CLV->LoadFolder(hWnd, Path);
						MessageBox(hWnd, _T("Thu muc da bi xoa vao thung rac!"), _T("Thong bao"), MB_ICONINFORMATION);
					}
					else
					{
						MessageBox(hWnd, _T("Khong xoa duoc thu muc, hay kiem tra lai!"), _T("Error Deleting Folder!"),
							ERROR | MB_ICONERROR);
					}
				}
				else
					return 0;
			}
			break;
		}
		case IDM_FILE_RENAME1:
		{
			LVITEM tmp;
			int wIndex = 0;
			wcscpy_s(cTmpPath, Path4);
			wIndex = SendDlgItemMessage(hWnd, IDC_MAIN_LISTVIEW, LVM_GETNEXTITEM, -1, LVNI_FOCUSED);
			SendMessage(h_List, LVM_EDITLABEL, (WPARAM)wIndex, (LPARAM)0);
			//tmp.iItem = wIndex;
			break;
		}
		case IDM_FILE_COPY1:
		{
			nCopy = 1;
			LVITEM tmp1;
			int index1;
			TCHAR text1[MAX_PATH] = { 0 };
			index1 = SendMessage(h_List, LVM_GETNEXTITEM, -1, LVNI_FOCUSED);

			tmp1.mask = TVIF_TEXT;
			tmp1.iSubItem = 0;
			tmp1.pszText = text1;
			tmp1.iItem = index1;
			tmp1.cchTextMax = MAX_PATH;

			TCHAR itemText1[MAX_PATH] = _T("");
			ListView_GetItemText(h_List, index1, 1, itemText1, MAX_PATH);

			SendMessage(h_List, LVM_GETITEMTEXT, index1, (LPARAM)&tmp1);
			swprintf_s(cCopy, _T("%s\\%s"), Path, text1);
			break;
		}
		case IDM_FILE_CUT1:
		{
			nCopy = 0;
			LVITEM tmp1;
			int index1;
			TCHAR text1[MAX_PATH] = { 0 };
			index1 = SendMessage(h_List, LVM_GETNEXTITEM, -1, LVNI_FOCUSED);
			tmp1.mask = TVIF_TEXT;
			tmp1.iSubItem = 0;
			tmp1.pszText = text1;
			tmp1.iItem = index1;
			tmp1.cchTextMax = MAX_PATH;
			TCHAR itemText1[256] = _T("");
			ListView_GetItemText(h_List, index1, 1, itemText1, MAX_PATH);
			SendMessage(h_List, LVM_GETITEMTEXT, index1, (LPARAM)&tmp1);
			swprintf_s(cCut, _T("%s\\%s"), Path, text1);
			break;
		}
		case IDM_FILE_PASTE1:
		{
			if (nCopy == 0)
			{
				LVITEM tmp1;
				int index1;
				TCHAR text1[MAX_PATH] = { 0 };
				index1 = SendMessage(h_List, LVM_GETNEXTITEM, -1, LVNI_FOCUSED);

				tmp1.mask = TVIF_TEXT;
				tmp1.iSubItem = 0;
				tmp1.pszText = text1;
				tmp1.iItem = index1;
				tmp1.cchTextMax = MAX_PATH;

				TCHAR itemText1[MAX_PATH] = _T("");
				ListView_GetItemText(h_List, index1, 1, itemText1, MAX_PATH);

				SendMessage(h_List, LVM_GETITEMTEXT, index1, (LPARAM)&tmp1);
				swprintf_s(Cpaste, _T("%s\\%s"), Path, text1);

				Cut(cCut, Cpaste);
				CLV->LoadFolder(hWnd, Cpaste);
			}
			else if (nCopy == 1)
			{
				LVITEM tmp1;
				int index1;
				TCHAR text1[MAX_PATH] = { 0 };
				index1 = SendMessage(h_List, LVM_GETNEXTITEM, -1, LVNI_FOCUSED);

				tmp1.mask = TVIF_TEXT;
				tmp1.iSubItem = 0;
				tmp1.pszText = text1;
				tmp1.iItem = index1;
				tmp1.cchTextMax = MAX_PATH;

				TCHAR itemText1[MAX_PATH] = _T("");
				ListView_GetItemText(h_List, index1, 1, itemText1, MAX_PATH);

				SendMessage(h_List, LVM_GETITEMTEXT, index1, (LPARAM)&tmp1);
				swprintf_s(Cpaste, _T("%s\\%s"), Path, text1);
				Copy(cCopy, Cpaste);
				CLV->LoadFolder(hWnd, Cpaste);
			}
			else return 0;
			break;
		}
		case ID_BACK:
		{
			int wTmp = g_wLinkPos - 1; // bien tam de luu lai vi tri duong dan
			if (wTmp < 0) break;
			wcscpy_s(Path, g_ListHistory[wTmp]);
			CLV->LoadFolder(hWnd, g_ListHistory[wTmp]);
			cbb->AddText(hWnd, g_ListHistory[wTmp]); // g_wLinkNumer se thay doi
			g_wLinkNumber--; // so duong dan da duoc luu
			g_wLinkPos = wTmp; // vi tri duong dan hien tai
			break;
		}
		case ID_FORWARD:
		{
			int wTmp = g_wLinkPos + 1; // bien tam de luu lai vi tri duong dan
			if (wTmp > g_wLinkNumber) break;
			wcscpy_s(Path, g_ListHistory[wTmp]);
			CLV->LoadFolder(hWnd, g_ListHistory[wTmp]);
			cbb->AddText(hWnd, g_ListHistory[wTmp]); // g_wLinkNumer se thay doi
			g_wLinkNumber--; // so duong dan da duoc luu
			g_wLinkPos = wTmp; // vi tri duong dan hien tai
			break;
		}
		case IDM_FILE_OPEN1:
		{
			CLV->onDBClick(hWnd, cbb);
			break;
		}
		case IDM_FILE_PROPERTIES1:
		{
			HANDLE hFind;
			WIN32_FIND_DATAW fd;
			TCHAR *create = new TCHAR[260];
			LVITEM tmp;
			int wIndex;
			TCHAR chFolder[MAX_PATH];
			// Bien cho kich thuoc
			TCHAR chName[256];
			wIndex = SendDlgItemMessage(hWnd, IDC_MAIN_LISTVIEW, LVM_GETNEXTITEM, -1, LVNI_FOCUSED);

			tmp.mask = TVIF_TEXT;
			tmp.iSubItem = 0;
			tmp.pszText = szChText;
			tmp.iItem = wIndex;
			tmp.cchTextMax = 260;
			SendDlgItemMessage(hWnd, IDC_MAIN_LISTVIEW, LVM_GETITEMTEXT, wIndex, (LPARAM)&tmp);
			swprintf_s(chTmpPath, _T("%s/%s"), Path, szChText);// Da lay duoc duong dan

			ListView_GetItemText(h_List, wIndex, 2, chSize, 256);
			ListView_GetItemText(h_List, wIndex, 1, chdateMoti, 256);


			SendMessage(h_List, LVM_GETITEMTEXT, wIndex, (LPARAM)&tmp);
			// Kiem tra xem duong dan hay folder
			swprintf_s(chFolder, _T("%s/*.*"), chTmpPath);//tao bien folder chua ten duong dan
			hFind = FindFirstFile(chFolder, &fd);
			TCHAR size[100] = L"";
			if (hFind != INVALID_HANDLE_VALUE)
			{
				create = getDateModified(fd.ftCreationTime);
				TCHAR tmpPath[MAX_PATH] = L"";
				//TCHAR size[100] = L"";
				__int64 foldersize = 0;
				foldersize = GetFolderSize(chTmpPath);
				double fSize = 0;
				if (foldersize > 1024 && foldersize < 1048576)
				{
					fSize = foldersize / 1024.;
					swprintf_s(size, _T("%0.2f KB"), fSize);
				}
				else if (foldersize > 1048576 && foldersize < 1024 * 1048576)
				{
					fSize = foldersize / 1048576.;
					swprintf_s(size, _T("%0.2f MB"), fSize);
				}
				else if (foldersize > 1024 * 1048576)
				{
					fSize = foldersize / (float)(1024 * 1048576);
					swprintf_s(size, _T("%0.2f GB"), fSize);
				}
				else
				{
					swprintf_s(size, _T("0 KB"));
				}
				wcscpy_s(chNameTmp, tmp.pszText);
				wcscpy_s(chNameType, _T("Folder"));
				wcscpy_s(chSize, size);
				wcscpy_s(chCreate, create);
			}
			else
			{
				swprintf_s(chName, _T("%s Properties"), tmp.pszText);
				wcscpy_s(chNameType, _T("File"));
				wcscpy_s(chNameTmp, tmp.pszText);
				//wcscpy_s(chCreate, create);
			}
			swprintf_s(chTmpName, _T("%s Properties"), tmp.pszText);
			DialogBox(NULL, MAKEINTRESOURCE(IDD_DIALOG_PRO), hWnd, About);
			break;
		}
		case IDM_FILE_REFRESH:
		{
			int nIndex;
			TCHAR cTmp[MAX_PATH];
			nIndex = SendMessage(h_cbb, CB_GETCURSEL, 0, 0);
			if (nIndex < 0)
			{
				break;
			}
			else
			{
				SendMessageW(h_cbb, CB_GETLBTEXT, nIndex, (LPARAM)cTmp);
				CLV->LoadFolder(h_List, Path);
			}
			break;
		}
		case IDC_MAIN_COMBOBOX_SORT:
		{
			if (HIWORD(wParam) == CBN_SELCHANGE) // lua chon option trong combobox
			{
				int nIndex;
				TCHAR cTmp[MAX_PATH];
				nIndex = SendMessageW(h_cbbsort, CB_GETCURSEL, 0, 0); //Get index of the chosen line in Combobox
				SendMessageW(h_cbbsort, CB_GETLBTEXT, nIndex, (LPARAM)cTmp); //Get text in the chosen line
				if (wcscmp(cTmp, _T("Name")) == 0) //Compare user's option with column header text for sorting 
				{
					ListView_SortItemsEx(h_List, ListView_CompareName, (LPARAM)h_List);
				}
				if (wcscmp(cTmp, _T("Size")) == 0)
				{
					ListView_SortItemsEx(h_List, ListView_CompareSize, (LPARAM)h_List);
					ListView_SortItemsEx(h_List, ListView_CompareType, (LPARAM)h_List);
				}
				if (wcscmp(cTmp, _T("Type")) == 0)
				{
					ListView_SortItemsEx(h_List, ListView_CompareType, (LPARAM)h_List);
				}
			}
			break;
		}
		case IDC_MAIN_BUTTON_GO:
		{
			TCHAR szTmp[300];
			SendDlgItemMessage(hWnd, IDC_MAIN_COMBOBOX_ADD, WM_GETTEXT, 300, (LPARAM)szTmp);
			wcscpy_s(Path, szTmp);
			CLV->LoadFolder(hWnd, Path);
			break;
		}
		case IDC_MAIN_BUTTON_SEARCH:
		{
			int i = 0;
			TCHAR current[1000];
			TCHAR text[1000];
			wcscpy_s(current, Path);
			SendMessage(h_serachedit, WM_GETTEXT, 260, (LPARAM)text);
			while (text[i])
			{
				if (isupper(text[i]))
				{
					text[i] = tolower(text[i]);
				}
				i++;
			}
			CLV->Clear(hWnd);
			SendDlgItemMessage(hWnd, IDC_STATUS, WM_SETTEXT, 0, (LPARAM)_T("Searching"));
			Search(hWnd, IDC_MAIN_LISTVIEW, current, text);
			break;
		}
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
	}
	break;
	case WM_HOTKEY:
	{
		switch (wParam)
		{
		case IDM_FILE_COPY:
		{
			nCopy = 1;
			LVITEM tmp1;
			int index1;
			TCHAR text1[MAX_PATH] = { 0 };
			index1 = SendMessage(h_List, LVM_GETNEXTITEM, -1, LVNI_FOCUSED);
			tmp1.mask = TVIF_TEXT;
			tmp1.iSubItem = 0;
			tmp1.pszText = text1;
			tmp1.iItem = index1;
			tmp1.cchTextMax = MAX_PATH;
			TCHAR itemText1[MAX_PATH] = _T("");
			ListView_GetItemText(h_List, index1, 1, itemText1, MAX_PATH);
			SendMessage(h_List, LVM_GETITEMTEXT, index1, (LPARAM)&tmp1);
			swprintf_s(cCopy, _T("%s\\%s"), Path, text1);
			break;
		}
		case IDM_FILE_BACK:
		{
			int wTmp = g_wLinkPos - 1; // bien tam de luu lai vi tri duong dan
			if (wTmp < 0) break;
			wcscpy_s(Path, g_ListHistory[wTmp]);
			CLV->LoadFolder(hWnd, g_ListHistory[wTmp]);
			cbb->AddText(hWnd, g_ListHistory[wTmp]); // g_wLinkNumer se thay doi
			g_wLinkNumber--; // so duong dan da duoc luu
			g_wLinkPos = wTmp; // vi tri duong dan hien tai
			break;
		}
		case IDM_FILE_DELETE:
		{
			TCHAR cpy1[MAX_PATH];
			LVITEM tmp1;
			int index1;
			TCHAR text1[MAX_PATH] = { 0 };
			index1 = SendMessage(h_List, LVM_GETNEXTITEM, -1, LVNI_FOCUSED);

			tmp1.mask = TVIF_TEXT;
			tmp1.iSubItem = 0;
			tmp1.pszText = text1;
			tmp1.iItem = index1;
			tmp1.cchTextMax = MAX_PATH;

			TCHAR itemText1[256] = _T("");
			ListView_GetItemText(h_List, index1, 1, itemText1, MAX_PATH);

			SendMessage(h_List, LVM_GETITEMTEXT, index1, (LPARAM)&tmp1);
			swprintf_s(cpy1, _T("%s\\%s"), Path, text1);

			if (GetFileAttributes(cpy1) &FILE_ATTRIBUTE_DIRECTORY)
			{
				if (MessageBox(hWnd, _T("Ban co muon xoa thu muc khong?"), _T("Confirm Folder Delete"), MB_YESNO | MB_ICONWARNING) == IDYES)
				{
					if (DeleteDirectory(cpy1, false))
					{
						//	CLV->DeleteList(hWnd);
						CLV->LoadFolder(hWnd, Path);
						MessageBox(hWnd, _T("Thu muc da bi xoa vao thung rac!"), _T("Thong bao"), MB_ICONINFORMATION);
					}
					else
					{
						MessageBox(hWnd, _T("Khong xoa duoc thu muc, hay kiem tra lai!"), _T("Error Deleting Folder!"),
							ERROR | MB_ICONERROR);
					}
				}
				else
					return 0;
			}
			break;
		}
		case IDM_FILE_PASTE1:
		{
			if (nCopy == 0)
			{
				LVITEM tmp1;
				int index1;
				TCHAR text1[MAX_PATH] = { 0 };
				index1 = SendMessage(h_List, LVM_GETNEXTITEM, -1, LVNI_FOCUSED);

				tmp1.mask = TVIF_TEXT;
				tmp1.iSubItem = 0;
				tmp1.pszText = text1;
				tmp1.iItem = index1;
				tmp1.cchTextMax = MAX_PATH;

				TCHAR itemText1[MAX_PATH] = _T("");
				ListView_GetItemText(h_List, index1, 1, itemText1, MAX_PATH);

				SendMessage(h_List, LVM_GETITEMTEXT, index1, (LPARAM)&tmp1);
				swprintf_s(Cpaste, _T("%s\\%s"), Path, text1);

				Cut(cCut, Cpaste);
				CLV->LoadFolder(hWnd, Cpaste);
			}
			else if (nCopy == 1)
			{
				LVITEM tmp1;
				int index1;
				TCHAR text1[MAX_PATH] = { 0 };
				index1 = SendMessage(h_List, LVM_GETNEXTITEM, -1, LVNI_FOCUSED);

				tmp1.mask = TVIF_TEXT;
				tmp1.iSubItem = 0;
				tmp1.pszText = text1;
				tmp1.iItem = index1;
				tmp1.cchTextMax = MAX_PATH;

				TCHAR itemText1[MAX_PATH] = _T("");
				ListView_GetItemText(h_List, index1, 1, itemText1, MAX_PATH);

				SendMessage(h_List, LVM_GETITEMTEXT, index1, (LPARAM)&tmp1);
				swprintf_s(Cpaste, _T("%s\\%s"), Path, text1);
				Copy(cCopy, Cpaste);
				CLV->LoadFolder(hWnd, Cpaste);
			}
			else return 0;
			break;
		}
		case IDM_FILE_CUT:
		{
			nCopy = 0;
			LVITEM tmp1;
			int index1;
			TCHAR text1[MAX_PATH] = { 0 };
			index1 = SendMessage(h_List, LVM_GETNEXTITEM, -1, LVNI_FOCUSED);
			tmp1.mask = TVIF_TEXT;
			tmp1.iSubItem = 0;
			tmp1.pszText = text1;
			tmp1.iItem = index1;
			tmp1.cchTextMax = MAX_PATH;
			TCHAR itemText1[256] = _T("");
			ListView_GetItemText(h_List, index1, 1, itemText1, MAX_PATH);
			SendMessage(h_List, LVM_GETITEMTEXT, index1, (LPARAM)&tmp1);
			swprintf_s(cCut, _T("%s\\%s"), Path, text1);
			break;
		}
		default:
			break;
		}
		break;
	}
	case WM_SIZE:
	{
		RECT rect;
		GetClientRect(hWnd, &rect);
		// chinh size tool
		CTool->size(hWnd);
		// chinh status
		CStt->size(hWnd);
		// chinh size button
		HWND hbtnGo = GetDlgItem(hWnd, IDC_MAIN_BUTTON_GO);
		SetWindowPos(hbtnGo, NULL, rect.right - 120, rect.top + 27, 100, 23, SWP_NOSIZE);

		//chinh size combobox add
		cbb->size(hWnd);

		//chinh size comboboxsort
		HWND hcbo_sort = GetDlgItem(hWnd, IDC_MAIN_COMBOBOX_SORT);
		SetWindowPos(hcbo_sort, NULL, rect.right - 120, rect.top + 60, 100, 23, SWP_NOZORDER);

		// chinh size static sortby
		HWND hstatic_sort = GetDlgItem(hWnd, IDC_MAIN_STATIC_SORT);
		SetWindowPos(hstatic_sort, NULL, rect.right - 200, rect.top + 60, 60, 23, SWP_NOZORDER);

		// chinh size tab
		Ctab->size(hWnd);

		//chinh size static search
		HWND hbtn_search = GetDlgItem(hWnd, IDC_MAIN_BUTTON_SEARCH);
		SetWindowPos(hbtn_search, NULL, rect.right - 700, rect.top + 60, 60, 23, SWP_NOZORDER);

		// chinh size editbox
		HWND hEdit = GetDlgItem(hWnd, IDC_MAIN_EDIT);
		SetWindowPos(hEdit, NULL, 0, rect.top + 60, rect.right - 710, 23, SWP_NOZORDER);
		/*if (GetWindowRect(hWnd, &rect))
		{
			gMainWindow_Width = rect.right - rect.left;
			gMainWindow_Height = rect.bottom - rect.top;
		}*/
		//hLV = GetDlgItem(hWnd, IDC_MAIN_LISTVIEW);
	//	SetWindowPos(h_List, NULL, gMainWindow_Width*0.3, gMainWindow_Height + 90, gMainWindow_Width*0.7,rect.bottom - 110, SWP_NOZORDER);
		// chinh size treeview
		CTV->size(hWnd);
		// chinh size listview
		CLV->size(hWnd, h_List);
		if (GetWindowRect(hWnd, &rect)) {
			gMainWindow_Width = rect.right - rect.left;
			gMainWindow_Height = rect.bottom - rect.top;
			hTreeView_Width = rect.right - 710 + 30;
			//SetWindowPos(h_Tree, 0,
			//	0, 0,						//pos sau 
			//	rect.top + 90, hTreeView_Width, rect.bottom - 110); //size sau khi resize
			//SetWindowPos(h_Tree, NULL, rect.right - 705 - hTreeView_Width, rect.top + 90, 705 - hTreeView_Width, rect.bottom - 110, SWP_NOZORDER);
		}
		break;
	}
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);
		// TODO: Add any drawing code that uses hdc here...
		EndPaint(hWnd, &ps);
	}
	break;
	case WM_DESTROY:
		delete cbb,CLV,CTV;
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
	}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
	{
		SendDlgItemMessage(hDlg, IDC_STT_Name, WM_SETTEXT, 0, (LPARAM)chNameTmp);
		SendDlgItemMessage(hDlg, IDC_STT_Type, WM_SETTEXT, 0, (LPARAM)chNameType);
		SendDlgItemMessage(hDlg, IDC_STT_Size, WM_SETTEXT, 0, (LPARAM)chSize);
		SendDlgItemMessage(hDlg, IDC_STT_Path, WM_SETTEXT, 0, (LPARAM)chTmpPath);
		SendDlgItemMessage(hDlg, IDC_STT_Create, WM_SETTEXT, 0, (LPARAM)chCreate);
		SendDlgItemMessage(hDlg, IDC_STT_datemoti, WM_SETTEXT, 0, (LPARAM)chdateMoti);
		SetWindowText(hDlg, chTmpName);
	}	
    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}

