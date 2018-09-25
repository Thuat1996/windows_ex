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
TCHAR Path1[MAX_PATH];
TCHAR Path2[MAX_PATH];
TCHAR History[100][MAX_PATH];
int g_wLinkNumber;
int g_wLinkPos;

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
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WINDOWSEXPLORER));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_MENU +1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_WINDOWSEXPLORER);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_WINDOWSEXPLORER));
	
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
	static POINTS m_click;
	static CMenu *Cmenu;
	static CListview *CLV;
	static CToolbar *CTool;
	static CCombobox *cbb;
	static CStatus *CStt;
	static CTabView *Ctab;
	static CTreeView *CTV;
	static HWND h_Tree;
	static HWND h_List;
	static HTREEITEM Selected;

    switch (message)
    {
	case WM_CREATE:
	{
		
		// khoi tao doi tuong cua class
		CTool->CreatToolbar(hWnd);
		//khoi tao doi tuong cua class status
		CStt->CreateStatus(hWnd);
		//khoi tao doi tuong cua class cbb
		cbb->CreateCombobox(hWnd);
		HWND hstatic_add = CreateWindowEx(0, _T("Static"), _T("Address"), WS_CHILD | WS_VISIBLE, 0, 30, 60, 23, hWnd,
			(HMENU)IDC_MAIN_STATIC_ADD, GetModuleHandle(NULL), NULL);

		HWND hBtnGo = CreateWindowEx(0, _T("Button"), _T("GO"), WS_CHILD | WS_VISIBLE, 900, 27, 100, 20, hWnd,
			(HMENU)IDC_MAIN_BUTTON_GO, GetModuleHandle(NULL), NULL);

		/**********creat edit**********/
		HWND hEdit = CreateWindowEx(0, _T("EDIT"), _T(""), WS_CHILD | WS_VISIBLE,
			0, 53, 300, 20, hWnd, (HMENU)IDC_MAIN_EDIT, GetModuleHandle(NULL), NULL);
		HWND hBtnSearch = CreateWindowEx(0, _T("Button"), _T("Search"), WS_CHILD | WS_VISIBLE, 320, 53, 70, 20, hWnd,
			(HMENU)IDC_MAIN_BUTTON_SEARCH, GetModuleHandle(NULL), NULL);
		// create tab control
		Ctab->InitTab(hWnd,hInst);
		// create static "sort by"
		HWND hStatic_sort = CreateWindowEx(0, _T("Static"), _T("Sort by :"), WS_CHILD | WS_VISIBLE, 800, 60, 60, 23, hWnd,
			(HMENU)IDC_MAIN_STATIC_SORT, GetModuleHandle(NULL), NULL);
		// create combobox sort
		HWND hCbb1 = CreateWindowEx(0, _T("ComboBox"), _T(""), WS_CHILD | WS_VISIBLE | CBS_DROPDOWN, 870, 60, 100, 23, hWnd,
			(HMENU)IDC_MAIN_COMBOBOX_SORT, GetModuleHandle(NULL), NULL);
		//create treeview
		InitCommonControls();
		//CTV.CreateTV(hWnd, hInst);
		h_Tree = CTV->CreateTV(hWnd,hInst);
		CTV->LoadDisk(hWnd);
		CTV->setImage(h_Tree);
		// create ListView
		
		h_List = CLV->CreatListview(hWnd);
		CLV->CreateList(hWnd);
		wcscpy_s(Path, _T("C:"));
		wcscpy_s(Path1, _T("C:"));
		CLV->SetImageList(h_List);
		CLV->LoadFolder(hWnd, Path);
		
		
	}
	break;
	case WM_NOTIFY:
	{
		
		if (LOWORD(wParam) == IDC_MAIN_TREEVIEW && ((LPNMHDR)lParam)->code == TVN_SELCHANGED)
		{
			CTV->onSelChange(hWnd,CLV,cbb);
		}
		if (LOWORD(wParam) == IDC_MAIN_LISTVIEW && ((LPNMHDR)lParam)->code == NM_DBLCLK)
		{
			CLV->onDBClick(hWnd,cbb);
		}
	}
	break;
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Parse the menu selections:
            switch (wmId)
            {
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
	case WM_RBUTTONDOWN:
	{
		////MessageBox(NULL, L"abc", L"adfads", MB_ICONERROR | MB_OK);
		//m_click = MAKEPOINTS(lParam);
		//bool flag;
		//flag = CTV.toadoclick(hWnd, m_click,lParam);
		//if (flag == true)
		//{
		//	MessageBox(NULL, L"abc", L"adfads", MB_ICONERROR | MB_OK);
		//}
		//else MessageBox(NULL, L"deo vao", L"adfads", MB_ICONERROR | MB_OK);
		////Cmenu.CreateMenuTree(hWnd, lParam);
		//break;
		Cmenu->CreateMenuList(hWnd, lParam);
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
		SetWindowPos(hbtnGo, NULL, rect.right - 120, rect.top + 27, 100, 23,SWP_NOSIZE);

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
		SetWindowPos(hEdit, NULL, 0 ,rect.top + 60, rect.right - 710, 23, SWP_NOZORDER); 

		// chinh size treeview
		CTV->size(hWnd);
		// chinh size listview
		CLV->size(hWnd);
		

	}
	break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: Add any drawing code that uses hdc here...
            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
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
        return (INT_PTR)TRUE;

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

