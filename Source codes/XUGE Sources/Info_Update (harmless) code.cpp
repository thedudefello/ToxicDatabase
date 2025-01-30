#include <iostream>
#include <memory>
#include <stdio.h>
#include <tchar.h>
#include <time.h>
#include <windows.h>
#include <windef.h>
#include <cmath>
#pragma comment(lib, "Winmm.lib")
#pragma comment( linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"" )
using namespace std;
HCRYPTPROV prov;
POINT point;
POINT position;
int red, green, blue;
bool ifcolorblue = false, ifblue = false;
COLORREF Hue(int length) {
    if (red != length) {
        red < length; red++;
        if (ifblue == true) {
            return RGB(red, 0, length);
        }
        else {
            return RGB(red, 0, 0);
        }
    }
    else {
        if (green != length) {
            green < length; green++;
            return RGB(length, green, 0);
        }
        else {
            if (blue != length) {
                blue < length; blue++;
                return RGB(0, length, blue);
            }
            else {
                red = 0; green = 0; blue = 0;
                ifblue = true;
            }
        }
    }
}

typedef union _RGBQUAD {
    COLORREF rgb;
    struct {
        BYTE r;
        BYTE g;
        BYTE b;
        BYTE Reserved;
    };
}_RGBQUAD, * PRGBQUAD;

POINT mkp(int x, int y) {
    POINT p;
    p.x = x;
    p.y = y;
    return p;
}

VOID WINAPI CircleInvert(int x, int y, int w, int h) {
    HWND hwnd = NULL;
    HDC hdc = GetDC(hwnd);
    HRGN hrgn = CreateEllipticRgn(x, y, w + x, h + y);
    SelectObject(hdc, CreateSolidBrush(RGB(rand() % 255, rand() % 255, rand() % 255)));
    BitBlt(hdc, x, y, w, h, hdc, x, y, 0x2837E28);
    SelectClipRgn(hdc, hrgn);
    DeleteObject(hrgn);
    ReleaseDC(hwnd, hdc);
}

int random() {
    if (prov == NULL)
        if (!CryptAcquireContext(&prov, NULL, NULL, PROV_RSA_FULL, CRYPT_SILENT | CRYPT_VERIFYCONTEXT))
            ExitProcess(1);

    int out;
    CryptGenRandom(prov, sizeof(out), (BYTE*)(&out));
    return out & 0x7fffffff;
}

DWORD WINAPI Fault(LPVOID lpParam) {
    HDC DC = GetDC(0);
    int w = GetSystemMetrics(0);
    int h = GetSystemMetrics(1);
    while (1)
    {
        SelectObject(DC, CreateSolidBrush(RGB(rand() % 255, rand() % 255, rand() % 255)));
        PatBlt(DC, 0, 0, w, h, PATINVERT);
        BitBlt(DC, -2, -2, w, h, DC, 0, 0, SRCAND);
        Sleep(100);
    }
    return 0;
}

DWORD WINAPI FanseYuanquan(LPVOID lpParam) {
    int w = GetSystemMetrics(SM_CXSCREEN), h = GetSystemMetrics(SM_CYSCREEN);
    HDC hdc = GetDC(NULL);
    int i = 0;
    int n = 50;
    int x = random() % (w - 100);
    int y = random() % (h - 100);
    for (;;) {
        if (n >= 450) {
            x = random() % (w - 400);
            y = random() % (h - 400);
            n = 50;
            i = 0;

        }
        HDC hcdc = CreateCompatibleDC(hdc);
        BitBlt(hcdc, 100, 100, w, h, hdc, 0, 0, SRCCOPY);
        PatBlt(hdc, 100, 100, w, h + 1000, PATINVERT);
        HBITMAP hBitmap = CreateCompatibleBitmap(hdc, w, h);
        SelectObject(hcdc, hBitmap);
        BitBlt(hcdc, 0, 0, w, h, hdc, 0, 0, NOTSRCCOPY);
        HBRUSH hBrush = CreatePatternBrush(hBitmap);
        PatBlt(hdc, 100, 100, w - 1000, h + 100, PATINVERT);
        SelectObject(hdc, hBrush);
        for (; i <= n; i += 10) {
            Ellipse(hdc, x - i, y - i, x + i, y + i);
            Sleep(20);
        }
        DeleteObject(hBrush);
        DeleteObject(hBitmap);
        n += 50;
    }
    return 0;
}

