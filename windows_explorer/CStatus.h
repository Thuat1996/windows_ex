#pragma once
#include "stdafx.h"
#define  IDC_STATUS 1000
class CStatus
{
public:
	CStatus();
	~CStatus();
	HWND CreateStatus(HWND);
	void size(HWND);
};

