#include "stdafx.h"
#include "Otherfuntions.h"

Otherfuntions::Otherfuntions()
{
}


Otherfuntions::~Otherfuntions()
{
}
int GetType(TCHAR *s)
{
	TCHAR folder[MAX_PATH];
	HANDLE hFind;
	WIN32_FIND_DATAW fd;
	swprintf_s(folder, L"%s/*.*", s);
	hFind = FindFirstFile(folder, &fd);
	if (hFind != INVALID_HANDLE_VALUE)
	{
		return 1;
	}
	else return 0;
}
int DeleteDirectory(LPCTSTR lpszdir, bool noRecycleBin = true)
{
	int wLen = _tcslen(lpszdir);
	TCHAR *pszFrom = new TCHAR[wLen + 2];
	_tcscpy(pszFrom, lpszdir);
	pszFrom[wLen] = 0;
	pszFrom[wLen + 1] = 0;
	SHFILEOPSTRUCT fileop;
	fileop.hwnd = NULL; // nos tatus display
	fileop.wFunc = FO_DELETE; // deldete operation
	fileop.pFrom = pszFrom;
	fileop.pTo = NULL; 
	fileop.fFlags = FOF_NOCONFIRMATION | FOF_SILENT;
	if (!noRecycleBin)
		fileop.fFlags |= FOF_ALLOWUNDO;
	fileop.fAnyOperationsAborted = FALSE;
	fileop.lpszProgressTitle = NULL;
	fileop.hNameMappings = NULL;
	int wRet = SHFileOperation(&fileop);
	delete[] pszFrom;
	return(wRet == 0);
}
int Copy(LPCTSTR lpSource, LPCTSTR lpDestination)
{
	TCHAR szSource[MAX_PATH + 2 * sizeof(TCHAR)] = { 0 };
	TCHAR szDestination[MAX_PATH + 2 * sizeof(TCHAR)] = { 0 };
	wcsncpy_s(szSource, lpSource, MAX_PATH);
	wcsncpy_s(szDestination, lpDestination, MAX_PATH);

	SHFILEOPSTRUCT fs;
	memset(&fs, 0, sizeof(SHFILEOPSTRUCT));

	fs.pFrom = szSource;
	fs.pTo = szDestination;
	fs.wFunc = FO_COPY;
	fs.fFlags = FOF_NOCONFIRMATION | FOF_NOCONFIRMMKDIR;

	return (0 == ::SHFileOperation(&fs));

}
int Cut(LPCTSTR lpSource, LPCTSTR lpDestination)
{
	TCHAR szSource[MAX_PATH + 2 * sizeof(TCHAR)] = { 0 };
	TCHAR szDestination[MAX_PATH + 2 * sizeof(TCHAR)] = { 0 };

	_tcsncpy(szSource, lpSource, MAX_PATH);
	_tcsncpy(szDestination, lpDestination, MAX_PATH);

	SHFILEOPSTRUCT fs;
	memset(&fs, 0, sizeof(SHFILEOPSTRUCT));

	fs.pFrom = szSource;
	fs.pTo = szDestination;
	fs.wFunc = FO_MOVE;
	fs.fFlags = FOF_NOCONFIRMATION | FOF_NOCONFIRMMKDIR;

	return (0 == ::SHFileOperation(&fs));
}

bool FindSubStream(TCHAR * s, TCHAR * t)
{
	int size1 = wcslen(s);						//khai bao bien dem do dai xau	1			
	int size2 = wcslen(t);						//khai bao bien dem do dai xau	2
	bool check = true;
	for (int i = 0; i < size1 - size2 + 1; i++)
	{
		for (int j = 0; j < size2; j++)
		{
			if (s[i + j] != t[j])
			{
				check = false;
				break;
			}
			check = true;
		}
		if (check == true)
			return true;
	}
	return false;
}