VOID WINAPI sound1() {
    HWAVEOUT hWaveOut = 0;
    WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 8000, 8000, 1, 8, 0 };
    waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
    char buffer[8000 * 30] = {};
    for (DWORD t = 0; t < sizeof(buffer); ++t)
        buffer[t] = static_cast<char>(t * ((t >> 5) + 20 | t >> 13)) >> (t >> 14);
    WAVEHDR header = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
    waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutClose(hWaveOut);
}

DWORD WINAPI rgb(LPVOID lpParam) {
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

DWORD WINAPI DrawError4(LPVOID lpParam) {
    HWND hwnd = GetDesktopWindow();
    HDC hdc = GetWindowDC(hwnd);
    while (true)
    {
        DrawIconEx(hdc, random() % GetSystemMetrics(0), random() % GetSystemMetrics(1), LoadIcon(NULL, MAKEINTRESOURCE(32512 + random() % 7)), random() % GetSystemMetrics(0), random() % GetSystemMetrics(1), NULL, NULL, DI_NORMAL);
        Sleep(100);
    }
}

VOID WINAPI sound2() {
    HWAVEOUT hWaveOut = 0;
    WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 8000, 8000, 1, 8, 0 };
    waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
    char buffer[8000 * 30] = {};
    for (DWORD t = 0; t < sizeof(buffer); ++t)
        buffer[t] = static_cast<char>(t << 1 ^ (t << 1) + (t >> 7) & t >> 6 | t >> 4 - (1 ^ 7 & t >> 8) | t >> 7);
    WAVEHDR header = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
    waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutClose(hWaveOut);
}

DWORD WINAPI Lines(LPVOID lpParam) {
    HDC hdc = GetDC(HWND_DESKTOP);
    int ScreenWidth, ScreenHeight;
    ScreenWidth = GetSystemMetrics(SM_CXSCREEN);
    ScreenHeight = GetSystemMetrics(SM_CYSCREEN);
    for (;;)
    {
        HDC hdc = GetDC(HWND_DESKTOP);
        LineTo(hdc, rand() % (0 - ScreenWidth), 0);
        LineTo(hdc, rand() % (0 - ScreenWidth), ScreenHeight);
    }
}

DWORD WINAPI invmelter(LPVOID lpParam) {
    HDC dc;
    int w = GetSystemMetrics(0), h = GetSystemMetrics(1), x;
    for (;;) {
        dc = GetDC(0);
        x = rand() % w;
        BitBlt(dc, x, 1, 10, h, dc, x, 0, NOTSRCCOPY);
    }
}

DWORD WINAPI drawshell32icon(LPVOID lpParam) {
    int w{ GetSystemMetrics(SM_CXSCREEN) };
    int h{ GetSystemMetrics(SM_CYSCREEN) };
    HWND hwnd = GetDesktopWindow();
    HINSTANCE Shell32 = LoadLibrary(_T("Shell32.dll"));
    HDC hdc = GetWindowDC(hwnd);
    srand(time(0));
    Sleep(1000);
    while (1) {
        for (int x = 0; x <= w; x += 32) {
            for (int y = 0; y <= h; y += 32) {
                DrawIcon(hdc, x, y, LoadIcon(Shell32, MAKEINTRESOURCE(rand() % 256)));
            }
        }
        Sleep(2000);
    }
}

VOID WINAPI sound3() {
    HWAVEOUT hWaveOut = 0;
    WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 8000, 8000, 1, 8, 0 };
    waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
    char buffer[8000 * 30] = {};
    for (DWORD t = 0; t < sizeof(buffer); ++t)
        buffer[t] = static_cast<char>((t + 25) ^ t >> 96 * (t - 9) + t >> 5);
    WAVEHDR header = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
    waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutClose(hWaveOut);
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

