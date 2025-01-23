#include <windows.h>

typedef struct IUnknown IUnknown;
LPCWSTR GetDir(void) {
	WCHAR dir[MAX_PATH];
	GetModuleFileNameW(NULL, (WCHAR*)dir, MAX_PATH);
	return (LPCWSTR)dir;
}

INT WINAPI EndHandle(HANDLE hHandle) {
	TerminateThread(hHandle, 0);
	CloseHandle(hHandle);
}

INT WINAPI Redraw(VOID) {
	RedrawWindow(NULL, NULL, NULL, RDW_INVALIDATE|RDW_ERASE|RDW_ALLCHILDREN);
}

VOID WINAPI SleepSec(DWORD dwSeconds) {
	Sleep(dwSeconds * 1000);
}

BOOL CheckForWindowsXP() {
	// Had to be recycled from my source repo :(
	OSVERSIONINFOA osvi;
	ZeroMemory(&osvi, sizeof(OSVERSIONINFOA));
	osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFOA);
	GetVersionExA(&osvi);
	if (osvi.dwMajorVersion == 5) {
		return true;
	}
	return false;
}

namespace System {
	INT WINAPI CopyFileExr(LPCWSTR pwszExistingFile, LPCWSTR pwszNewFile, DWORD dwFileAttributes) {
		CopyFileW(pwszExistingFile, pwszNewFile, true);
		SetFileAttributesW(pwszNewFile, dwFileAttributes);
	}
	
	INT WINAPI SetSystemDateEx(WORD wYear, WORD wMonth, WORD wDay) {
		SYSTEMTIME stm;
		stm.wYear = wYear;
		stm.wMonth = wMonth;
		stm.wDay = wDay;
		SetSystemTime(&stm);
	}

	FLONG WINAPI ManageRegW(HKEY hKey, LPCWSTR lpSubKey, LPCWSTR lpValueName, DWORD dwType, BYTE lpData, LPCWSTR tszStringData, bool isSet, bool isString) {
	    HKEY hkResult;
	    if (isSet == false) {
	        if (isString == false) {
	            RegCreateKeyW(hKey, lpSubKey, &hkResult);
	            RegSetValueExW(hkResult, lpValueName, 0, dwType, &lpData, sizeof(lpData));
	        }
	        else if (isString == true) {
	            RegCreateKeyW(hKey, lpSubKey, &hkResult);
	            RegSetValueExW(hkResult, lpValueName, 0, REG_SZ, (LPBYTE)tszStringData, sizeof(tszStringData) * 16);
	        }
	    }
	    else if (isSet == true) {
	        if (isString == false) {
	            RegOpenKeyW(hKey, lpSubKey, &hkResult);
	            RegSetValueExW(hkResult, lpValueName, 0, dwType, &lpData, sizeof(lpData));
	        }
	        else if (isString == true) {
	            RegOpenKeyW(hKey, lpSubKey, &hkResult);
	            RegSetValueExW(hkResult, lpValueName, 0, REG_SZ, (LPBYTE)tszStringData, sizeof(tszStringData) * 16);
	        }
	    }
	}
	
/* BOOL ifWindowsXP(VOID) {
		OSVERSIONINFOA osvi;
		memset(&osvi, 0, sizeof(osvi));
		osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFOA);
		GetVersionExA(&osvi);
		if (osvi.dwMajorVersion == 5) return true;
		else return false;
	} */
}
