#include <Windows.h>

int WINAPI wWinMain(__in HINSTANCE hInstance, __in_opt HINSTANCE hPrevInstance, __in LPWSTR lpCmdLine, __in int nShowCmd) {
    HWND hDesktopWindow;
    HDC hDesktopDC;
    RECT Rect;

    while (TRUE) {
        hDesktopWindow = GetDesktopWindow();
        hDesktopDC = GetWindowDC(hDesktopWindow);
        GetWindowRect(hDesktopWindow, &Rect);

        for (int i = 0; i <= 1899; ++i)
            StretchBlt(hDesktopDC, i, i, Rect.right - i, Rect.bottom - i, hDesktopDC, i, i, Rect.right, Rect.bottom, SRCCOPY);
        ReleaseDC(hDesktopWindow, hDesktopDC);
        Sleep(1000);
    }
}