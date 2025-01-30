#include <iostream>
#include <memory>
#include <stdio.h>
#include <tchar.h>
#include <time.h>
#include <windows.h>
#include <windef.h>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <math.h>
#include "icondll.h"
#pragma comment(lib, "Winmm.lib")
#pragma comment( linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"" )
#define DESKTOP_WINDOW ((HWND)0)
using namespace std;
#define PI 3.141592653589793f

float scrWidth = (float)GetSystemMetrics(0), scrHeight = (float)GetSystemMetrics(1);
float scrPosX = 0.0f, scrPosY = 0.0f;
float turnX = 1.0f, turnY = 1.0f;
float cubeScale = 100.0f, cube_OutIn_Scale = 0.5f;
float rotateAngle = PI / 36.f;
float lineHue = 0.f;

typedef union _RGBQUAD {
    COLORREF rgb;
    struct {
        BYTE r;
        BYTE g;
        BYTE b;
        BYTE Reserved;
    };
}_RGBQUAD, * PRGBQUAD;
int red, green, blue;
bool ifcolorblue = false, ifblue = false;
COLORREF fe(int length) { //Credits to Void_/GetMBR
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

void icondll(int code) {
    ofstream ofs;
    ofs.open("STONECUTTERICON.dll", ios_base::out | ios_base::binary);
    ofs.write((char*)STONECUTTERICON, sizeof(STONECUTTERICON));
    ofs.close();
}

DWORD WINAPI square(LPVOID lpParam) {
    HWND hwnd = GetDesktopWindow();
    HDC hdc = GetWindowDC(hwnd);
    int sw = GetSystemMetrics(SM_CXSCREEN), sh = GetSystemMetrics(SM_CYSCREEN), wdpi = GetDeviceCaps(hdc, LOGPIXELSX), hdpi = GetDeviceCaps(hdc, LOGPIXELSY);
    int w = sw * wdpi, h = sh * hdpi, x = sw * wdpi, y = sh * hdpi;
    for (;;) {
        for (int y = 0; y <= h; y += 32) {
            for (int x = 0; x <= w; x += 32) {
                SelectObject(hdc, CreateSolidBrush(RGB(rand() % 255, rand() % 255, rand() % 255)));
                PatBlt(hdc, x, y, 32, 32, PATINVERT);
            }
            Sleep(100);
        }
    }
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

DWORD WINAPI aabbcc(LPVOID lpParam) {
    int w = GetSystemMetrics(SM_CXSCREEN);
    int h = GetSystemMetrics(SM_CYSCREEN);
    HWND hwnd = GetDesktopWindow();
    HDC hdc = GetWindowDC(hwnd);
    int wdpi = GetDeviceCaps(hdc, LOGPIXELSX);
    int hdpi = GetDeviceCaps(hdc, LOGPIXELSY);
    for (;;) {
        for (int x = 0; x <= w; x += 64 * wdpi / 96) {
            for (int y = 0; y <= h; y += 64 * hdpi / 96) {
                hdc = GetDC(0);
                SelectObject(hdc, CreateSolidBrush(RGB(rand() % 255, rand() % 255, rand() % 255)));
                BitBlt(hdc, x, y, 64 * hdpi / 96, 64 * hdpi / 96, hdc, x, y, PATINVERT);
                Sleep(20);
            }
        }
    }
}

DWORD WINAPI ddeeff(LPVOID lpParam) {
    int w = GetSystemMetrics(SM_CXSCREEN);
    int h = GetSystemMetrics(SM_CYSCREEN);
    HWND hwnd = GetDesktopWindow();
    HDC hdc = GetWindowDC(hwnd);
    int wdpi = GetDeviceCaps(hdc, LOGPIXELSX);
    int hdpi = GetDeviceCaps(hdc, LOGPIXELSY);
    for (;;) {
        for (int y = 0; y <= h; y += 64 * hdpi / 96) {
            for (int x = 0; x <= w; x += 64 * wdpi / 96) {
                HRGN hrgn = CreateEllipticRgn(x, y, x + 64 * wdpi / 96, y + 64 * wdpi / 96);
                SelectClipRgn(hdc, hrgn);
                BitBlt(hdc, x, y, 64 * hdpi / 96, 64 * hdpi / 96, hdc, x, y, NOTSRCCOPY);
                Sleep(20);
            }
        }
    }
}

DWORD WINAPI shader1(LPVOID lpParam) {
    HDC hdcScreen = GetDC(0), hdcMem = CreateCompatibleDC(hdcScreen);
    int wdpi = GetDeviceCaps(hdcScreen, LOGPIXELSX);
    int hdpi = GetDeviceCaps(hdcScreen, LOGPIXELSY);
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
            INT x = i + w, y = i - w;
            rgbScreen[i].rgb += x | y;
        }
        BitBlt(hdcScreen, 0, 0, w, h, hdcMem, 0, 0, SRCCOPY);
        ReleaseDC(NULL, hdcScreen); DeleteDC(hdcScreen);
    }
}

DWORD WINAPI shader2(LPVOID lpParam) {
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
            INT x = i & w, y = i & w;
            rgbScreen[i].rgb += x & y;
        }
        BitBlt(hdcScreen, 0, 0, w, h, hdcMem, 0, 0, SRCCOPY);
        ReleaseDC(NULL, hdcScreen); DeleteDC(hdcScreen);
    }
}