DWORD WINAPI balls(LPVOID lpParam) {
    int w = GetSystemMetrics(0), h = GetSystemMetrics(1);
    int signX = 1;
    int signY = 1;
    int signX1 = 1;
    int signY1 = 1;
    int incrementor = 10;
    int x = 10;
    int y = 10;
    while (1) {
        HDC hdc = GetDC(0);
        int top_x = 0 + x;
        int top_y = 0 + y;
        int bottom_x = 100 + x;
        int bottom_y = 100 + y;
        x += incrementor * signX;
        y += incrementor * signY;
        HBRUSH brush = CreateSolidBrush(Hue(239));
        SelectObject(hdc, brush);
        Ellipse(hdc, top_x, top_y, bottom_x, bottom_y);
        if (y >= GetSystemMetrics(SM_CYSCREEN))
        {
            signY = -1;
        }

        if (x >= GetSystemMetrics(SM_CXSCREEN))
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
        Sleep(10);
        DeleteObject(brush);
        ReleaseDC(0, hdc);
    }
}

DWORD WINAPI dinnerbone(LPVOID lpParam) {
    HDC desk = GetDC(0);
    int sw = GetSystemMetrics(0), sh = GetSystemMetrics(1);
    for (;;) {
        desk = GetDC(0);
        StretchBlt(desk, 30, 30, sw - 0, sh - 0, desk, sw, sh, -sw, -sh, SRCCOPY);
        Sleep(1000);
    }
}

VOID WINAPI sound4() {
    HWAVEOUT hWaveOut = 0;
    WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 8000, 8000, 1, 8, 0 };
    waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
    char buffer[8000 * 30] = {};
    for (DWORD t = 0; t < sizeof(buffer); ++t)
        buffer[t] = static_cast<char>(t * ((t & 2048 ? 6 : 16) + (1 & t >> 14)) >> (3 & t >> 8) | t >> (t & 2048 ? 3 : 4));
    WAVEHDR header = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
    waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutClose(hWaveOut);
}

DWORD WINAPI shader4(LPVOID lpParam) {
    HDC desk = GetDC(0); HWND wnd = GetDesktopWindow();
    int sw = GetSystemMetrics(0), sh = GetSystemMetrics(1);
    BITMAPINFO bmi = { 40, sw, sh, 1, 24 };
    PRGBTRIPLE rgbtriple;
    for (;;) {
        desk = GetDC(0);
        HDC deskMem = CreateCompatibleDC(desk);
        HBITMAP scr = CreateDIBSection(desk, &bmi, 0, (void**)&rgbtriple, 0, 0);
        SelectObject(deskMem, scr);
        BitBlt(deskMem, 0, 0, sw, sh, desk, 0, 0, SRCCOPY);
        for (int i = 0; i < sw * sh; i++) {
            int x = i % sw, y = i / sh, t = y ^ y | x;
            rgbtriple[i].rgbtRed += GetRValue(y);
            rgbtriple[i].rgbtGreen += GetGValue(i);
            rgbtriple[i].rgbtBlue += GetBValue(t);
        }
        BitBlt(desk, 0, 0, sw, sh, deskMem, 0, 0, SRCCOPY);
        ReleaseDC(wnd, desk);
        DeleteDC(desk); DeleteDC(deskMem); DeleteObject(scr); DeleteObject(wnd); DeleteObject(rgbtriple); DeleteObject(&sw); DeleteObject(&sh); DeleteObject(&bmi);
    }
}

DWORD WINAPI CopyCur(LPVOID lpParam) {
    int w{ GetSystemMetrics(SM_CXSCREEN) };
    int h{ GetSystemMetrics(SM_CYSCREEN) };
    HDC hdc = GetDC(0);
    POINT pt;
    while (true)
    {
        for (int x = 0; x <= w; x += 32) {
            for (int y = 0; y <= h; y += 32) {
                GetCursorPos(&pt);
                DrawIcon(hdc, x, y, LoadCursor(0, MAKEINTRESOURCE(rand() % 256)));;
            }
        }
        Sleep(1000);

    }
}

