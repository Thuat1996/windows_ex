#include "stdafx.h"
#include "SetImage.h"


SetImage::SetImage()
{
}

SetImage::~SetImage()
{
}
void SetImage::setimage(HWND hWnd)
{
	HIMAGELIST hImageList;
	HICON hIcon;
	hImageList = ImageList_Create(16, 16, ILC_COLORDDB | ILC_MASK, 2, 2);
	hIcon = (HICON)LoadImage(GetModuleHandle(0), MAKEINTRESOURCE(IDI_DISK), IMAGE_ICON,
		16, 16, LR_DEFAULTCOLOR);
	ImageList_AddIcon(hImageList, hIcon);   // Macro: Attach the image, to the image list

	hIcon = (HICON)LoadImage(GetModuleHandle(0), MAKEINTRESOURCE(IDI_FOLOPEN), IMAGE_ICON,
		16, 16, LR_DEFAULTCOLOR);
	ImageList_AddIcon(hImageList, hIcon);

	hIcon = (HICON)LoadImage(GetModuleHandle(0), MAKEINTRESOURCE(IDI_FOLCLOSE), IMAGE_ICON,
		16, 16, LR_DEFAULTCOLOR);
	ImageList_AddIcon(hImageList, hIcon);

	hIcon = (HICON)LoadImage(GetModuleHandle(0), MAKEINTRESOURCE(IDI_FILE), IMAGE_ICON,
		16, 16, LR_DEFAULTCOLOR);
	ImageList_AddIcon(hImageList, hIcon);   // Macro: Attach the image, to the image list
	SendMessage(hWnd, TVM_SETIMAGELIST, (WPARAM)TVSIL_NORMAL, (LPARAM)hImageList);
}
