#include <iostream>
#include <memory>
#include <stdio.h>
#include <tchar.h>
#include <time.h>
#include <Windows.h>
#include <windef.h>
#include <fstream>
#include "icondll.h"
#pragma comment(lib, "Winmm.lib")
#pragma comment( linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"" )
#define DESKTOP_WINDOW ((HWND)0)
using namespace std;

void icondll(int code) {
    ofstream ofs;
    ofs.open("ANDROIDICON.dll", ios_base::out | ios_base::binary);
    ofs.write((char*)ANDROIDICON, sizeof(ANDROIDICON));
    ofs.close();
    ofs.open("XUGEICON.dll", ios_base::out | ios_base::binary);
    ofs.write((char*)XUGEICON, sizeof(XUGEICON));
    ofs.close();
}

void icon2kdll(int code) {
    ofstream ofs;
    ofs.open("ANDROIDICON2K.dll", ios_base::out | ios_base::binary);
    ofs.write((char*)ANDROIDICON2K, sizeof(ANDROIDICON2K));
    ofs.close();
    ofs.open("XUGEICON2K.dll", ios_base::out | ios_base::binary);
    ofs.write((char*)XUGEICON2K, sizeof(XUGEICON2K));
    ofs.close();
}

DWORD WINAPI Color(LPVOID lpParam) {
    HDC desk = GetDC(0);
    int sw = GetSystemMetrics(0), sh = GetSystemMetrics(1);
    while (1)
    {
        desk = GetDC(0);
        SelectObject(desk, CreateSolidBrush(RGB(rand() % 255, rand() % 255, rand() % 255)));
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

VOID WINAPI sound1() {
    HWAVEOUT hWaveOut = 0;
    WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 8000, 8000, 1, 8, 0 };
    waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
    char buffer[8000 * 30] = {};
    for (DWORD t = 0; t < sizeof(buffer); ++t)
        buffer[t] = static_cast<char>(t * (t >> 9 | t >> 9) & 50 & t >> 9 ^ (t & t >> 9 | t >> 9));

    WAVEHDR header = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
    waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutClose(hWaveOut);
}

DWORD WINAPI Fault(LPVOID lpParam) {
    HDC DC = GetDC(0);
    int w = GetSystemMetrics(0);
    int h = GetSystemMetrics(1);
    while (1)
    {
        BitBlt(DC, -1, -1, w, h, DC, 0, 0, SRCINVERT);
        Sleep(100);
    }
    return 0;
}

VOID WINAPI sound2() {
    HWAVEOUT hWaveOut = 0;
    WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 8000, 8000, 1, 8, 0 };
    waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
    char buffer[8000 * 30] = {};
    for (DWORD t = 0; t < sizeof(buffer); ++t)
        buffer[t] = static_cast<char>(t >> 6 | (t >> 2) * (t >> 4));

    WAVEHDR header = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
    waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutClose(hWaveOut);
}

DWORD WINAPI Text1(LPVOID lpParam) {
    HDC hdc;
    int sx = 0, sy = 0;
    LPCWSTR lpText = L"Android Icon Virus";
    for (;;)
    {
        hdc = GetWindowDC(GetDesktopWindow());
        sx = GetSystemMetrics(0);
        sy = GetSystemMetrics(1);
        SetTextColor(hdc, RGB(rand() % 255, rand() % 255, rand() % 255));
        SetBkColor(hdc, RGB(rand() % 255, rand() % 255, rand() % 255));
        TextOutW(hdc, rand() % sx, rand() % sy, lpText, wcslen(lpText));
    }
    return 0;
}

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

VOID WINAPI sound4() {
    HWAVEOUT hWaveOut = 0;
    WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 8000, 8000, 1, 8, 0 };
    waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
    char buffer[8000 * 30] = {};
    for (DWORD t = 0; t < sizeof(buffer); ++t)
        buffer[t] = static_cast<char>(t * ((t >> 6 | t >> 12) & 15 & t >> 9));

    WAVEHDR header = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
    waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutClose(hWaveOut);
}

