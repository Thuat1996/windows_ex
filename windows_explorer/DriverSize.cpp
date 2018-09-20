#include "stdafx.h"
#include "DriverSize.h"


//dùng để sử dụng hàm Strcpy, StrCat
#include <shlwapi.h>
#pragma comment(lib, "shlwapi.lib")
#define KB 1
#define MB 2
#define GB 3
#define TB 4
#define RADIX 10
DriverSize::DriverSize()
{
}

DriverSize::~DriverSize()
{
}
DriverSize::DriverSize(__int64 totalspace, __int64 freespace)
{
	mTotalSpace = totalspace;
	mFreeSpace = freespace;
}
LPWSTR DriverSize::convertSizeToString(__int64 size)
{
	int ntype = 0; // bytes
	while (size >= 1048576) // 1MB
	{
		size /= 1024;
		++ntype;
	}
	__int64 nRight;
	if (size >= 1024)
	{
		//lay 1 chu so thap phan cua nSize chua trong nRight
		nRight = size % 1024;
		while (nRight > 99) nRight /= 10;

			size /= 1024;
			++ntype;
	}
	else nRight = 0;

	TCHAR *buffer = new TCHAR[11];
	_itow_s(size, buffer, 11, RADIX);
	if (nRight != 0 && ntype > KB)
	{
		StrCat(buffer, _T("."));
		TCHAR *right = new TCHAR[3];
		_itow_s(nRight, right, 3, RADIX);
		StrCat(buffer, right);
	}
	switch (ntype)
	{
	case 0: //Byte
		StrCat(buffer, _T("bytes"));
		break;
	case 1:
		StrCat(buffer, _T("KB"));
		break;
	case 2:
		StrCat(buffer, _T("MB"));
		break;
	case 3:
		StrCat(buffer, _T("GB"));
		break;
	case 4:
		StrCat(buffer, _T("TB"));
		break;
	}
	return buffer;
}
LPWSTR DriverSize::getTotalSpaceStr()
{
	return convertSizeToString(mTotalSpace);
}
LPWSTR DriverSize::getFreeSpaceStr()
{
	return convertSizeToString(mFreeSpace);
}