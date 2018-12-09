#include "stdafx.h"
#include "CStatus.h"

extern TCHAR chSize[100];
extern TCHAR chTmpPath[MAX_PATH];
CStatus::CStatus()
{
}

CStatus::~CStatus()
{
}
HWND CStatus::CreateStatus(HWND hWnd)
{
	int gMainWindow_Width;
	HWND hStatus = CreateWindowEx(0, STATUSCLASSNAME, NULL, WS_CHILD | WS_VISIBLE| SBARS_SIZEGRIP, 0, 0, 0, 0, hWnd,
		(HMENU)IDC_STATUS, GetModuleHandle(NULL), NULL);
	RECT rect;
	if (GetWindowRect(hWnd, &rect))
	{
		gMainWindow_Width = rect.right - rect.left;
	}
	int size[3] = { gMainWindow_Width*0.1, gMainWindow_Width*0.2, gMainWindow_Width*0.3 };
	SendMessage(hStatus, SB_SETPARTS, 3, (LPARAM)&size);
	return hStatus;
}
void CStatus::count_item(HWND h_List, HWND h_stt)
{
	LVITEM tmp;
	int wIndex = 0; // chi so cua item
	/*wIndex = SendDlgItemMessage(h_List, IDC_MAIN_LISTVIEW, LVM_GETNEXTITEM, -1, LVNI_FOCUSED);
	tmp.mask = TVIF_TEXT;
	tmp.iSubItem = 0;
	tmp.iItem = wIndex;
	tmp.cchTextMax = 260;
	SendDlgItemMessage(h_List, IDC_MAIN_LISTVIEW, LVM_GETITEMTEXT, wIndex, (LPARAM)&tmp);*/
	//ListView_GetItemText(h_List, wIndex, 2, chSize, 256);
	//SendMessage(h_List, LVM_GETITEMTEXT, wIndex, (LPARAM)&tmp);
	LARGE_INTEGER FileSize[1000];
	TCHAR *szFileList[1000]; //  danh sach file
	int count = 0;
	int flag = 0;
	int wFile = 0; // so file

	HANDLE hFind;
	TCHAR szFolder[MAX_PATH];
	WIN32_FIND_DATAW fd;
	TCHAR cCount[260];
	TCHAR chFolder[MAX_PATH];
	count = SendMessage(h_List, LVM_GETITEMCOUNT, 0, count);
	swprintf_s(cCount, _T("%d items"), count);
	SendMessage(h_stt, SB_SETTEXT, 0, (LPARAM)cCount);
	int dem = ListView_GetSelectedCount(h_List);
	swprintf_s(cCount, _T("%d Item selected"), dem);
	//swprintf_s(chSi, _T("%d Item selected"), dem);
	TCHAR size[100] = L"";
	if(dem >= 1) // nhieu hon 1 muc duoc chon
	{
		SendMessage(h_stt, SB_SETTEXT, 1, (LPARAM)cCount);
		SendMessage(h_stt, SB_SETTEXT, 2, (LPARAM)"");
		flag = 1;
	}
	else if (0 == dem)// khong chon muc nao
	{
		flag = 0;
		SendMessage(h_stt, SB_SETTEXT, 1, (LPARAM)"");
		SendMessage(h_stt, SB_SETTEXT, 2, (LPARAM)"");
	}
	else if( 1 == dem)
	{

		SendMessage(h_stt, SB_SETTEXT, 2, (LPARAM)chSize);
		/*hFind = FindFirstFile(chFolder, &fd);
		if (hFind != INVALID_HANDLE_VALUE)
		{
			TCHAR tmpPath[MAX_PATH] = L"";
			__int64 foldersize = 0;
			foldersize = GetFolderSize(chTmpPath);
			float fSize = 0;
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
			wcscpy_s(chSize, size);
			if (1 == dem)
			{
				SendMessage(h_stt, SB_SETTEXT, 2, (LPARAM)chSize);

			}
			*/

		//}
	}
}
	
void CStatus::size(HWND hWnd)
{
	HWND hStatus = GetDlgItem(hWnd, IDC_STATUS);
	SendMessage(hStatus, WM_SIZE, 0, 0);
}