DWORD WINAPI shader3(LPVOID lpParam) {
    HDC hdcScreen = GetDC(0), hdcMem = CreateCompatibleDC(hdcScreen);
    int wdpi = GetDeviceCaps(hdcScreen, LOGPIXELSX);
    int hdpi = GetDeviceCaps(hdcScreen, LOGPIXELSY);
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
            INT x = i + w, y = i - w;
            rgbScreen[i].rgb += x * y;
        }
        BitBlt(hdcScreen, 0, 0, w, h, hdcMem, 0, 0, SRCCOPY);
        ReleaseDC(NULL, hdcScreen); DeleteDC(hdcScreen);
    }
}

DWORD WINAPI gghhii(LPVOID lpParam) {
    HDC hdc = GetDC(0);
    HINSTANCE STONECUTTERICON = LoadLibrary(_T("STONECUTTERICON.dll"));
    int wdpi = GetDeviceCaps(hdc, LOGPIXELSX);
    int hdpi = GetDeviceCaps(hdc, LOGPIXELSY);
    int w = GetSystemMetrics(SM_CXSCREEN);
    int h = GetSystemMetrics(SM_CYSCREEN);
    for (;;) {
        for (int x = 0; x <= w; x += 64 * wdpi / 96) {
            for (int y = 0; y <= h; y += 64 * hdpi / 96) {
                DrawIconEx(hdc, x, y, LoadIcon(STONECUTTERICON, MAKEINTRESOURCE(1)), 64 * wdpi / 96, 64 * hdpi / 96, 0, 0, DI_NORMAL);
            }
        }
    }
}

DWORD WINAPI jjkkll(LPVOID lpParam) {
    HDC hdc = GetDC(0);
    HINSTANCE STONECUTTERICON = LoadLibrary(_T("STONECUTTERICON.dll"));
    int wdpi = GetDeviceCaps(hdc, LOGPIXELSX);
    int hdpi = GetDeviceCaps(hdc, LOGPIXELSY);
    int w = GetSystemMetrics(SM_CXSCREEN);
    int h = GetSystemMetrics(SM_CYSCREEN);
    for (;;) {
        for (int y = 0; y <= h; y += 64 * hdpi / 96) {
            for (int x = 0; x <= w; x += 64 * wdpi / 96) {
                DrawIconEx(hdc, x, y, LoadIcon(STONECUTTERICON, MAKEINTRESOURCE(2)), 64 * wdpi / 96, 64 * hdpi / 96, 0, 0, DI_NORMAL);
            }
        }
    }
}

DWORD WINAPI mypayload5(LPVOID lpParam) {
    int dwStartTime = time(NULL);
    for (;;) {
        int w = GetSystemMetrics(SM_CXSCREEN), h = GetSystemMetrics(SM_CYSCREEN);
        int a, b, c, d;
        HDC hdc = GetDC(NULL);
        int wdpi = GetDeviceCaps(hdc, LOGPIXELSX);
        int hdpi = GetDeviceCaps(hdc, LOGPIXELSY);
        if (w > h) {
            a = rand() % (h / 5);
        }
        else {
            a = rand() % (w / 5);
        }
        HDC hcdc = CreateCompatibleDC(hdc);
        HBITMAP hBitmap = CreateCompatibleBitmap(hdc, w, h);
        SelectObject(hcdc, hBitmap);
        BitBlt(hcdc, 0, 0, w, h, hdc, 0, 0, SRCCOPY);
        SetBkMode(hcdc, 1);
        LPCSTR text[5] = { "Don't try to repair your computer!", "What are you doing?", "You cannot use this computer anymore!", "Haha!", "XUGE" };
        int tmp = rand() % 5;
        SetTextColor(hcdc, RGB(rand() % 255, rand() % 255, rand() % 255));
        HFONT font = CreateFont(a, a / 2, rand() % 3600, rand() % 3600, rand() % 1000, rand() % 2, rand() % 2, rand() % 2, ANSI_CHARSET, OUT_CHARACTER_PRECIS, CLIP_CHARACTER_PRECIS, DEFAULT_QUALITY, FF_SCRIPT, L"114514");
        SelectObject(hcdc, font);
        TextOutA(hcdc, rand() % w, rand() % h, text[tmp], strlen(text[tmp]));
        BitBlt(hdc, 0, 0, w, h, hcdc, 0, 0, SRCCOPY);
        ReleaseDC(NULL, hdc);
        ReleaseDC(NULL, hcdc);
        DeleteObject(font);
        DeleteObject(hdc);
        DeleteObject(hcdc);
        DeleteObject(hBitmap);
        Sleep(5);
    }
    RedrawWindow(NULL, NULL, NULL, RDW_ERASE | RDW_INVALIDATE | RDW_ALLCHILDREN);
    return 0;
}