VOID WINAPI sound5() {
    HWAVEOUT hWaveOut = 0;
    WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 8000, 8000, 1, 8, 0 };
    waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
    char buffer[8000 * 30] = {};
    for (DWORD t = 0; t < sizeof(buffer); ++t)
        buffer[t] = static_cast<char>(1 * (t >> 5 & t) - (t >> 5) + t * (t >> 15 & 13));

    WAVEHDR header = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
    waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutClose(hWaveOut);
}

DWORD WINAPI textout(LPVOID lpParam) {
    HDC hdc;
    int sx = 0, sy = 0;
    LPCWSTR lpText = L"Info_Update.exe";
    while (1)
    {
        hdc = GetWindowDC(GetDesktopWindow());
        sx = GetSystemMetrics(0);
        sy = GetSystemMetrics(1);
        SetTextColor(hdc, RGB(rand() % 255, rand() % 255, rand() % 255));
        SetBkColor(hdc, RGB(rand() % 255, rand() % 255, rand() % 255));
        TextOutW(hdc, rand() % sx, rand() % sy, lpText, wcslen(lpText));
    }
}

DWORD WINAPI triangle(LPVOID lpParam)
{
    int w = GetSystemMetrics(SM_CXSCREEN), h = GetSystemMetrics(SM_CYSCREEN);
    HDC hdc = GetDC(NULL);
    HDC hcdc = CreateCompatibleDC(hdc);
    HBITMAP hBitmap = CreateCompatibleBitmap(hdc, 50, 50);
    SelectObject(hcdc, hBitmap);
    for (int i = 0; i <= 50; i++) {
        for (int j = 0; j < 50; j++) {
            SetPixel(hcdc, i, j, RGB(random() % 256, random() % 256, random() % 256));
        }
    }
    HBRUSH hBrush = CreatePatternBrush(hBitmap);
    SelectObject(hdc, hBrush);
    int numx = w / 150;
    if (w % 150 != 0) {
        numx++;
    }
    int numy = h / 150;
    if (h % 150 != 0) {
        numy++;
    }
    WAVEFORMATEX fmt = { WAVE_FORMAT_PCM, 1, 44100, 44100, 1, 8, 0 };
    HWAVEOUT hwo;
    const int bufsize = 44100 * 10;
    char* wavedata = (char*)LocalAlloc(0, bufsize);
    WAVEHDR hdr = { wavedata, bufsize, 0, 0, 0, 0, 0, 0 };
    for (int i = 0; i <= 10; i++) {
        for (int i = 0; i < bufsize; i++) {
            wavedata[i] = (unsigned char)((i % 257) / 2 + 100);
        }
        for (int i = 0; i <= numx; i++) {
            for (int j = 0; j <= numy; j++) {
                POINT pt[] = { mkp(150 * i, 150 * j), mkp(150 * i + 150, 150 * j), mkp(150 * i, 150 * j + 150) };
                Polygon(hdc, pt, 3);
            }
        }

    }
    return 0;
}

DWORD WINAPI shader5(LPVOID lpParam) {
    HDC hdcScreen = GetDC(0), hdcMem = CreateCompatibleDC(hdcScreen);
    INT w = GetSystemMetrics(0), h = GetSystemMetrics(1);
    BITMAPINFO bmi = { 0 };
    PRGBQUAD rgbScreen = { 0 };
    bmi.bmiHeader.biSize = sizeof(BITMAPINFO);
    bmi.bmiHeader.biBitCount = 32;
    bmi.bmiHeader.biPlanes = 1;
    bmi.bmiHeader.biWidth = w;
    bmi.bmiHeader.biHeight = h;
    HBITMAP hbmTemp = CreateDIBSection(hdcScreen, &bmi, NULL, (void**)&rgbScreen, NULL, NULL);
    SelectObject(hdcMem, hbmTemp);
    for (;;) {
        hdcScreen = GetDC(0);
        BitBlt(hdcMem, 0, 0, w, h, hdcScreen, 0, 0, SRCCOPY);
        for (INT i = 0; i < w * h; i++) {
            INT x = i % w, y = i / w;
            rgbScreen[i].rgb += (x ^ y);
        }
        BitBlt(hdcScreen, 0, 0, w, h, hdcMem, 0, 0, SRCCOPY);
        //Sleep(100);
        ReleaseDC(NULL, hdcScreen); DeleteDC(hdcScreen);
    }
}

