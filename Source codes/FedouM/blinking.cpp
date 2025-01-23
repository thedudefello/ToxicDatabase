#include <Windows.h>

DWORD WINAPI shader1(LPVOID lpParam) {
    int x = GetSystemMetrics(0);
    int y = GetSystemMetrics(1);
    while (true) {
        HDC hdc = GetDC(0);
        RoundRect(hdc, x, y, 8, 1, 9, 0);
        SelectObject(hdc, 0);
        BitBlt(hdc, 0, 0, x, y, hdc, 0, 0, SRCERASE);
        DeleteDC(hdc);
    }
}

int main() {
    CreateThread(0, 0, shader1, 0, 0, 0);
    Sleep(5000);
}