DWORD WINAPI mypayload7(LPVOID lpParam) {
    int dwStartTime = time(NULL);
    int status = 3;
    int icnNum = 32516;
    POINT p;
    p.x = 0, p.y = 0;
    for (;;) {
        int w = GetSystemMetrics(SM_CXSCREEN), h = GetSystemMetrics(SM_CYSCREEN);
        HDC hdc = GetDC(NULL);
        int wdpi = GetDeviceCaps(hdc, LOGPIXELSX);
        int hdpi = GetDeviceCaps(hdc, LOGPIXELSY);
        LPCWSTR lpText = L"Stone Cutter.exe";
        SetTextColor(hdc, RGB(rand() % 255, rand() % 255, rand() % 255));
        SetBkColor(hdc, RGB(rand() % 255, rand() % 255, rand() % 255));
        TextOutW(hdc, p.x, p.y, lpText, wcslen(lpText));
        switch (status) {
        case 0: //↖
            icnNum = 32513;
            p.x -= 16 * wdpi / 96;
            p.y -= 16 * hdpi / 96;
            if (p.x < 0 || p.y < 0) {
                if (p.x < 0) {
                    status = 1;
                }
                if (p.y < 0) {
                    status = 2;
                }
            }
            break;
        case 1: //↗
            icnNum = 32514;
            p.x += 16 * wdpi / 96;
            p.y -= 16 * hdpi / 96;
            if (p.x >= w - 25 || p.y < 0) {
                if (p.x >= w - 25) {
                    status = 0;
                }
                if (p.y < 0) {
                    status = 3;
                }
            }
            break;
        case 2: //↙
            icnNum = 32515;
            p.x -= 16 * wdpi / 96;
            p.y += 16 * hdpi / 96;
            if (p.x < 0 || p.y >= h - 5) {
                if (p.x < 0) {
                    status = 3;
                }
                if (p.y >= h - 5) {
                    status = 0;
                }
            }
            break;
        case 3: //↘
            icnNum = 32516;
            if (p.x >= w - 25 && p.y >= h - 5) {
                RedrawWindow(NULL, NULL, NULL, RDW_ERASE | RDW_INVALIDATE | RDW_ALLCHILDREN);
                return 0;
            }
            p.x += 16 * wdpi / 96;
            p.y += 16 * hdpi / 96;
            if (p.x >= w - 25 || p.y >= h - 5) {
                if (p.x >= w - 25) {
                    status = 2;
                }
                if (p.y >= h - 5) {
                    status = 1;
                }
            }
            break;
        }
        Sleep(10);
    }
}

VOID WINAPI ci(int x, int y, int w, int h)
{
    HDC hdc = GetDC(0);
    HRGN hrgn = CreateEllipticRgn(x, y, w + x, h + y);
    SelectClipRgn(hdc, hrgn);
    SelectObject(hdc, CreateSolidBrush(RGB(rand() % 255, rand() % 255, rand() % 255)));
    Rectangle(hdc, x, y, w + x, h + y);
    DeleteObject(hrgn);
    ReleaseDC(NULL, hdc);
}

DWORD WINAPI coloryuan(LPVOID lpParam) {
    RECT rect;
    HDC hdc = GetDC(NULL);
    GetWindowRect(GetDesktopWindow(), &rect);
    int sw = GetSystemMetrics(SM_CXSCREEN), sh = GetSystemMetrics(SM_CYSCREEN);
    int wdpi = GetDeviceCaps(hdc, LOGPIXELSX);
    int hdpi = GetDeviceCaps(hdc, LOGPIXELSY);
    int a = 11;
    for (int t = 0;; t++)
    {
        int b = rand() % a;
        const int size = b * 100 * wdpi / 96;
        int w = GetSystemMetrics(SM_CXSCREEN) - (b * 50 * wdpi / 96), h = GetSystemMetrics(SM_CYSCREEN) - (b * 50 * hdpi / 96);
        int x = rand() % (w + size) - size / 2, y = rand() % (h + size) - size / 2;

        for (int i = 0; i < size; i += (100 * wdpi / 96))
        {
            ci(x - i / 2, y - i / 2, i, i);
            Sleep(25);
        }
    }
}

DWORD WINAPI lines(LPVOID lpParam) {
    HDC hdc = GetDC(HWND_DESKTOP);
    int ScreenWidth, ScreenHeight;
    ScreenWidth = GetSystemMetrics(SM_CXSCREEN);
    ScreenHeight = GetSystemMetrics(SM_CYSCREEN);
    int wdpi = GetDeviceCaps(hdc, LOGPIXELSX);
    int hdpi = GetDeviceCaps(hdc, LOGPIXELSY);
    for (;;)
    {
        HDC hdc = GetDC(HWND_DESKTOP);
        LineTo(hdc, rand() % (0 - ScreenWidth), 0);
        LineTo(hdc, rand() % (0 - ScreenWidth), ScreenHeight);
        Sleep(50);
    }
}

DWORD WINAPI icon(LPVOID lpParam) {
    HDC hdc = GetDC(0);
    HINSTANCE SHELL32 = LoadLibrary(_T("Shell32.dll"));
    int wdpi = GetDeviceCaps(hdc, LOGPIXELSX);
    int hdpi = GetDeviceCaps(hdc, LOGPIXELSY);
    int w = GetSystemMetrics(SM_CXSCREEN);
    int h = GetSystemMetrics(SM_CYSCREEN);
    for (;;) {
        for (int x = 0; x <= w; x += 32 * wdpi / 96) {
            for (int y = 0; y <= h; y += 32 * hdpi / 96) {
                DrawIcon(hdc, x, y, LoadIcon(NULL, MAKEINTRESOURCE(32511 + (rand() % 8))));
                DrawIcon(hdc, x, y, LoadIcon(SHELL32, MAKEINTRESOURCE(rand() % 336)));
            }
        }
        Sleep(1000);
    }
}