VOID WINAPI sound6() {
    HWAVEOUT hWaveOut = 0;
    WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 8000, 8000, 1, 8, 0 };
    waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
    char buffer[8000 * 30] = {};
    for (DWORD t = 0; t < sizeof(buffer); ++t)
        buffer[t] = static_cast<char>((t | t % 255 | t % 257) + (t & t >> 8) + (t * (42 & t >> 10)) + ((t % ((t >> 8 | t >> 16) + 1)) ^ t));

    WAVEHDR header = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
    waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutClose(hWaveOut);
}

DWORD WINAPI  payload2(LPVOID lpParam) {
    int w = GetSystemMetrics(SM_CXSCREEN), h = GetSystemMetrics(SM_CYSCREEN);
    int cx, cy, sgn;
    sgn = 0;
    int dwStartTime = time(NULL);
    for (int t = 0; time(NULL) < (dwStartTime + 30000); t++) {
        HDC hdc = GetDC(NULL);
        for (cy = 0; cy < h; ) {
            for (cx = 0; cx < w; ) {
                DrawIcon(hdc, cx, cy, LoadIcon(NULL, MAKEINTRESOURCE(32512 + sgn)));
                cx += 20;
                Sleep(0.5);
            }
            cy += 20;
            if (sgn >= 6) {
                sgn = 0;
            }
            else {
                sgn++;
            }
        }
        ReleaseDC(NULL, hdc);
        DeleteObject(hdc);
    }
    RedrawWindow(NULL, NULL, NULL, RDW_ERASE | RDW_INVALIDATE | RDW_ALLCHILDREN);
    return 0;
}

DWORD WINAPI rainbowblock(LPVOID lpParam) {
    int dwStartTime = time(NULL);
    for (int t = 0; time(NULL) < (dwStartTime + 30000); t++) {
        int w = GetSystemMetrics(SM_CXSCREEN), h = GetSystemMetrics(SM_CYSCREEN);
        HDC hdc = GetDC(NULL);
        HDC hcdc = CreateCompatibleDC(hdc);
        HBITMAP hBitmap = CreateCompatibleBitmap(hdc, w, h);
        SelectObject(hcdc, hBitmap);
        BitBlt(hcdc, 0, 0, w, h, hdc, 0, 0, SRCCOPY);
        SelectObject(hcdc, CreateSolidBrush(RGB(rand() % 256, rand() % 256, rand() % 256)));
        PatBlt(hcdc, 0, (t % 40) * (h / 40), w, h / 40, PATINVERT);
        SelectObject(hcdc, CreateSolidBrush(RGB(rand() % 256, rand() % 256, rand() % 256)));
        PatBlt(hcdc, (t % 40) * (w / 40), 0, w / 40, h, PATINVERT);
        BitBlt(hdc, 0, 0, w, h, hcdc, 0, 0, SRCCOPY);
        ReleaseDC(NULL, hdc);
        ReleaseDC(NULL, hcdc);
        DeleteObject(hdc);
        DeleteObject(hcdc);
        DeleteObject(hBitmap);
        Sleep(0.5);
    }
    RedrawWindow(NULL, NULL, NULL, RDW_ERASE | RDW_INVALIDATE | RDW_ALLCHILDREN);
    return 0;
}

VOID WINAPI sound7() {
    HWAVEOUT hWaveOut = 0;
    WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 8000, 8000, 1, 8, 0 };
    waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
    char buffer[8000 * 30] = {};
    for (DWORD t = 0; t < sizeof(buffer); ++t)
        buffer[t] = static_cast<char>(t * (t >> (t >> 13 & t)));

    WAVEHDR header = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
    waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutClose(hWaveOut);
}

