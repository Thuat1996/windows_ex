#include "stdafx.h"
#include "Drives.h"
#include <shellapi.h>

//dùng để sử dụng hàm Strcpy, StrCat
#include <shlwapi.h>
#pragma comment(lib, "shlwapi.lib")

TCHAR* const DriveLetter[] = {
	_T("abc"),
};

DriverSize *Drives::getDriveSize(int i)
{
	__int64 totalSize;
	__int64 freeSpace;
	SHGetDiskFreeSpaceEx(getDriveLetter(i), NULL, (PULARGE_INTEGER)&totalSize, (PULARGE_INTEGER)&freeSpace);
	DriverSize* Size = new DriverSize(totalSize, freeSpace);
return Size;
}
Drives::Drives()
{
}
TCHAR* Drives::getDriveLetter(int i)
{
	return mDirverLetter[i];
}
TCHAR* Drives::getVolumeLabel(int i)
{
	return mVolumeLabel[i];
}
TCHAR* Drives::getDriveType(int i)
{
	return mDriveType[i];
}
LPWSTR Drives::getTotalSpace(int i)
{
	return mDriverSize[i]->getTotalSpaceStr();
}
LPWSTR Drives::getFreeSpace(int i)
{
	return mDriverSize[i]->getFreeSpaceStr();
}

int Drives::getDriverNumber()
{
	return mDrivesNumber;
}

void Drives::getDiversFromSystem()
{
	TCHAR buffer[105];
	TCHAR *tempBuffer = new TCHAR[105];
	mDrivesNumber = 0;
	DWORD bitmask_count = GetLogicalDrives();
	int i = 0;
	while (bitmask_count)
	{
		// sue the bitwise AND,1 - available, 0- unvailable
		if (bitmask_count & 1)
		{
			mDrivesNumber++;
		}
		i++;
		bitmask_count >>= 1;
	}
	//cap phat bo nho
	mDirverLetter = new TCHAR*[mDrivesNumber];
	mVolumeLabel = new TCHAR*[mDrivesNumber];
	mDriveType = new TCHAR*[mDrivesNumber];
	mDirverLetter = new TCHAR*[mDrivesNumber];
	for (int i = 0; i < mDrivesNumber; ++i)
	{
		mDirverLetter[i] = new TCHAR[128];
		mVolumeLabel[i] = new TCHAR[255];
		mDriveType[i] = new TCHAR[255];
	}

	//lay ki tu của ổ
	DWORD bitmask_getletter = GetLogicalDrives();
	i = 0;
	int k = 0;
	while (bitmask_getletter)
	{
		//AND, 1- co, 0- khong
		if (bitmask_getletter & 1)
		{
			mDirverLetter[k] = DriveLetter[i];
			k++;
		}
		i++;
		bitmask_getletter >>= 1;
	}
	int nType;
	for (int i = 0; i < mDrivesNumber; ++i)
	{
		//lay kieu o dia
		nType = GetDriveType(mDirverLetter[i]);

		switch (nType)
		{
		case DRIVE_FIXED:
			StrCpy(mDriveType[i], L"Local Disk");
			break;
		case DRIVE_REMOVABLE:
			StrCpy(mDriveType[i], L"Removable Diver");
			break;
		case DRIVE_CDROM:
			StrCpy(mDriveType[i], L"CD-ROM");
			break;
		default:
			break;
		}

		//lay size cua o dia
		mDriverSize[i] = getDriveSize(i);
		StrCpy(buffer, _T(""));
		if ((nType == DRIVE_FIXED) || (nType == DRIVE_REMOVABLE) || (nType == DRIVE_REMOTE))
		{
			//lay thong tin cua o
			GetVolumeInformation(mDirverLetter[i], buffer, 105, NULL, NULL, NULL, NULL, 0);
			StrCpy(tempBuffer, buffer);
		}
		else 
		{
			if (nType == DRIVE_CDROM)
			{
				GetVolumeInformation(mDirverLetter[i], buffer, 105, NULL, NULL, NULL, NULL,0);
				if (wcslen(buffer) == 0) //khong co lable
				{
					StrCpy(tempBuffer, _T("CD_ROm"));
				}
				else
					StrCpy(tempBuffer, buffer);
			
			}
			else if (((i == 0) || (i == 1)) && (nType == DRIVE_REMOVABLE)) //floppy disk
			{
				StrCpy(tempBuffer, _T("3½ Floppy"));
			}
		}
		if (wcslen(tempBuffer) == 0) //khong co lable
		{
			StrCpy(mVolumeLabel[i], _T("Local Disk"));
		}
		else
		{
			//copy
			StrCpy(mVolumeLabel[i], tempBuffer);
		}

		//them()
		StrCat(mVolumeLabel[i], _T("("));
		StrNCat(mVolumeLabel[i], mDirverLetter[i], 3);
		StrCat(mVolumeLabel[i], _T("("));
	}

}
Drives::~Drives()
{
	for (int i = 0; i < mDrivesNumber; ++i)
	{
		delete[] mDirverLetter[i];
		delete[] mVolumeLabel[i];
		delete[] mDriveType[i];
	}
	delete[] mDirverLetter;
	delete[] mVolumeLabel;
	delete[] mDriveType;
	mDrivesNumber = 0;
}