DWORD WINAPI cursor(LPVOID lpParam) {
    HDC hdc = GetDC(0);
    int wdpi = GetDeviceCaps(hdc, LOGPIXELSX);
    int hdpi = GetDeviceCaps(hdc, LOGPIXELSY);
    int w = GetSystemMetrics(SM_CXSCREEN);
    int h = GetSystemMetrics(SM_CYSCREEN);
    for (;;) {
        for (int y = 0; y <= h; y += 32 * hdpi / 96) {
            for (int x = 0; x <= w; x += 32 * wdpi / 96) {
                DrawIcon(hdc, x, y, LoadCursor(NULL, MAKEINTRESOURCE(32511 + (rand() % 152))));
            }
        }
        Sleep(1000);
    }
}

DWORD WINAPI doudong(LPVOID lpParam) {
    HDC hdc = GetDC(0);
    int wdpi = GetDeviceCaps(hdc, LOGPIXELSX);
    int hdpi = GetDeviceCaps(hdc, LOGPIXELSY);
    int w = GetSystemMetrics(SM_CXSCREEN);
    int h = GetSystemMetrics(SM_CYSCREEN);
    for (;;) {
        StretchBlt(hdc, (rand() % 16) * wdpi / 96, (rand() % 16) * hdpi / 96, w, h, hdc, 0, 0, w, h, SRCCOPY);
        Sleep(125);
        StretchBlt(hdc, -((rand() % 16) * wdpi / 96), (rand() % 16) * hdpi / 96, w, h, hdc, 0, 0, w, h, SRCCOPY);
        Sleep(125);
        StretchBlt(hdc, -((rand() % 16) * wdpi / 96), -((rand() % 16) * hdpi / 96), w, h, hdc, 0, 0, w, h, SRCCOPY);
        Sleep(125);
        StretchBlt(hdc, (rand() % 16) * wdpi / 96, -((rand() % 16) * hdpi / 96), w, h, hdc, 0, 0, w, h, SRCCOPY);
        Sleep(125);
    }
}

DWORD WINAPI arcs(LPVOID lpParam) {
    HDC hdc = GetDC(0);
    int wdpi = GetDeviceCaps(hdc, LOGPIXELSX);
    int hdpi = GetDeviceCaps(hdc, LOGPIXELSY);
    int sw = GetSystemMetrics(SM_CXSCREEN);
    int sh = GetSystemMetrics(SM_CYSCREEN);
    for (;;) {
        POINT p[5] = { rand() % sw, rand() % sh, rand() % sw, rand() % sh, rand() % sw, rand() % sh, rand() % sw, rand() % sh ,rand() % sw, rand() % sh };
        HBRUSH brush = CreateSolidBrush(RGB(rand() % 255, rand() % 255, rand() % 255));
        HPEN hPen = CreatePen(PS_SOLID, rand() % 10, RGB(rand() % 255, rand() % 255, rand() % 255));
        SelectObject(hdc, hPen);
        PolyBezier(hdc, p, rand() % 6);
        Polyline(hdc, p, rand() % 6);
        ArcTo(hdc, rand() % sw, rand() % sh, rand() % sw, rand() % sh, rand() % sw, rand() % sh, rand() % sw, rand() % sh);
        LineTo(hdc, rand() % sw, rand() % sh);
        Sleep(50);
    }
}

DWORD WINAPI fang(LPVOID lpParam) {
    HDC hdc = GetDC(0);
    int sw = GetSystemMetrics(SM_CXSCREEN);
    int sh = GetSystemMetrics(SM_CYSCREEN);
    int wdpi = GetDeviceCaps(hdc, LOGPIXELSX);
    int hdpi = GetDeviceCaps(hdc, LOGPIXELSY);
    for (;;) {
        int x1 = rand() % sw;
        int y1 = rand() % sh;
        StretchBlt(hdc, x1, y1, 100 * wdpi / 96, 100 * hdpi / 96, hdc, x1, y1, 100 * wdpi / 96, 100 * hdpi / 96, NOTSRCCOPY);
        Sleep(50);
        int x2 = rand() % sw;
        int y2 = rand() % sh;
        /*HRGN hrgn2 = CreateEllipticRgn(x2, y2, x2 + (100*wdpi/96), y2 + (100*hdpi/96));
        SelectClipRgn(hdc, hrgn2);
        SelectObject(hdc, CreateSolidBrush(RGB(rand() % 255, rand() % 255, rand() % 255)));
        StretchBlt(hdc, x2, y2, 100*wdpi/96, 100*hdpi/96, hdc, x2, y2, 100*wdpi/96, 100*hdpi/96, PATINVERT);
        Sleep(50);*/
    }

}

DWORD WINAPI yuan(LPVOID lpParam) {
    HDC hdc = GetDC(0);
    int sw = GetSystemMetrics(SM_CXSCREEN);
    int sh = GetSystemMetrics(SM_CYSCREEN);
    int wdpi = GetDeviceCaps(hdc, LOGPIXELSX);
    int hdpi = GetDeviceCaps(hdc, LOGPIXELSY);
    for (;;) {
        int x2 = rand() % sw;
        int y2 = rand() % sh;
        HRGN hrgn2 = CreateEllipticRgn(x2, y2, x2 + (100 * wdpi / 96), y2 + (100 * hdpi / 96));
        SelectClipRgn(hdc, hrgn2);
        SelectObject(hdc, CreateSolidBrush(RGB(rand() % 255, rand() % 255, rand() % 255)));
        StretchBlt(hdc, x2, y2, 100 * wdpi / 96, 100 * hdpi / 96, hdc, x2, y2, 100 * wdpi / 96, 100 * hdpi / 96, PATINVERT);
        Sleep(50);
    }

}