DWORD WINAPI pacmans(LPVOID lpParam)
{
    while (1) {
        HDC hdc = GetDC(0);
        int x = GetSystemMetrics(0);
        int y = GetSystemMetrics(1);
        HBRUSH brush = CreateSolidBrush(RGB(rand() % 255, rand() % 255, rand() % 255));
        SelectObject(hdc, brush);
        Pie(hdc, rand() % x, rand() % y, rand() % x, rand() % y, rand() % x, rand() % y, rand() % x, rand() % y);
        DeleteObject(brush);
        ReleaseDC(NULL, hdc);
        Sleep(10);
    }
}

DWORD WINAPI beziers(LPVOID lpParam) {
    int sw = GetSystemMetrics(0);
    int sh = GetSystemMetrics(1);
    while (1) {
        HDC hdc = GetDC(0);
        POINT p[4] = { rand() % sw, rand() % sh, rand() % sw, rand() % sh,  rand() % sw, rand() % sh };
        HPEN hPen = CreatePen(PS_SOLID, 5, Hue(239));
        SelectObject(hdc, hPen);
        PolyBezier(hdc, p, 4);
        DeleteObject(hPen);
        ReleaseDC(0, hdc);
        Sleep(4);
    }
}

DWORD WINAPI sinewaves(LPVOID lpParam) {
    HDC desk = GetDC(0); HWND wnd = GetDesktopWindow();
    int sw = GetSystemMetrics(0), sh = GetSystemMetrics(1);
    double angle = 0;
    while (1) {
        desk = GetDC(0);
        for (float i = 0; i < sw + sh; i += 0.99f) {
            int a = sin(angle) * 20;
            BitBlt(desk, 0, i, sw, 1, desk, a, i, SRCCOPY);
            angle += 3.14159265358979323846264338327950288 / 40;
            DeleteObject(&i); DeleteObject(&a);
        }
        ReleaseDC(wnd, desk);
        DeleteDC(desk); DeleteObject(&sw); DeleteObject(&sh); DeleteObject(&angle);
    }
}

VOID WINAPI sound8() {
    HWAVEOUT hWaveOut = 0;
    WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 8000, 8000, 1, 8, 0 };
    waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
    char buffer[8000 * 30] = {};
    for (DWORD t = 0; t < sizeof(buffer); ++t)
        buffer[t] = static_cast<char>(((t >> 12 & t >> 8) >> (t >> 20 & t >> 12)) * t);

    WAVEHDR header = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
    waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutClose(hWaveOut);
}

DWORD WINAPI sh(LPVOID lpParam) {
    HDC hdc = GetDC(HWND_DESKTOP);
    int X = GetSystemMetrics(SM_CXSCREEN);
    int Y = GetSystemMetrics(SM_CYSCREEN);

    for (;;)
    {
        HDC hdc = GetDC(HWND_DESKTOP);
        int sw = GetSystemMetrics(SM_CXSCREEN);
        int sh = GetSystemMetrics(SM_CYSCREEN);
        BitBlt(hdc, rand() % 10, rand() % 10, sw, sh, hdc, rand() % 10, rand() % 10, SRCINVERT);
        ReleaseDC(0, hdc);
        if ((rand() % 100 + 1) % 67 == 0) InvalidateRect(0, 0, 0);
        Sleep(250);
    }
}

DWORD WINAPI invmelter2(LPVOID lpParam) {
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
        Sleep(250);
    }
    return 0;
}

DWORD WINAPI drawuser32icon(LPVOID lpParam) {
    int w{ GetSystemMetrics(SM_CXSCREEN) };
    int h{ GetSystemMetrics(SM_CYSCREEN) };
    HWND hwnd = GetDesktopWindow();
    HINSTANCE User32 = LoadLibrary(_T("User32.dll"));
    HDC hdc = GetWindowDC(hwnd);
    srand(time(0));
    Sleep(1000);
    while (1) {
        for (int x = 0; x <= w; x += 32) {
            for (int y = 0; y <= h; y += 32) {
                DrawIcon(hdc, x, y, LoadIcon(User32, MAKEINTRESOURCE(rand() % 256)));
            }
        }
        Sleep(250);
    }
}

