#pragma once
#include "DriverSize.h"
#include <Windows.h>



class Drives
{
private:
	TCHAR** mDirverLetter;
	TCHAR** mVolumeLabel;
	TCHAR** mDriveType;
	int mDrivesNumber;
	DriverSize** mDriverSize;

	DriverSize* getDriveSize(int i);
public:
	Drives();
	TCHAR* getDriveLetter(int);
	TCHAR* getVolumeLabel(int);
	TCHAR* getDriveType(int);
	LPWSTR getTotalSpace(int);
	LPWSTR getFreeSpace(int);
	int getDriverNumber();
	void getDiversFromSystem();



	~Drives();
};