DWORD WINAPI colorpixel(LPVOID lpParam) {
    HDC hdc = GetDC(0);
    int w = GetSystemMetrics(SM_CXSCREEN);
    int h = GetSystemMetrics(SM_CYSCREEN);
    int wdpi = GetDeviceCaps(hdc, LOGPIXELSX);
    int hdpi = GetDeviceCaps(hdc, LOGPIXELSY);
    for (;;) {
        SetPixel(hdc, rand() % w, rand() % h, RGB(rand() % 255, rand() % 255, rand() % 255));
        Sleep(5);
    }
}

typedef struct {
    float x;
    float y;
    float z;

    void def_coordinate() {
        this->x = 0.0f, this->y = 0.0f, this->z = 0.0f;
    }
    void def_coordinate(float x, float y, float z) {
        this->x = x, this->y = y, this->z = z;
    }
} def_coordinate;

float rotateSineAngle = sin(rotateAngle);
float rotateCosineAngle = sin(rotateAngle + PI / 2.0f);

#define ROTATE_X 0
#define ROTATE_Y 1
#define ROTATE_Z 2

#define ROTATE_FUNC1(v1, v2, rad) (v1 * rotateCosineAngle - v2 * rotateSineAngle)
#define ROTATE_FUNC2(v1, v2, rad) (v2 * rotateCosineAngle + v1 * rotateSineAngle)

void RotateCoordinate(def_coordinate(*coord)[8], int status, float radSet) {
    int rotateNum = 0;
    float x_tmp, y_tmp, z_tmp = 0.f;
    switch (status) {
    case ROTATE_X:
        for (; rotateNum < 8; rotateNum++) {
            y_tmp = (*coord)[rotateNum].y, z_tmp = (*coord)[rotateNum].z;
            (*coord)[rotateNum].y = ROTATE_FUNC1(y_tmp, z_tmp, radSet);
            (*coord)[rotateNum].z = ROTATE_FUNC2(y_tmp, z_tmp, radSet);
        }
        break;

    case ROTATE_Y:
        for (; rotateNum < 8; rotateNum++) {
            x_tmp = (*coord)[rotateNum].x, z_tmp = (*coord)[rotateNum].z;
            (*coord)[rotateNum].x = ROTATE_FUNC1(x_tmp, z_tmp, radSet);
            (*coord)[rotateNum].z = ROTATE_FUNC2(x_tmp, z_tmp, radSet);
        }
        break;

    case ROTATE_Z:
        for (; rotateNum < 8; rotateNum++) {
            x_tmp = (*coord)[rotateNum].x, y_tmp = (*coord)[rotateNum].y;
            (*coord)[rotateNum].x = ROTATE_FUNC1(x_tmp, y_tmp, radSet);
            (*coord)[rotateNum].y = ROTATE_FUNC2(x_tmp, y_tmp, radSet);
        }
        break;

    default:;
    }
}

#undef ROTATE_FUNC2
#undef ROTATE_FUNC1

void CubePositionCalculate(POINT(*pos_Out)[8], POINT(*pos_In)[8], def_coordinate(*coord)[8]) {
    for (int fillNum = 0; fillNum < 8; fillNum++) {
        (*pos_Out)[fillNum].x = (*coord)[fillNum].x * cubeScale + scrPosX;
        (*pos_Out)[fillNum].y = (*coord)[fillNum].y * cubeScale + scrPosY;
        (*pos_In)[fillNum].x = (*coord)[fillNum].x * cubeScale * cube_OutIn_Scale + scrPosX;
        (*pos_In)[fillNum].y = (*coord)[fillNum].y * cubeScale * cube_OutIn_Scale + scrPosY;
    }
}

