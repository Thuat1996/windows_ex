#pragma once
class Otherfuntions
{
public:

	Otherfuntions();
	~Otherfuntions();
	
};
int GetType(TCHAR*);
int DeleteDirectory(LPCTSTR, bool);
int Copy(LPCTSTR, LPCTSTR);
int Cut(LPCTSTR, LPCTSTR);
bool FindSubStream(TCHAR *s, TCHAR *t);
void Search(HWND hWnd, int list_id, TCHAR current[1000], TCHAR text[1000]);
__int64 GetFolderSize(TCHAR path[260]);
LPCWSTR getPath(HWND m_hListView, int iItem);