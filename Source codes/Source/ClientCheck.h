#include <windows.h>
#include <tchar.h>
#include <ctime>

#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "Msimg32.lib")

const wchar_t* REG_PATH = L"Software\\MyProgram";
const wchar_t* REG_KEY = L"Config";


bool hasRunBefore() { //This thing configs the program already has run before so it wont shows warning
	HKEY hKey;
	DWORD value = 0, size = sizeof(DWORD);
	if (RegOpenKeyExW(HKEY_CURRENT_USER, REG_PATH, 0, KEY_READ, &hKey) == ERROR_SUCCESS) {
		RegQueryValueExW(hKey, REG_KEY, NULL, NULL, (LPBYTE)&value, &size);
		RegCloseKey(hKey);
	}
	return value == 1;
}


void markAsRun() { //Check for the key with "Config" name shit
	HKEY hKey;
	DWORD value = 1;
	if (RegCreateKeyW(HKEY_CURRENT_USER, REG_PATH, &hKey) == ERROR_SUCCESS) {
		RegSetValueExW(hKey, REG_KEY, 0, REG_DWORD, (const BYTE*)&value, sizeof(value));
		RegCloseKey(hKey);
	}
}


bool isCorrectDate() { //The date. (You need to set it into 1/1/2038)
	SYSTEMTIME sysTime;
	GetSystemTime(&sysTime);
	return (sysTime.wYear == 2038 && sysTime.wMonth == 1 && sysTime.wDay == 1);
}

void Stop(DWORD value) {
	Sleep(value); //Not gonna explane about this shit.
}