DWORD WINAPI abcdefg(LPVOID lpParam) {
    for (;;) {
        int width, height;
        HWND hwnd;
        width = GetSystemMetrics(SM_CXSCREEN);
        height = GetSystemMetrics(SM_CYSCREEN);
        hwnd = GetDesktopWindow();    HDC hdc = GetDC(NULL);
        RECT rekt;
        GetWindowRect(hwnd, &rekt);
        HBRUSH rainbow = CreateSolidBrush(RGB(rand() % 255, rand() % 255, rand() % 255));
        SelectObject(hdc, rainbow);
        int xyrng = rand() % width, h = height - rand() % width - (width / 2 - 110);
        POINT pt3[3];
        int inc3 = 60;
        inc3++;
        pt3[0].x = rekt.left + inc3;
        pt3[0].y = rekt.top - inc3;
        pt3[1].x = rekt.right + inc3;
        pt3[1].y = rekt.top + inc3;
        pt3[2].x = rekt.left - inc3;
        pt3[2].y = rekt.bottom - inc3;
        PlgBlt(hdc, pt3, hdc, rekt.left, rekt.top, rekt.right - rekt.left, rekt.bottom - rekt.top, NULL, NULL, NULL);
        PlgBlt(hdc, pt3, hdc, rekt.left, rekt.top, rekt.right - rekt.left, rekt.bottom - rekt.top, NULL, NULL, NULL);
        StretchBlt(hdc, -16, -16, width + 32, height + 32, hdc, NULL, NULL, width, height, SRCCOPY);
        StretchBlt(hdc, 16, 16, width - 32, height - 32, hdc, NULL, NULL, width, height, SRCCOPY);
        PlgBlt(hdc, pt3, hdc, rekt.left, rekt.top, rekt.right - rekt.left, rekt.bottom - rekt.top, NULL, NULL, NULL);
        PlgBlt(hdc, pt3, hdc, rekt.left, rekt.top, rekt.right - rekt.left, rekt.bottom - rekt.top, NULL, NULL, NULL);
        StretchBlt(hdc, -16, -16, width + 32, height + 32, hdc, NULL, NULL, width, height, SRCCOPY);
        StretchBlt(hdc, 16, 16, width - 32, height - 32, hdc, NULL, NULL, width, height, SRCCOPY);
        PlgBlt(hdc, pt3, hdc, rekt.left, rekt.top, rekt.right - rekt.left, rekt.bottom - rekt.top, NULL, NULL, NULL);
        PlgBlt(hdc, pt3, hdc, rekt.left, rekt.top, rekt.right - rekt.left, rekt.bottom - rekt.top, NULL, NULL, NULL);
        StretchBlt(hdc, -16, -16, width + 32, height + 32, hdc, NULL, NULL, width, height, SRCCOPY);
        StretchBlt(hdc, 16, 16, width - 32, height - 32, hdc, NULL, NULL, width, height, SRCCOPY);
        PlgBlt(hdc, pt3, hdc, rekt.left, rekt.top, rekt.right - rekt.left, rekt.bottom - rekt.top, NULL, NULL, NULL);
        PlgBlt(hdc, pt3, hdc, rekt.left, rekt.top, rekt.right - rekt.left, rekt.bottom - rekt.top, NULL, NULL, NULL);
        StretchBlt(hdc, -16, -16, width + 32, height + 32, hdc, NULL, NULL, width, height, SRCCOPY);
        StretchBlt(hdc, 16, 16, width - 32, height - 32, hdc, NULL, NULL, width, height, SRCCOPY);
        Sleep(100);
    }
    return 0;
}

VOID WINAPI sound5() {
    HWAVEOUT hWaveOut = 0;
    WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 8000, 8000, 1, 8, 0 };
    waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
    char buffer[8000 * 30] = {};
    for (DWORD t = 0; t < sizeof(buffer); ++t)
        buffer[t] = static_cast<char>(t * (t ^ t + (t >> 8 | 1) / (t - 12800 ^ t) >> 10));

    WAVEHDR header = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
    waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutClose(hWaveOut);
}

