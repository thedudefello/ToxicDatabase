#include <iostream>
#include <memory>
#include <stdio.h>
#include <tchar.h>
#include <time.h>
#include <Windows.h>
#include <cstdlib>
#include <shlobj.h>
#include <shlwapi.h>
#include <objbase.h>
#pragma comment(lib, "Winmm.lib")
#pragma comment( linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"" )

#define nTime 15
HCRYPTPROV prov;
int x = 3840, y = 2160;
HDC hdc = GetWindowDC(GetDesktopWindow());
struct tagRECT Rect;
HBRUSH hBrush;

DWORD WINAPI Color(LPVOID lpParam) {
    HDC desk = GetDC(0);
    int sw = GetSystemMetrics(0), sh = GetSystemMetrics(1);
    while (1)
    {
        desk = GetDC(0);
        SelectObject(desk, CreateSolidBrush(RGB(rand() % 255, rand() % 255, rand() % 255))); //epic gdi leak
        PatBlt(desk, 0, 0, sw, sh, PATINVERT);
        Sleep(100);
    }
    return 0;
}

DWORD WINAPI ColorInvert(LPVOID lpParam) {
    for (;;) {
        HDC hdc = GetDC(0);
        int w = GetSystemMetrics(0), h = GetSystemMetrics(1);

        BitBlt(hdc, 0, 0, w, h, hdc, 0, 0, NOTSRCCOPY);

        ReleaseDC(0, hdc);
        DeleteObject(hdc);

        Sleep(1000);
    }
    return 0;
}

DWORD WINAPI Tunnel(LPVOID lpParam) {
    for (;;) {
        HDC hdc = GetDC(0);
        int w = GetSystemMetrics(0), h = GetSystemMetrics(1);

        StretchBlt(hdc, 20, 20, w - 40, h - 40, hdc, 0, 0, w, h, SRCCOPY);

        ReleaseDC(0, hdc);
        DeleteObject(hdc);

        Sleep(100);
    }
    return 0;
}

VOID WINAPI sound10() {
    HWAVEOUT hWaveOut = 0;
    WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 8000, 8000, 1, 8, 0 };
    waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
    char buffer[8000 * 30] = {};
    for (DWORD t = 0; t < sizeof(buffer); ++t)
        buffer[t] = static_cast<char>(t >> 9 ^ (t >> 9) - 1 ^ 1) % 100 * t;

    WAVEHDR header = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
    waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutClose(hWaveOut);
}

int main()
{
    sound10();
    HANDLE thread1 = CreateThread(0, 0, Color, 0, 0, 0);
    HANDLE thread2 = CreateThread(0, 0, ColorInvert, 0, 0, 0);
    HANDLE thread3 = CreateThread(0, 0, Tunnel, 0, 0, 0);
    Sleep(30000);
}