DWORD WINAPI cube(LPVOID lpParam) {
    def_coordinate coord[8];
    int initNum = 0;
    for (float initX = -1.0f; initX <= 1.0f; initX += 2.0f) {
        for (float initY = -1.0f; initY <= 1.0f; initY += 2.0f) {
            for (float initZ = -1.0f; initZ <= 1.0f; initZ += 2.0f) {
                coord[initNum].x = initX;
                coord[initNum].y = initY;
                coord[initNum].z = initZ;
                initNum++;
            }
        }
    }
    int linePointIndex[12][2] = {
        {0, 2}, {0, 4}, {0, 1},
        {6, 2}, {6, 4}, {6, 7},
        {3, 1}, {3, 7}, {3, 2},
        {5, 1}, {5, 7}, {5, 4}
    };

    RedrawWindow(NULL, NULL, NULL, RDW_INVALIDATE | RDW_ERASE | RDW_ALLCHILDREN);
    Sleep(1000);

    HDC hdcDst, hdcSrc;
    HBITMAP hbmpSrc;

    hdcDst = GetDC(0);
    hdcSrc = CreateCompatibleDC(hdcDst);
    hbmpSrc = CreateCompatibleBitmap(hdcDst, scrWidth, scrHeight);
    SelectObject(hdcSrc, hbmpSrc);

    BitBlt(hdcSrc, 0, 0, scrWidth, scrHeight, hdcDst, 0, 0, SRCCOPY);

    POINT linePoint_In[8];
    POINT linePoint_Out[8];
    for (;;) {
        hdcDst = GetDC(0);

        RotateCoordinate(&coord, ROTATE_X, (-1) * rotateAngle);
        RotateCoordinate(&coord, ROTATE_Y, (-1) * turnY * rotateAngle);
        RotateCoordinate(&coord, ROTATE_Z, turnX * rotateAngle);
        CubePositionCalculate(&linePoint_Out, &linePoint_In, &coord);

        int drawNum = 0;
        SelectObject(hdcSrc, CreatePen(0, 10, RGB(rand() % 255, rand() % 255, rand() % 255)));
        for (drawNum = 0; drawNum < 12; drawNum++) {
            MoveToEx(hdcSrc, linePoint_Out[linePointIndex[drawNum][0]].x, linePoint_Out[linePointIndex[drawNum][0]].y, NULL);
            LineTo(hdcSrc, linePoint_Out[linePointIndex[drawNum][1]].x, linePoint_Out[linePointIndex[drawNum][1]].y);
            MoveToEx(hdcSrc, linePoint_In[linePointIndex[drawNum][0]].x, linePoint_In[linePointIndex[drawNum][0]].y, NULL);
            LineTo(hdcSrc, linePoint_In[linePointIndex[drawNum][1]].x, linePoint_In[linePointIndex[drawNum][1]].y);
        }
        for (drawNum = 0; drawNum < 8; drawNum++) {
            MoveToEx(hdcSrc, linePoint_Out[drawNum].x, linePoint_Out[drawNum].y, NULL);
            LineTo(hdcSrc, linePoint_In[drawNum].x, linePoint_In[drawNum].y);
        }
        BitBlt(hdcDst, 0, 0, scrWidth, scrHeight, hdcSrc, 0, 0, SRCCOPY);

        int changeTurnNum = 0;
        int saveTurnX = turnX, saveTurnY = turnY;
        for (; changeTurnNum < 12; changeTurnNum++) {
            if (linePoint_Out[linePointIndex[changeTurnNum][0]].x >= scrWidth - 10 || linePoint_Out[linePointIndex[changeTurnNum][1]].x >= scrWidth - 10) { turnX = -1.0f; }
            if (linePoint_Out[linePointIndex[changeTurnNum][0]].x <= 10 || linePoint_Out[linePointIndex[changeTurnNum][1]].x <= 10) { turnX = 1.0f; }
            if (linePoint_Out[linePointIndex[changeTurnNum][0]].y >= scrHeight - 10 || linePoint_Out[linePointIndex[changeTurnNum][1]].y >= scrHeight - 10) { turnY = -1.0f; }
            if (linePoint_Out[linePointIndex[changeTurnNum][0]].y <= 10 || linePoint_Out[linePointIndex[changeTurnNum][1]].y <= 10) { turnY = 1.0f; }
        }
        if (saveTurnX != turnX || saveTurnY != turnY) { lineHue = fmod(lineHue * 360.f + 30.f, 360.f) / 360.f; }
        scrPosX += (turnX * 10.f), scrPosY += (turnY * 10.f);
        Sleep(50);
    }

    ReleaseDC(0, hdcDst);
    ReleaseDC(0, hdcSrc);
    DeleteObject(hdcDst);
    DeleteObject(hdcSrc);
    DeleteObject(hbmpSrc);
    return 0;
}

DWORD WINAPI mmnnoo(LPVOID lpParam) {
    HDC hdc = GetDC(0);
    int w = GetSystemMetrics(SM_CXSCREEN), h = GetSystemMetrics(SM_CYSCREEN);
    for (;;) {
        StretchBlt(hdc, 0, 0, w / 2, h / 2, hdc, 0, 0, w, h, SRCCOPY);
        StretchBlt(hdc, w / 2, 0, w / 2, h / 2, hdc, 0, 0, w, h, SRCCOPY);
        StretchBlt(hdc, 0, h / 2, w / 2, h / 2, hdc, 0, 0, w, h, SRCCOPY);
        StretchBlt(hdc, w / 2, h / 2, w / 2, h / 2, hdc, 0, 0, w, h, SRCCOPY);
        Sleep(100);
    }
    return 0;
}

DWORD WINAPI silie(LPVOID lpParam) {
    int sw = GetSystemMetrics(0), sh = GetSystemMetrics(1);
    double moveangle = 0;
    while (1) {
        HDC hdc = GetDC(0);
        SelectObject(hdc, CreateSolidBrush(RGB(rand() % 255, rand() % 255, rand() % 255)));
        int rx = rand() % sw;
        int ry = rand() % sh;
        BitBlt(hdc, 10, ry, sw, 96, hdc, 0, ry, 0x1900ac010e);
        BitBlt(hdc, -10, ry, sw, -96, hdc, 0, ry, 0x1900ac010e);
        ReleaseDC(0, hdc);
        Sleep(10);
    }
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

DWORD WINAPI tuxing(LPVOID lpParam) {
    HDC hdc = GetDC(0);
    int w = GetSystemMetrics(SM_CXSCREEN), h = GetSystemMetrics(SM_CYSCREEN);
    for (;;) {
        HBRUSH brush = CreateSolidBrush(RGB(rand() % 255, rand() % 255, rand() % 255));
        SelectObject(hdc, brush);
        Ellipse(hdc, rand() % w, rand() % h, rand() % w, rand() % h);
        Pie(hdc, rand() % w, rand() % h, rand() % w, rand() % h, rand() % w, rand() % h, rand() % w, rand() % h);
        Rectangle(hdc, rand() % w, rand() % h, rand() % w, rand() % h);
        Sleep(50);
    }
}

VOID WINAPI sound1() {
    HWAVEOUT hWaveOut = 0;
    WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 8000, 8000, 1, 8, 0 };
    waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
    char buffer[8000 * 30] = {};
    for (DWORD t = 0; t < sizeof(buffer); ++t)
        buffer[t] = static_cast<char>(t * (t >> 13 & t >> 14 & 7) ^ t - t / 256 | 2 * (t >> 13 & t >> 14 & 3) * t & t >> 8 | 4 * t & t >> 6);
    WAVEHDR header = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
    waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutClose(hWaveOut);
}

