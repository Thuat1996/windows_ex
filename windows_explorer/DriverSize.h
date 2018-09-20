#pragma once
class DriverSize
{
private:
	__int64 mTotalSpace;
	__int64 mFreeSpace;
public:
	DriverSize();
	DriverSize(__int64 totalspace, __int64 freespace);
	static LPWSTR convertSizeToString(__int64 size);
	LPWSTR getTotalSpaceStr();
	LPWSTR getFreeSpaceStr();
	~DriverSize();
};

