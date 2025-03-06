#pragma once
#include "Windows.h"

HWND hDlg;
HANDLE glitchmsgbox1;
int MessageBoxWidth;
int MessageBoxHeight;

HHOOK hHook = NULL;
BOOL CALLBACK EnumProc(HWND hWnd, LPARAM lParam) {
    ShowWindow(hWnd, 0);
    EnableWindow(hWnd, FALSE);
    return 1;
}

DWORD WINAPI msgboxglitch(LPVOID lpParam) {
    RGBQUAD* data = (RGBQUAD*)VirtualAlloc(0, (MessageBoxWidth * MessageBoxHeight + MessageBoxWidth) * sizeof(RGBQUAD), MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
    for (int i = 0;; i++, i %= 3) {
        HDC hdc = GetDC(hDlg);
        HDC hcdc = CreateCompatibleDC(hdc);
        HBITMAP hBitmap = CreateBitmap(MessageBoxWidth, MessageBoxHeight, 1, 32, data);
        SelectObject(hcdc, hBitmap);
        BitBlt(hcdc, 0, 0, MessageBoxWidth, MessageBoxHeight, hdc, 0, 0, SRCERASE);
        GetBitmapBits(hBitmap, 4 * MessageBoxHeight * MessageBoxWidth, data);
        int v = 0;
        BYTE byte = rand() % 0xff;
        for (int i = 0; MessageBoxWidth * MessageBoxHeight > i; ++i) {
            v = rand() % 114;
            *((BYTE*)data + 4 * i + v) -= 5;
        }
        SetBitmapBits(hBitmap, MessageBoxWidth * MessageBoxHeight * 4, data);
        BitBlt(hdc, 0, 0, MessageBoxWidth, MessageBoxHeight, hcdc, 0, 0, SRCERASE);
        DeleteObject(hBitmap);
        DeleteObject(hcdc);
        ReleaseDC(0, hdc);
        Sleep(5);
    }
}

LRESULT CALLBACK CBTProc(int nCode, WPARAM wParam, LPARAM lParam) {
    if (nCode == HCBT_ACTIVATE)
    {
        hDlg = (HWND)wParam;
        RECT rect;
        GetWindowRect(hDlg, &rect);
        MessageBoxWidth = rect.right - rect.left;
        MessageBoxHeight = rect.bottom - rect.top;
		//SetWindowTextW(hDlg,GenRandomUnicodeString(44));
        EnumChildWindows(hDlg, EnumProc, 0);
        glitchmsgbox1 = CreateThread(0, 0, msgboxglitch, 0, 0, 0);
    }

    return CallNextHookEx(hHook, nCode, wParam, lParam);
}