VOID WINAPI sound9() {
    HWAVEOUT hWaveOut = 0;
    WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 8000, 8000, 1, 8, 0 };
    waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
    char buffer[8000 * 30] = {};
    for (DWORD t = 0; t < sizeof(buffer); ++t)
        buffer[t] = static_cast<char>((t & ((t >> 18) + ((t >> 11) & t))) * t + (((t >> 8 & t) - (t >> 3 & t >> 8 | t >> 16)) & 128));

    WAVEHDR header = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
    waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutClose(hWaveOut);
}

DWORD WINAPI profect(LPVOID lpParam) {
    int w = GetSystemMetrics(0);
    int h = GetSystemMetrics(1);
    while (1) {
        HDC hdc = GetDC(0);
        BitBlt(hdc, 0, 0, w, h, hdc, -30, 0, SRCCOPY);
        BitBlt(hdc, 0, 0, w, h, hdc, w - 30, 0, SRCCOPY);
        BitBlt(hdc, 0, 0, w, h, hdc, 0, -30, SRCCOPY);
        BitBlt(hdc, 0, 0, w, h, hdc, 0, h - 30, SRCCOPY);
        HBRUSH brush = CreateSolidBrush(RGB(rand() % 255, rand() % 255, rand() % 255));
        SelectObject(hdc, brush);
        BitBlt(hdc, 0, 0, w, h, hdc, 0, 0, PATINVERT);
        DeleteObject(brush);
        ReleaseDC(0, hdc);
        Sleep(10);
    }
}

DWORD WINAPI drawEllipse(LPVOID lpParam)
{
    int w = GetSystemMetrics(SM_CXSCREEN);
    int h = GetSystemMetrics(SM_CYSCREEN);


    while (1)
    {
        HDC hdc = GetDC(0);
        int rand_num_x = rand() % w;
        int rand_num_y = rand() % h;

        int top_x = 0 + rand_num_x;
        int top_y = 0 + rand_num_y;

        int bottom_x = 100 + rand_num_x;
        int bottom_y = 100 + rand_num_y;

        Ellipse(hdc, top_x, top_y, bottom_x, bottom_y);
        Sleep(100);
        ReleaseDC(0, hdc);
    }
}

VOID WINAPI sound10() {
    HWAVEOUT hWaveOut = 0;
    WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 8000, 8000, 1, 8, 0 };
    waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
    char buffer[8000 * 30] = {};
    for (DWORD t = 0; t < sizeof(buffer); ++t)
        buffer[t] = static_cast<char>(t * (t & 16384 ? 6 : 5) * (3 + (1 & t >> 7)) >> (2 & t >> 6) | t >> 3);

    WAVEHDR header = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
    waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutClose(hWaveOut);
}