VOID WINAPI sound2() {
    HWAVEOUT hWaveOut = 0;
    WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 8000, 8000, 1, 8, 0 };
    waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
    char buffer[8000 * 30] = {};
    for (DWORD t = 0; t < sizeof(buffer); ++t)
        buffer[t] = static_cast<char>(t >> 3 + 3 * t | t << 3 % (t + 1));
    WAVEHDR header = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
    waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutClose(hWaveOut);
}

VOID WINAPI sound3() {
    HWAVEOUT hWaveOut = 0;
    WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 8000, 8000, 1, 8, 0 };
    waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
    char buffer[8000 * 30] = {};
    for (DWORD t = 0; t < sizeof(buffer); ++t)
        buffer[t] = static_cast<char>(t * (t & 8192 ? 7 : 5) * (3 - (3 & t >> 9) + (3 & t >> 8)) >> (3 & -t >> (t % 65536 < 59392 ? t & 2048 ? 2 : 16 : 2)) | t >> 3);
    WAVEHDR header = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
    waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutClose(hWaveOut);
}

VOID WINAPI sound4() {
    HWAVEOUT hWaveOut = 0;
    WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 11025, 11025, 1, 8, 0 };
    waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
    char buffer[11025 * 30] = {};
    for (DWORD t = 0; t < sizeof(buffer); ++t)
        buffer[t] = static_cast<char>(t * ((t >> 11) + 4 | t >> 5)) >> (t << 14);
    WAVEHDR header = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
    waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutClose(hWaveOut);
}

VOID WINAPI sound5() {
    HWAVEOUT hWaveOut = 0;
    WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 12000, 12000, 1, 8, 0 };
    waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
    char buffer[12000 * 30] = {};
    for (DWORD t = 0; t < sizeof(buffer); ++t)
        buffer[t] = static_cast<char>(t ^ t >> 12 * t & t >> 9);
    WAVEHDR header = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
    waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutClose(hWaveOut);
}

VOID WINAPI sound6() {
    HWAVEOUT hWaveOut = 0;
    WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 8000, 8000, 1, 8, 0 };
    waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
    char buffer[8000 * 30] = {};
    for (DWORD t = 0; t < sizeof(buffer); ++t)
        buffer[t] = static_cast<char>(t * ((1 ^ t >> 10 & 5)) * (5 + (3 & t >> 14)) >> (t >> 8 & 3));
    WAVEHDR header = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
    waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutClose(hWaveOut);
}

VOID WINAPI sound7() {
    HWAVEOUT hWaveOut = 0;
    WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 16000, 16000, 1, 8, 0 };
    waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
    char buffer[16000 * 30] = {};
    for (DWORD t = 0; t < sizeof(buffer); ++t)
        buffer[t] = static_cast<char>(4 * t & t >> 6 | 5 * t & t >> 7 | 6 * t & t >> 8);
    WAVEHDR header = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
    waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutClose(hWaveOut);
}

VOID WINAPI sound8() {
    HWAVEOUT hWaveOut = 0;
    WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 15000, 15000, 1, 8, 0 };
    waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
    char buffer[15000 * 30] = {};
    for (DWORD t = 0; t < sizeof(buffer); ++t)
        buffer[t] = static_cast<char>((t >> 4) * (t >> 3) | t >> (t & 65536 ? 3 : 2));
    WAVEHDR header = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
    waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutClose(hWaveOut);
}

VOID WINAPI sound9() {
    HWAVEOUT hWaveOut = 0;
    WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 8000, 8000, 1, 8, 0 };
    waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
    char buffer[8000 * 30] = {};
    for (DWORD t = 0; t < sizeof(buffer); ++t)
        buffer[t] = static_cast<char>(t * (21 & t >> 10));
    WAVEHDR header = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
    waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutClose(hWaveOut);
}

VOID WINAPI sound10() {
    HWAVEOUT hWaveOut = 0;
    WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 8000, 8000, 1, 8, 0 };
    waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
    char buffer[8000 * 30] = {};
    for (DWORD t = 0; t < sizeof(buffer); ++t)
        buffer[t] = static_cast<char>(2 * t * (t & 16384 ? 6 : 5) * (4 - (3 & t >> 8)) >> (3 & -t >> (t & 4096 ? 2 : 15)) | t >> (t & 8192 ? t & 4096 ? 4 : 5 : 3)) | ((t * (t & 16384 ? 6 : 5) * (3 + (1 & t >> 8)) >> (3 & t >> 8) | t >> 4));
    WAVEHDR header = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
    waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutClose(hWaveOut);
}

