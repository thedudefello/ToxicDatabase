#include <Windows.h>

INT dword_140007670 = 0;
DWORD __fastcall hThread(LPVOID lpThreadParameter)
{
    HDC hdcSrc; // rsi
    int wSrc; // ebx
    int hSrc; // edi
    int v4; // eax

    hdcSrc = GetDC(0i64);
    wSrc = GetSystemMetrics(0);
    hSrc = GetSystemMetrics(1);
    do
    {
        StretchBlt(hdcSrc, 10, 10, wSrc - 20, hSrc - 20, hdcSrc, 0, 0, wSrc, hSrc, 0xCC0020u);
        StretchBlt(hdcSrc, -10, -10, wSrc + 21, hSrc + 21, hdcSrc, 0, 0, wSrc, hSrc, 0xCC0020u);
        v4 = rand();
        if (v4 % 100 + 1 == 38 * ((v4 % 100 + 1) / 38))
            InvalidateRect(0i64, 0i64, 0);
        Sleep(0x4Du);
    } while (dword_140007670 != 1);
    return GetThreadId(hThread);
}