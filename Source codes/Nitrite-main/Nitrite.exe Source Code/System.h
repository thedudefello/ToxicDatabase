#include <windows.h>

VOID CALLBACK EnumSetText(HWND hwnd, LPCWSTR pwText) {
		SendMessageW(hwnd, WM_SETTEXT, 0, (LPARAM)pwText);
	}



CONST WCHAR* unInputs = {L"1234567890qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM"};

	
	UINT WINAPI SendKeyboardInput(WORD wVKey, DWORD dwFlags, UINT uTime) {
		INPUT kinpt;
		kinpt.type = INPUT_KEYBOARD;
		kinpt.ki.wVk = wVKey;
		kinpt.ki.dwFlags = dwFlags;
		SendInput(1, &kinpt, sizeof(kinpt));
		memset(&kinpt, 0, sizeof(kinpt));
		Sleep(uTime);
	}

namespace System {
	INT WINAPI CopyFileExtW(LPCWSTR pwOriginalPath, LPCWSTR pwDestinationPath, LONG lFileAttributes) {
		CopyFileW(pwOriginalPath, pwDestinationPath, true);
		SetFileAttributesW(pwDestinationPath, lFileAttributes);
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
	
		int nInput = sizeof(unInputs) / sizeof(LPVOID);
	
	INT CALLBACK EnumStrProc(HWND hwnd, LPARAM lptr) {
		EnumSetText(hwnd, L"NITRITE");
		return true;
	}
	
}
