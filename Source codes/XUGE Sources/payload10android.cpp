#include <iostream>
#include <memory>
#include <stdio.h>
#include <tchar.h>
#include <time.h>
#include <Windows.h>
#pragma comment(lib, "Winmm.lib")
#pragma comment( linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"" )

VOID WINAPI sound9() {
    HWAVEOUT hWaveOut = 0;
    WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 8000, 8000, 1, 8, 0 };
    waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
    char buffer[8000 * 30] = {};
    for (DWORD t = 0; t < sizeof(buffer); ++t)
        buffer[t] = static_cast<char>(t * (t & 16384 ? 6 : 5) * (3 + (1 & t >> 7)) >> (3 & t >> 7) | t >> 2);

    WAVEHDR header = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
    waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutClose(hWaveOut);
}

DWORD WINAPI Color(LPVOID lpParam) {
    {
        HDC desk = GetDC(0);
        int sw = GetSystemMetrics(0), sh = GetSystemMetrics(1);
        while (1)
        {
            desk = GetDC(0);
            SelectObject(desk, CreateSolidBrush(RGB(rand() % 255, rand() % 255, rand() % 255))); //epic gdi leak
            PatBlt(desk, 0, 0, sw, sh, PATINVERT);
            Sleep(250);
        }
        return 0;
    }
    Sleep(30000);
}

DWORD WINAPI ColorInvert(LPVOID lpParam) {
    {
        for (;;) {
            HDC hdc = GetDC(0);
            int w = GetSystemMetrics(0), h = GetSystemMetrics(1);

            BitBlt(hdc, 0, 0, w, h, hdc, 0, 0, NOTSRCCOPY);

            ReleaseDC(0, hdc);
            DeleteObject(hdc);

            Sleep(250);
        }
        return 0;
    }
    Sleep(30000);
}

DWORD WINAPI rgg(LPVOID lpParam) {
    {
        for (; ; ) {
            HDC hdc = GetDC(0);
            int w = GetSystemMetrics(0), h = GetSystemMetrics(1);
            POINT pos[3];
            pos[0].x = 10, pos[0].y = -30;
            pos[1].x = w + 10, pos[1].y = 30;
            pos[2].x = -40, pos[2].y = h - 30;
            PlgBlt(hdc, pos, hdc, 0, 0, w, h, 0, 0, 0);
            ReleaseDC(NULL, hdc);
            DeleteObject(hdc);
            Sleep(200);
        }
        return 0;
    }
    Sleep(30000);
}

int main() {
    sound9();
    HANDLE thread1 = CreateThread(0, 0, Color, 0, 0, 0);
    HANDLE thread2 = CreateThread(0, 0, ColorInvert, 0, 0, 0);
    HANDLE thread3 = CreateThread(0, 0, rgg, 0, 0, 0);
    Sleep(30000);
    return 0;
}