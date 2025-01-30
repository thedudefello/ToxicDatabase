#include <iostream>
#include <memory>
#include <stdio.h>
#include <tchar.h>
#include <time.h>
#include <Windows.h>
#pragma comment(lib, "Winmm.lib")
#pragma comment( linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"" )

VOID WINAPI sound3() {
    HWAVEOUT hWaveOut = 0;
    WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 8000, 8000, 1, 8, 0 };
    waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
    char buffer[8000 * 30] = {};
    for (DWORD t = 0; t < sizeof(buffer); ++t)
        buffer[t] = static_cast<char>(6 * t & t >> 6 | 3 * t & 4 * t >> 10);

    WAVEHDR header = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
    waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutClose(hWaveOut);
}

DWORD WINAPI Fault2(LPVOID lpParam) {
    HDC hdc = GetDC(0);
    int w = GetSystemMetrics(0);
    int h = GetSystemMetrics(1);
    for (;;)
    {
        int v5 = w - 5;
        int v6 = w - 20;
        StretchBlt(hdc, -5, -5, v6, v5, hdc, 0, 0, w, h, NOTSRCERASE);
        StretchBlt(hdc, 5, 5, v6, v5, hdc, 0, 0, w, h, NOTSRCERASE);
        StretchBlt(hdc, -5, -5, v6, w - 5, hdc, 0, 0, h, w, SRCINVERT);
        StretchBlt(hdc, 5, 5, v6, w - 5, hdc, 0, 0, h, w, SRCINVERT);
        Sleep(rand() % 500);
        Sleep(100);
    }
}

int main() {
    sound3();
    HANDLE thread1 = CreateThread(0, 0, Fault2, 0, 0, 0);
    Sleep(30000);
}