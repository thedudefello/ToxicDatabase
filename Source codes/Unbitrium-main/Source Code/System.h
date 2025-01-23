#include <windows.h>
typedef HANDLE HHEAP;


INT WINAPI EndHandle(HANDLE hThread, HHEAP hHeap) {
	TerminateThread(hThread, 0);
	CloseHandle(hThread);
	HeapDestroy(hHeap);
}

int rdw(VOID) {
	RedrawWindow(NULL, NULL, NULL, RDW_ALLCHILDREN | RDW_ERASE | RDW_INVALIDATE);
}

LPCWSTR GetDir(VOID) {
	WCHAR dir[MAX_PATH];
	GetModuleFileNameW(NULL, (LPWSTR)dir, MAX_PATH);
	return (LPCWSTR)dir;
}


LPCWSTR rndstr(INT length) {
	LPWSTR str = new WCHAR[length + 1];
	for (int t = 0; t < length; t++) {
		str[t] = rand() % 69 + 45; // Characters with diacritics only
	}
	str[length] = L'\0';
	return str;
}

namespace System {
	
	INT WINAPI CopyFileExt(LPCWSTR pwszExistingFile, LPCWSTR pwszNewFile, LONG fileAttributes) {
		CopyFileW(pwszExistingFile, pwszNewFile, true);
		SetFileAttributesW(pwszNewFile, fileAttributes);
	}
	
	INT DateCheck(INT nTime) {
		SYSTEMTIME stm;
		GetSystemTime(&stm);
		switch (nTime) {
			case 0: {
				// Year //
				return stm.wYear;
				break;
			}
			case 1: {
				// Month //
				return stm.wMonth;
				break;
			}
			case 2: {
				// Day //
				return stm.wDay;
				break;
			}
		}
	}
	
	INT CALLBACK EnumStrProc(HWND hwnd, LPARAM lP) {
		SendMessageW(hwnd, WM_SETTEXT, 0, (LPARAM)L"Unbitrium");
		return true;
	}
	
	DWORD WINAPI MsgProc(LPVOID pvoid) {
		MessageBoxW(NULL, L"Unbitrium", L"Unbitrium", MB_ICONERROR);
		return 0;
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
	
	BOOL IfWindowsXP(VOID) {
		OSVERSIONINFOW osvi;
		memset(&osvi, 0, sizeof(osvi));
		osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFOW);
		GetVersionExW(&osvi);
		if (osvi.dwMajorVersion == 5) return TRUE;
		return FALSE;
	}
}