void Search(HWND hWnd, int list_id, TCHAR current[1000], TCHAR text[1000])
{
	TCHAR folder[MAX_PATH];					// Bien tam de luu duong dan
	HANDLE hFind;							// bien hFind dang HANDLE
	WIN32_FIND_DATAW fd;					// bien fd luu tru thong tin tim duoc
	TCHAR tmpFileName[1000];					// bien de luu ten file
	swprintf_s(folder, L"%s/*.*", current); // gan ten thu muc vao duong dan
	hFind = FindFirstFile(folder, &fd);		// tim file dau tien

	if (hFind != INVALID_HANDLE_VALUE)		// kiem tra co thanh cong hay khong
	{
		do
		{
			int i = 0;						//khoi tao bien i		
			wcscpy_s(tmpFileName, fd.cFileName);//gan ten file vao bien tmpFileName
			while (tmpFileName[i])			//kiem tra dieu kien
			{
				if (isupper(tmpFileName[i]))//chuan hoa ten file 
				{
					tmpFileName[i] = tolower(tmpFileName[i]);
				}
				i++;
			}
			bool check = FindSubStream(tmpFileName, text);//goi ham check xau con
			if (check == true)
			{
				TCHAR tmpPath[1000];
				swprintf_s(tmpPath, L"%s/%s", current, fd.cFileName);
				LV_ITEM LvItem;
				LvItem.mask = LVIF_TEXT | LVIF_IMAGE;
				LvItem.cchTextMax = 256;
				if (GetType(tmpPath) == 1)
					LvItem.iImage = 0;
				else
					LvItem.iImage = 2;
				LvItem.iSubItem = 0;
				LvItem.iItem = 0;
				LvItem.pszText = fd.cFileName;

				SendDlgItemMessage(hWnd, list_id, LVM_INSERTITEM, 0, (LPARAM)&LvItem);
				

				//SendDlgItemMessage(hWnd, list_id, LVM_SETITEM, 0, (LPARAM)&LvItem);

				LvItem.iSubItem = 3;
				if (GetType(tmpPath) == 1)
					LvItem.pszText = const_cast<TCHAR*>(_T("Folder"));
				else
					LvItem.pszText = const_cast<TCHAR*>(_T("File"));
				SendDlgItemMessage(hWnd, list_id, LVM_SETITEM, 0, (LPARAM)&LvItem);
			}
			if (fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
			{
				if (wcscmp(fd.cFileName, L".") == 0 || wcscmp(fd.cFileName, L"..") == 0)
					continue;
				else
				{
					TCHAR tmpPath[1000];
					swprintf_s(tmpPath, L"%s/%s", current, fd.cFileName);
					Search(hWnd, list_id, tmpPath, text);// de quy hoi lai chinh ham do
				}
			}
		} while (FindNextFileW(hFind, &fd));
		FindClose(hFind);
	}
}
__int64 GetFolderSize(TCHAR path[260])
{

	WIN32_FIND_DATAW data;
	__int64 size = 0;
	TCHAR fname[MAX_PATH];
	swprintf_s(fname, L"%s/*.*", path);
	HANDLE h;
	h = FindFirstFile(fname, &data);
	if (h != INVALID_HANDLE_VALUE)
	{
		do {
			if ((data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
			{
				if (wcscmp(data.cFileName, L".") != 0 && wcscmp(data.cFileName, L"..") != 0)
				{
					swprintf_s(fname, L"%s/%s", path, data.cFileName);
					size += GetFolderSize(fname);
				}
			}
			else
			{
				LARGE_INTEGER sz;
				sz.LowPart = data.nFileSizeLow;
				sz.HighPart = data.nFileSizeHigh;
				size += sz.QuadPart;
			}
		} while (FindNextFile(h, &data) != 0);
		FindClose(h);
	}
	return size;
}
LPCWSTR getPath(HWND m_hListView, int iItem)
{
	if (iItem != -1) {
		LVITEM lv;
		lv.mask = LVIF_PARAM;
		lv.iItem = iItem;
		lv.iSubItem = 0;
		ListView_GetItem(m_hListView, &lv);
		return (LPCWSTR)lv.lParam;
	}
	return NULL;
}