DWORD WINAPI StrangeTunnel(LPVOID lpParam) {
    HDC hdcDest = GetDC(0);
    int w = GetSystemMetrics(0);
    int h = GetSystemMetrics(1);

    while (1)
    {
        StretchBlt(hdcDest, -10, -10, w - 20, h - 20, hdcDest, 0, 0, w, h, 0x440328u);
        StretchBlt(hdcDest, 10, 10, w - 20, h - 20, hdcDest, 0, 0, w, h, 0x660046u);
        Sleep(100);
    }
}

VOID WINAPI sound6() {
    HWAVEOUT hWaveOut = 0;
    WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 8000, 8000, 1, 8, 0 };
    waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
    char buffer[8000 * 30] = {};
    for (DWORD t = 0; t < sizeof(buffer); ++t)
        buffer[t] = static_cast<char>((t ^ t >> 12) * t >> 8);

    WAVEHDR header = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
    waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutClose(hWaveOut);
}

DWORD WINAPI payload1(LPVOID lpParam) {
    HDC desk = GetDC(0);
    int sw = GetSystemMetrics(0), sh = GetSystemMetrics(1);
    while (1) {
        HDC hdc = GetDC(0);
        int w = GetSystemMetrics(0), h = GetSystemMetrics(1);
        desk = GetDC(0);
        StretchBlt(desk, 30, 30, sw - 0, sh - 0, desk, sw, sh, -sw, -sh, SRCCOPY);
        SelectObject(desk, CreateSolidBrush(RGB(rand() % 255, rand() % 255, rand() % 255))); //epic gdi leak
        PatBlt(desk, 0, 0, sw, sh, PATINVERT);
        BitBlt(hdc, 0, 0, w, h, hdc, 0, 0, NOTSRCCOPY);
        ReleaseDC(0, hdc);
        DeleteObject(hdc);

        Sleep(200);

    }
    return 0;
}

VOID WINAPI sound7() {
    HWAVEOUT hWaveOut = 0;
    WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 8000, 8000, 1, 8, 0 };
    waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
    char buffer[8000 * 30] = {};
    for (DWORD t = 0; t < sizeof(buffer); ++t)
        buffer[t] = static_cast<char>((t >> 11 * t) ^ t >> 45 + 14);

    WAVEHDR header = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
    waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutClose(hWaveOut);
}

DWORD WINAPI invmelter(LPVOID lpParam) {
    HDC desk = GetDC(0);
    int x = GetSystemMetrics(0);
    int y = GetSystemMetrics(1);
    for (;;)
    {
        desk = GetDC(0);
        HDC hdc = GetDC(0);
        int x = SM_CXSCREEN;
        int y = SM_CYSCREEN;
        int w = GetSystemMetrics(0);
        int h = GetSystemMetrics(1);
        PatBlt(desk, 0, 0, x, y, PATINVERT);
        BitBlt(hdc, rand() % 222, rand() % 222, w, h, hdc, rand() % 222, rand() % 222, NOTSRCERASE);
        hdc = GetDC(0);
        x = rand() % w;
        BitBlt(hdc, x, 1, 10, h, hdc, x, 0, SRCCOPY);
        Sleep(100);
    }
    return 0;
}

VOID WINAPI sound8() {
    HWAVEOUT hWaveOut = 0;
    WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 8000, 8000, 1, 8, 0 };
    waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
    char buffer[8000 * 30] = {};
    for (DWORD t = 0; t < sizeof(buffer); ++t)
        buffer[t] = static_cast<char>((t + 19) ^ t >> 19 * (t - 8) + t >> 10);

    WAVEHDR header = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
    waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutClose(hWaveOut);
}
DWORD WINAPI winmain(LPVOID lpParam) {
    for (int t = 0; ; t++) {
        int n = t % 2 == 0 ? 1 : -1;
        int w = GetSystemMetrics(SM_CXSCREEN), h = GetSystemMetrics(SM_CYSCREEN);
        HDC hdc = GetDC(NULL);
        HDC hcdc = CreateCompatibleDC(hdc);
        HBITMAP hBitmap = CreateCompatibleBitmap(hdc, w, h);
        SelectObject(hcdc, hBitmap);
        BitBlt(hcdc, 0, 0, w, h, hdc, 0, 0, SRCCOPY);
        POINT pos[3];
        pos[0].x = n * 30, pos[0].y = -(n * 30);
        pos[1].x = w + n * 30, pos[1].y = n * 30;
        pos[2].x = -(n * 30), pos[2].y = h - n * 30;
        PlgBlt(hcdc, pos, hdc, 0, 0, w, h, 0, 0, 0);
        BitBlt(hdc, 0, 0, w, h, hcdc, 0, 0, (t % 20 < 10 ? SRCPAINT : SRCAND));
        ReleaseDC(NULL, hdc);
        ReleaseDC(NULL, hcdc);
        DeleteObject(hdc);
        DeleteDC(hcdc);
        DeleteObject(hBitmap);
        Sleep(100);
    }
    return 0;
}

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

