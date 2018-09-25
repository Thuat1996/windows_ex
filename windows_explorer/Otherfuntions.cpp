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