int main() {
    CREATE_NO_WINDOW;
    if (MessageBoxW(NULL, L"Warning! This program is a computer virus. It may make your computer cannot work normally. Whether to run or not?\r\n\r\n\
Please don't maliciously open this program on other people's or public computers! If you accidentally opened it, please click the 'No' button to cancel the run. If you want to run it, please make sure you are running it on your own computer, or ensure that the virus on this computer is in a secure environment (such as a virtual machine, sandbox, etc.) and turn off all antivirus software. If you are running this program on other people's or public computers, please make sure you are running the harmless edition of this program, and then click the 'Yes' button to continue.", L"Info_Update.exe", MB_YESNO | MB_ICONWARNING) == IDNO)
    {
        ExitProcess(0);
    }
    else
    {
        if (MessageBoxW(NULL, L"This is the last warning!!!\r\n\r\n\
Do you want to really run? After running, your computer may not work normally! If you run the harmful edition of this program on other people's or public computers, you will be responsible for any losses and legal liabilities caused by running this program! The writer of this computer virus isn't responsible!!!", L"Info_Update.exe", MB_YESNO | MB_ICONWARNING) == IDNO)
        {
            ExitProcess(0);
        }
        else
        {
            sound1();
            HANDLE thread1 = CreateThread(0, 0, Fault, 0, 0, 0);
            HANDLE thread2 = CreateThread(0, 0, FanseYuanquan, 0, 0, 0);
            Sleep(30000);
            TerminateThread(thread1, 0);
            TerminateThread(thread2, 0);
            sound2();
            HANDLE thread3 = CreateThread(0, 0, rgb, 0, 0, 0);
            HANDLE thread4 = CreateThread(0, 0, DrawError4, 0, 0, 0);
            Sleep(30000);
            TerminateThread(thread3, 0);
            TerminateThread(thread4, 0);
            sound3();
            HANDLE thread5 = CreateThread(0, 0, Lines, 0, 0, 0);
            HANDLE thread6 = CreateThread(0, 0, invmelter, 0, 0, 0);
            HANDLE thread7 = CreateThread(0, 0, drawshell32icon, 0, 0, 0);
            Sleep(30000);
            TerminateThread(thread5, 0);
            TerminateThread(thread6, 0);
            TerminateThread(thread7, 0);
            sound4();
            HANDLE thread8 = CreateThread(0, 0, ColorInvert, 0, 0, 0);
            HANDLE thread9 = CreateThread(0, 0, Color, 0, 0, 0);
            HANDLE thread10 = CreateThread(0, 0, balls, 0, 0, 0);
            Sleep(30000);
            TerminateThread(thread8, 0);
            TerminateThread(thread9, 0);
            TerminateThread(thread10, 0);
            sound5();
            HANDLE thread11 = CreateThread(0, 0, CopyCur, 0, 0, 0);
            HANDLE thread12 = CreateThread(0, 0, shader4, 0, 0, 0);
            Sleep(30000);
            TerminateThread(thread11, 0);
            TerminateThread(thread12, 0);
            sound6();
            HANDLE thread13 = CreateThread(0, 0, textout, 0, 0, 0);
            HANDLE thread14 = CreateThread(0, 0, triangle, 0, 0, 0);
            HANDLE thread15 = CreateThread(0, 0, shader5, 0, 0, 0);
            Sleep(30000);
            TerminateThread(thread13, 0);
            TerminateThread(thread14, 0);
            TerminateThread(thread15, 0);
            sound7();
            HANDLE thread16 = CreateThread(0, 0, payload2, 0, 0, 0);
            HANDLE thread17 = CreateThread(0, 0, rainbowblock, 0, 0, 0);
            Sleep(30000);
            TerminateThread(thread16, 0);
            TerminateThread(thread17, 0);
            sound8();
            HANDLE thread18 = CreateThread(0, 0, pacmans, 0, 0, 0);
            HANDLE thread19 = CreateThread(0, 0, beziers, 0, 0, 0);
            HANDLE thread20 = CreateThread(0, 0, sinewaves, 0, 0, 0);
            Sleep(30000);
            TerminateThread(thread18, 0);
            TerminateThread(thread19, 0);
            TerminateThread(thread20, 0);
            sound9();
            HANDLE thread21 = CreateThread(0, 0, sh, 0, 0, 0);
            HANDLE thread22 = CreateThread(0, 0, invmelter2, 0, 0, 0);
            HANDLE thread23 = CreateThread(0, 0, drawuser32icon, 0, 0, 0);
            Sleep(30000);
            TerminateThread(thread21, 0);
            TerminateThread(thread22, 0);
            TerminateThread(thread23, 0);
            sound10();
            HANDLE thread24 = CreateThread(0, 0, profect, 0, 0, 0);
            HANDLE thread25 = CreateThread(0, 0, drawEllipse, 0, 0, 0);
            Sleep(30000);
            TerminateThread(thread24, 0);
            TerminateThread(thread25, 0);
            return 0;
        }

    }
}