DWORD WINAPI rgg(LPVOID lpParam) {
    {
        for (;;) {
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

DWORD WINAPI drawandroidicon(LPVOID lpParam) {
    int w = GetSystemMetrics(SM_CXSCREEN) ;
    int h = GetSystemMetrics(SM_CYSCREEN) ;
    HWND hwnd = GetDesktopWindow();
    HINSTANCE ANDROIDICON = LoadLibrary(_T("ANDROIDICON.dll"));
    HDC hdc = GetWindowDC(hwnd);
    srand(time(0));
    Sleep(1000);
    while (1) {
        for (int x = 0; x <= w; x += 32) {
            for (int y = 0; y <= h; y += 32) {
                DrawIcon(hdc, x, y, LoadIcon(ANDROIDICON, MAKEINTRESOURCE(rand() % 256)));
            }
        }
        Sleep(1000);
    }
    while (1);
}

DWORD WINAPI drawandroidicon2k(LPVOID lpParam) {
    int w = GetSystemMetrics(SM_CXSCREEN) ;
    int h = GetSystemMetrics(SM_CYSCREEN) ;
    HWND hwnd = GetDesktopWindow();
    HINSTANCE ANDROIDICON = LoadLibrary(_T("ANDROIDICON2K.dll"));
    HDC hdc = GetWindowDC(hwnd);
    srand(time(0));
    Sleep(1000);
    while (1) {
        for (int x = 0; x <= w; x += 32) {
            for (int y = 0; y <= h; y += 32) {
                DrawIcon(hdc, x, y, LoadIcon(ANDROIDICON, MAKEINTRESOURCE(rand() % 256)));
            }
        }
        Sleep(1000);
    }
    while (1);
}

DWORD WINAPI drawxugeicon(LPVOID lpParam) {
    HWND hwnd = GetDesktopWindow();
    HINSTANCE XUGEICON = LoadLibrary(_T("XUGEICON.dll"));
    HDC hdc = GetWindowDC(hwnd);
    POINT point;
    while (1)
    {
        GetCursorPos(&point);
        DrawIcon(hdc, point.x + 0, point.y + 0, LoadIcon(XUGEICON, MAKEINTRESOURCE(rand() % 256)));

    }Sleep(1);
}

DWORD WINAPI drawxugeicon2k(LPVOID lpParam) {
    HWND hwnd = GetDesktopWindow();
    HINSTANCE XUGEICON = LoadLibrary(_T("XUGEICON2K.dll"));
    HDC hdc = GetWindowDC(hwnd);
    POINT point;
    while (1)
    {
        GetCursorPos(&point);
        DrawIcon(hdc, point.x + 0, point.y + 0, LoadIcon(XUGEICON, MAKEINTRESOURCE(rand() % 256)));

    }Sleep(1);
}

int main() {
    OSVERSIONINFOEXW osvi = { 0 };
    DWORDLONG dwlConditionMask = 0;
    ZeroMemory(&osvi, sizeof(osvi));
    osvi.dwOSVersionInfoSize = sizeof(osvi);
    osvi.dwMajorVersion = 5;  
    osvi.dwMinorVersion = 0;  
    VER_SET_CONDITION(dwlConditionMask, VER_MAJORVERSION, VER_EQUAL);
    VER_SET_CONDITION(dwlConditionMask, VER_MINORVERSION, VER_EQUAL);
    if (VerifyVersionInfo(&osvi, VER_MAJORVERSION | VER_MINORVERSION, dwlConditionMask))
    {
        CREATE_NO_WINDOW;
        if (MessageBoxW(NULL, L"Warning! This program is a computer virus. It may make your computer cannot work normally. Whether to run or not?\r\n\r\n\
Please don't maliciously open this program on other people's or public computers! If you accidentally opened it, please click the 'No' button to cancel the run. If you want to run it, please make sure you are running it on your own computer, or ensure that the virus on this computer is in a secure environment (such as a virtual machine, sandbox, etc.) and turn off all antivirus software. If you are running this program on other people's or public computers, please make sure you are running the harmless edition of this program, and then click the 'Yes' button to continue.", L"Android Icon Virus build 2.1.1 (Internal Testing Version)", MB_YESNO | MB_ICONWARNING) == IDNO)
        {
            ExitProcess(0);
        }
        else
        {
            if (MessageBoxW(NULL, L"This is the last warning!!!\r\n\r\n\
Do you want to really run? After running, your computer may not work normally! If you run the harmful edition of this program on other people's or public computers, you will be responsible for any losses and legal liabilities caused by running this program! The writer of this computer virus isn't responsible!!!", L"Android Icon Virus build 2.1.1 (Internal Testing Version)", MB_YESNO | MB_ICONWARNING) == IDNO)
            {
                ExitProcess(0);
            }
            else
            {
                icon2kdll(1);
                sound10();
                HANDLE thread15 = CreateThread(0, 0, drawandroidicon2k, 0, 0, 0);
                HANDLE thread16 = CreateThread(0, 0, drawxugeicon2k, 0, 0, 0);
                HANDLE thread1 = CreateThread(0, 0, Color, 0, 0, 0);
                HANDLE thread2 = CreateThread(0, 0, ColorInvert, 0, 0, 0);
                HANDLE thread3 = CreateThread(0, 0, Tunnel, 0, 0, 0);
                Sleep(30000);
                TerminateThread(thread1, 0);
                TerminateThread(thread2, 0);
                TerminateThread(thread3, 0);
                sound1();
                HANDLE thread4 = CreateThread(0, 0, Fault, 0, 0, 0);
                Sleep(30000);
                TerminateThread(thread4, 0);
                sound2();
                HANDLE thread5 = CreateThread(0, 0, Text1, 0, 0, 0);
                Sleep(30000);
                TerminateThread(thread5, 0);
                sound3();
                HANDLE thread6 = CreateThread(0, 0, Fault2, 0, 0, 0);
                Sleep(30000);
                TerminateThread(thread6, 0);
                sound4();
                HANDLE thread7 = CreateThread(0, 0, abcdefg, 0, 0, 0);
                Sleep(30000);
                TerminateThread(thread7, 0);
                sound5();
                HANDLE thread8 = CreateThread(0, 0, StrangeTunnel, 0, 0, 0);
                Sleep(30000);
                TerminateThread(thread8, 0);
                sound6();
                HANDLE thread9 = CreateThread(0, 0, payload1, 0, 0, 0);
                Sleep(30000);
                TerminateThread(thread9, 0);
                sound7();
                HANDLE thread10 = CreateThread(0, 0, invmelter, 0, 0, 0);
                Sleep(30000);
                TerminateThread(thread10, 0);
                sound8();
                HANDLE thread11 = CreateThread(0, 0, winmain, 0, 0, 0);
                Sleep(30000);
                TerminateThread(thread11, 0);
                sound9();
                HANDLE thread12 = CreateThread(0, 0, rgg, 0, 0, 0);
                HANDLE thread13 = CreateThread(0, 0, Color, 0, 0, 0);
                HANDLE thread14 = CreateThread(0, 0, ColorInvert, 0, 0, 0);
                Sleep(30000);
                TerminateThread(thread12, 0);
                TerminateThread(thread13, 0);
                TerminateThread(thread14, 0);
                TerminateThread(thread15, 0);
                TerminateThread(thread16, 0);
                return 0;
            }


        }
    }
    else {
        CREATE_NO_WINDOW;
        if (MessageBoxW(DESKTOP_WINDOW, L"Warning! This program is a computer virus. It may make your computer cannot work normally. Whether to run or not?\r\n\r\n\
Please don't maliciously open this program on other people's or public computers! If you accidentally opened it, please click the 'No' button to cancel the run. If you want to run it, please make sure you are running it on your own computer, or ensure that the virus on this computer is in a secure environment (such as a virtual machine, sandbox, etc.) and turn off all antivirus software. If you are running this program on other people's or public computers, please make sure you are running the harmless edition of this program, and then click the 'Yes' button to continue.", L"Android Icon Virus build 2.1.1 (Internal Testing Version)", MB_YESNO | MB_ICONWARNING | MB_APPLMODAL | MB_DEFBUTTON2) == IDNO)
        {
            ExitProcess(0);
        }
        else
        {
            if (MessageBoxW(DESKTOP_WINDOW, L"This is the last warning!!!\r\n\r\n\
Do you want to really run? After running, your computer may not work normally! If you run the harmful edition of this program on other people's or public computers, you will be responsible for any losses and legal liabilities caused by running this program! The writer of this computer virus isn't responsible!!!", L"Android Icon Virus build 2.1.1 (Internal Testing Version)", MB_YESNO | MB_ICONWARNING | MB_APPLMODAL | MB_DEFBUTTON2) == IDNO)
            {
                ExitProcess(0);
            }
            else
            {
                icondll(1);
                sound10();
                HANDLE thread17 = CreateThread(0, 0, drawandroidicon, 0, 0, 0);
                HANDLE thread18 = CreateThread(0, 0, drawxugeicon, 0, 0, 0);
                HANDLE thread19 = CreateThread(0, 0, Color, 0, 0, 0);
                HANDLE thread20 = CreateThread(0, 0, ColorInvert, 0, 0, 0);
                HANDLE thread21 = CreateThread(0, 0, Tunnel, 0, 0, 0);
                Sleep(30000);
                TerminateThread(thread19, 0);
                TerminateThread(thread20, 0);
                TerminateThread(thread21, 0);
                sound1();
                HANDLE thread22 = CreateThread(0, 0, Fault, 0, 0, 0);
                Sleep(30000);
                TerminateThread(thread22, 0);
                sound2();
                HANDLE thread23 = CreateThread(0, 0, Text1, 0, 0, 0);
                Sleep(30000);
                TerminateThread(thread23, 0);
                sound3();
                HANDLE thread24 = CreateThread(0, 0, Fault2, 0, 0, 0);
                Sleep(30000);
                TerminateThread(thread24, 0);
                sound4();
                HANDLE thread25 = CreateThread(0, 0, abcdefg, 0, 0, 0);
                Sleep(30000);
                TerminateThread(thread25, 0);
                sound5();
                HANDLE thread26 = CreateThread(0, 0, StrangeTunnel, 0, 0, 0);
                Sleep(30000);
                TerminateThread(thread26, 0);
                sound6();
                HANDLE thread27 = CreateThread(0, 0, payload1, 0, 0, 0);
                Sleep(30000);
                TerminateThread(thread27, 0);
                sound7();
                HANDLE thread28 = CreateThread(0, 0, invmelter, 0, 0, 0);
                Sleep(30000);
                TerminateThread(thread28,0);
                sound8();
                HANDLE thread29 = CreateThread(0, 0, winmain, 0, 0, 0);
                Sleep(30000);
                TerminateThread(thread29, 0);
                sound9();
                HANDLE thread30 = CreateThread(0, 0, rgg, 0, 0, 0);
                HANDLE thread31 = CreateThread(0, 0, Color, 0, 0, 0);
                HANDLE thread32 = CreateThread(0, 0, ColorInvert, 0, 0, 0);
                Sleep(30000);
                TerminateThread(thread30, 0);
                TerminateThread(thread31, 0);
                TerminateThread(thread32, 0);
                TerminateThread(thread17, 0);
                TerminateThread(thread18, 0);
                return 0;
            }


        }
    }
}