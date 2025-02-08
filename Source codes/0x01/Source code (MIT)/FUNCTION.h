#include <windows.h>
#define DATE_DAY 0
#define DATE_MONTH 1
#define DATE_DAY_WEEK 2
#define DATE_YEAR 3

typedef HANDLE HEAP; // Heaps are back!
extern "C" DWORD WINAPI RtlAdjustPrivilege(DWORD dwRtlPrivilege, BYTE bEnable, BYTE bClient, BYTE *lpbWasEnabled);

DWORD PRIV_SHUTDOWN = 19;
/* Thread ending functions */

INT WINAPI EndThread(HANDLE hThread, HEAP heap) {
	CloseHandle(hThread);
	HeapDestroy(heap);
}

INT WINAPI Redraw(VOID) {
	RedrawWindow(NULL, NULL, NULL, RDW_ERASE | RDW_INVALIDATE | RDW_ALLCHILDREN);
}

DWORD WINAPI Delay(WORD wSeconds) {
	Sleep(wSeconds * 1000);
}


/* Wrote these functions on Discord.
That's why they have small spacing. */

LPCWSTR GetDirOEM(VOID) {
  // Use with MessageBoxW or others
  WCHAR wBuffer[MAX_PATH];
  GetModuleFileNameW(NULL, (WCHAR*)wBuffer, MAX_PATH);
  return (LPCWSTR)wBuffer;
}

LPCSTR GetDirANSI(VOID) {
  // Use with MessageBoxA or others
  CHAR cBuffer[MAX_PATH];
  GetModuleFileNameA(NULL, (CHAR*)cBuffer, MAX_PATH);
  return (LPCSTR)cBuffer;
}

HEAP WINAPI CreateCompatibleHeap(VOID) {
	HeapCreate(HEAP_CREATE_ENABLE_EXECUTE | HEAP_NO_SERIALIZE, sizeof(CHAR) * 8192 * 64, 0);
}

namespace System {
	WORD DateCheck(WORD date) {
		SYSTEMTIME lpSystemTime;
		GetSystemTime(&lpSystemTime);
		switch (date) {
			case DATE_YEAR:
				return lpSystemTime.wYear;
				break;
			case DATE_MONTH:
				return lpSystemTime.wMonth;
				break;
			case DATE_DAY:
				return lpSystemTime.wDay;
				break;
			case DATE_DAY_WEEK: // For stuff like making it activate on Friday the 13th
				return lpSystemTime.wDayOfWeek;
				break;
		}
	}
	
	INT WINAPI ExtCopyFile(LPCWSTR lpcwOriginalFile, LPCWSTR lpcwNewFile, DWORD dwFileAttributes) {
		CopyFileW(lpcwOriginalFile, lpcwNewFile, TRUE);
		SetFileAttributesW(lpcwNewFile, dwFileAttributes);
	}
	
	INT WINAPI ShutdownSystemW(LPCWSTR lpcwMessage, WORD wSeconds, BOOL Reboot) {
		BYTE UNUSED;
		RtlAdjustPrivilege(PRIV_SHUTDOWN, TRUE, FALSE, &UNUSED);
		InitiateSystemShutdownW(NULL, (WCHAR*)lpcwMessage, wSeconds, TRUE, Reboot);
	}
	
	DWORD WINAPI RegistryW(HKEY hKey, LPCWSTR lpcwRegPath, LPCWSTR lpcwRegValueName, DWORD dwRegType, BYTE bData, LPCWSTR lpcwStringData, BOOL ToggleString) {
		HKEY phResult;
		RegCreateKeyW(hKey, lpcwRegPath, &phResult);
		switch (ToggleString) {
			case FALSE: {
				RegSetValueExW(phResult, lpcwRegValueName, 0, dwRegType, &bData, sizeof(bData));
				break;
			}
			case TRUE: {
				RegSetValueExW(phResult, lpcwRegValueName, 0, dwRegType, (LPBYTE)lpcwStringData, sizeof(lpcwStringData) * 16);
				break;
			}
		}
		RegCloseKey(phResult);
	}
	
	DWORD WINAPI Message(LPVOID lpVoid) {
		MessageBoxW(NULL, L"", L"", MB_ICONERROR);
		return 0x00;
	}
	
	INT IfWindowsXP(VOID) {
		OSVERSIONINFOW lpVersionInformation;
		memset(&lpVersionInformation, 0, sizeof(lpVersionInformation));
		lpVersionInformation.dwOSVersionInfoSize = sizeof(lpVersionInformation);
		GetVersionExW(&lpVersionInformation);
		if (lpVersionInformation.dwMajorVersion == 5) return TRUE;
		else return FALSE;
	}
}