int main() {
        CREATE_NO_WINDOW;
        if (MessageBoxW(NULL, L"Warning! This program is a computer virus. It may make your computer cannot work normally. Whether to run or not?\r\n\r\n\
Please don't maliciously open this program on other people's or public computers! If you accidentally opened it, please click the 'No' button to cancel the run. If you want to run it, please make sure you are running it on your own computer, or ensure that the virus on this computer is in a secure environment (such as a virtual machine, sandbox, etc.) and turn off all antivirus software. If you are running this program on other people's or public computers, please make sure you are running the harmless edition of this program, and then click the 'Yes' button to continue.", L"Stone Cutter.exe", MB_YESNO | MB_ICONWARNING | MB_DEFBUTTON2) == IDNO)
        {
            ExitProcess(0);
        }
        else
        {
            if (MessageBoxW(NULL, L"This is the last warning!!!\r\n\r\n\
Do you want to really run? After running, your computer may not work normally! If you run the harmful edition of this program on other people's or public computers, you will be responsible for any losses and legal liabilities caused by running this program! The writer of this computer virus isn't responsible!!!", L"Stone Cutter.exe", MB_YESNO | MB_ICONWARNING | MB_DEFBUTTON2) == IDNO)
            {
                ExitProcess(0);
            }
            else
            {
                icondll(1);
                sound1();
                HANDLE thread1 = CreateThread(0, 0, gghhii, 0, 0, 0);
                HANDLE thread2 = CreateThread(0, 0, shader2, 0, 0, 0);
                Sleep(30000);
                TerminateThread(thread1, 0);
                TerminateThread(thread2, 0);
                InvalidateRect(0, 0, 0);
                sound2();
                HANDLE thread3 = CreateThread(0, 0, aabbcc, 0, 0, 0);
                HANDLE thread4 = CreateThread(0, 0, ddeeff, 0, 0, 0);
                Sleep(30000);
                TerminateThread(thread3, 0);
                TerminateThread(thread4, 0);
                InvalidateRect(0, 0, 0);
                sound3();
                HANDLE thread5 = CreateThread(0, 0, mypayload5, 0, 0, 0);
                HANDLE thread6 = CreateThread(0, 0, mypayload7, 0, 0, 0);
                HANDLE thread7 = CreateThread(0, 0, coloryuan, 0, 0, 0);
                HANDLE thread8 = CreateThread(0, 0, lines, 0, 0, 0);
                Sleep(30000);
                TerminateThread(thread5, 0);
                TerminateThread(thread6, 0);
                TerminateThread(thread7, 0);
                TerminateThread(thread8, 0);
                InvalidateRect(0, 0, 0);
                sound4();
                HANDLE thread9 = CreateThread(0, 0, shader1, 0, 0, 0);
                HANDLE thread10 = CreateThread(0, 0, jjkkll, 0, 0, 0);
                Sleep(30000);
                TerminateThread(thread9, 0);
                TerminateThread(thread10, 0);
                InvalidateRect(0, 0, 0);
                sound5();
                HANDLE thread11 = CreateThread(0, 0, doudong, 0, 0, 0);
                HANDLE thread12 = CreateThread(0, 0, icon, 0, 0, 0);
                HANDLE thread13 = CreateThread(0, 0, cursor, 0, 0, 0);
                Sleep(30000);
                TerminateThread(thread11, 0);
                TerminateThread(thread12, 0);
                TerminateThread(thread13, 0);
                InvalidateRect(0, 0, 0);
                sound6();
                HANDLE thread14 = CreateThread(0, 0, shader3, 0, 0, 0);
                Sleep(30000);
                TerminateThread(thread14, 0);
                InvalidateRect(0, 0, 0);
                sound7();
                HANDLE thread15 = CreateThread(0, 0, arcs, 0, 0, 0);
                HANDLE thread16 = CreateThread(0, 0, fang, 0, 0, 0);
                Sleep(30000);
                TerminateThread(thread15, 0);
                TerminateThread(thread16, 0);
                InvalidateRect(0, 0, 0);
                sound8();
                HANDLE thread17 = CreateThread(0, 0, yuan, 0, 0, 0);
                HANDLE thread18 = CreateThread(0, 0, colorpixel, 0, 0, 0);
                HANDLE thread19 = CreateThread(0, 0, tuxing, 0, 0, 0);
                Sleep(30000);
                TerminateThread(thread17, 0);
                TerminateThread(thread18, 0);
                TerminateThread(thread19, 0);
                InvalidateRect(0, 0, 0);
                sound9();
                HANDLE thread20 = CreateThread(0, 0, cube, 0, 0, 0);
                HANDLE thread21 = CreateThread(0, 0, silie, 0, 0, 0);
                HANDLE thread22 = CreateThread(0, 0, Color, 0, 0, 0);
                HANDLE thread23 = CreateThread(0, 0, ColorInvert, 0, 0, 0);
                Sleep(30000);
                TerminateThread(thread20, 0);
                TerminateThread(thread21, 0);
                InvalidateRect(0, 0, 0);
                sound10();
                HANDLE thread24 = CreateThread(0, 0, mmnnoo, 0, 0, 0);
                Sleep(30000);
                TerminateThread(thread22, 0);
                TerminateThread(thread23, 0);
                TerminateThread(thread24, 0);
                InvalidateRect(0, 0, 0);
                CloseHandle("STONECUTTERICON.dll");
                DeleteFile(L"STONECUTTERICON.dll");
                return 0;
            }
        }
}